package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.exceptions.HeaderOverflowException;
import com.gmail.undifinedmaniac.mcscpplugin.network.exceptions.InvalidHeaderException;
import com.gmail.undifinedmaniac.mcscpplugin.network.exceptions.MessageOverflowException;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicIODeviceListener;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicTcpSocket;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.ITcpListStream;

import java.nio.charset.StandardCharsets;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class TcpListStream implements ITcpListStream, IBasicIODeviceListener {

    private IBasicTcpSocket mSocket = null;

    private Queue<List<String>> mReceivedLists = new ArrayDeque<>();

    private DynamicByteBuffer mBuffer = new DynamicByteBuffer();
    private int mSpaceSearchPos = 0;
    private int mSpaceLocation, mLength;
    private int[] mHeader = null;

    private int mMaxHeaderSize = 1024,
                mMaxMessageSize = 16384;

    private List<IBasicIODeviceListener> mListeners = new ArrayList<>();

    private static final byte SPACE_BYTE = 0x20;

    public static byte[] formatStringlist(List<String> list) {
        final int listSize = list.size();

        int[] headerData = new int[listSize];

        //Concatinate the strings and grab the header positions
        StringBuilder message = new StringBuilder();
        for (int i = 0; i < listSize; i++) {
            final int termStartPos = message.length();
            if (termStartPos != 0)
                headerData[i - 1] = termStartPos;

            message.append(list.get(i));
        }

        //Set the last header number to the total message size
        byte[] messageBytes = message.toString().getBytes(StandardCharsets.UTF_8);
        final int totalMessageSize = messageBytes.length;
        headerData[listSize - 1] = totalMessageSize;

        //Convert the list of ints into a String header
        StringBuilder header = new StringBuilder();
        for (int i = 0; i < listSize; i++) {
            header.append(headerData[i]);

            if (i != listSize - 1)
                header.append('.');
            else
                header.append(' ');
        }

        byte[] headerBytes = header.toString().getBytes(StandardCharsets.UTF_8);

        byte[] finalMessage = new byte[headerBytes.length + messageBytes.length];
        System.arraycopy(headerBytes, 0, finalMessage, 0, headerBytes.length);
        System.arraycopy(messageBytes, 0, finalMessage, headerBytes.length, messageBytes.length);

        return finalMessage;
    }

    public void setSocket(IBasicTcpSocket socket) {
        if (mSocket != null)
            mSocket.removeListener(this);

        if (socket!= null)
            socket.addListener(this);

        mSocket = socket;
    }

    public IBasicTcpSocket getSocket() {
        return mSocket;
    }

    public void setMaxHeaderSize(int maxSize) {
        mMaxHeaderSize = maxSize;
    }

    public int getMaxHeaderSize() {
        return mMaxHeaderSize;
    }

    public void setMaxMessageSize(int maxSize) {
        mMaxMessageSize = maxSize;
    }

    public int getMaxMessageSize() {
        return mMaxMessageSize;
    }

    public void readyRead() {
        mSpaceSearchPos = mBuffer.size();
        try {
            mBuffer.write(mSocket.readAll());
        } catch (Exception e) {
            error(e);
        }

        if (mBuffer.size() > mMaxMessageSize) {
            error(new MessageOverflowException());
            resetReadData(-1);
            return;
        }

        while (true) {
            if (mHeader == null) {
                mSpaceLocation = mBuffer.indexOf(SPACE_BYTE, mSpaceSearchPos);

                if (mSpaceLocation == -1) {
                    if (mBuffer.size() > mMaxHeaderSize) {
                        error(new HeaderOverflowException());
                        resetReadData(-1);
                    }
                    return;
                }

                if (!fetchHeader()) {
                    error(new InvalidHeaderException());
                    resetReadData(-1);
                    return;
                }

                mLength = mSpaceLocation + mHeader[mHeader.length - 1] + 1;
            }

            if (mBuffer.size() < mLength)
                return;

            final byte[] messageBytes = mBuffer.mid(mSpaceLocation + 1, mHeader[mHeader.length - 1]);

            final String message = new String(messageBytes, StandardCharsets.UTF_8);

            List<String> list = new ArrayList<>(mHeader.length);

            for (int i = 0; i < mHeader.length; i++) {
                int startPos, endPos;

                if (i == 0)
                    startPos = 0;
                else
                    startPos = mHeader[i - 1];

                if (i == mHeader.length - 1)
                    endPos = message.length();
                else
                    endPos = mHeader[i];

                final String data = message.substring(startPos, endPos);
                list.add(data);
            }

            resetReadData(mLength);

            mReceivedLists.offer(list);
            //Emit readyRead
            for (IBasicIODeviceListener listener : mListeners)
                listener.readyRead();

            if (mBuffer.size() == 0)
                return;
        }
    }

    public void closed() {
        for (IBasicIODeviceListener listener : mListeners)
            listener.closed();
    }

    public void error(Exception e) {
        for (IBasicIODeviceListener listener : mListeners)
            listener.error(e);
    }

    public void writeList(List<String> list) {
        mSocket.write(formatStringlist(list));
    }

    public List<String> readList() {
        return mReceivedLists.poll();
    }

    public List<List<String>> readAll() {
        List<List<String>> lists = new ArrayList<>(mReceivedLists.size());

        for (int i = 0; i < mReceivedLists.size(); i++)
            lists.add(readList());

        return lists;
    }

    //readyRead signal
    public void addListener(IBasicIODeviceListener listener) {
        mListeners.add(listener);
    }

    public void removeListener(IBasicIODeviceListener listener) {
        mListeners.remove(listener);
    }

    private boolean fetchHeader() {
        final String header = new String(mBuffer.left(mSpaceLocation), StandardCharsets.UTF_8).trim();
        final String[] headerData = header.split("\\.");
        final int headerDataSize = headerData.length;

        if (headerDataSize == 0)
            return false;

        mHeader = new int[headerDataSize];

        for (int i = 0; i < headerDataSize; i++) {
            try {
                final int position = Integer.parseInt(headerData[i]);
                mHeader[i] = position;
            } catch (Exception e) {
                return false;
            }
        }

        return true;
    }

    private void resetReadData(int bufferLength) {
        if (bufferLength == -1)
            mBuffer.reset();
        else
            mBuffer.remove(0, bufferLength);
        mHeader = null;
        mSpaceSearchPos = 0;
    }
}
