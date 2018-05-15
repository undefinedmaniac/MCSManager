package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicIODeviceListener;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicTcpSocket;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.List;

public class BasicTcpSocket implements IBasicTcpSocket {

    private SocketChannel mChannel;
    private Selector mSelector;
    private SelectionKey mKey;

    private ByteArrayOutputStream mReadBuffer = new ByteArrayOutputStream();
    private DynamicByteBuffer mWriteQueue = new DynamicByteBuffer();

    private List<IBasicIODeviceListener> mListeners = new ArrayList<>();

    public BasicTcpSocket(SocketChannel channel, Selector selector) {

        mChannel = channel;
        mSelector = selector;

        try {
            mChannel.configureBlocking(false);
            mKey = mChannel.register(mSelector, SelectionKey.OP_READ);
        } catch (Exception e) {
            emitError(e);
        }
    }

    public boolean isConnected() {
        return mChannel.isConnected();
    }

    public boolean connect(SocketAddress remote) throws IOException {
        return mChannel.connect(remote);
    }

    public void close() {
        try {
            mChannel.close();
            mKey.cancel();
        } catch (Exception e) {
            emitError(e);
        }
    }

    public void selectedForRead() {

        int bytesRead;

        //Loop until we cannot fill the buffer anymore
        do {
            bytesRead = -1;

            ByteBuffer buffer = ByteBuffer.allocate(2048);

            try {
                bytesRead = mChannel.read(buffer);
            } catch (Exception e) {
                emitError(e);
            }

            //End of stream
            if (bytesRead == -1) {
                close();
                return;
            }

            buffer.flip();

            byte[] bytes = new byte[bytesRead];
            buffer.get(bytes, 0, bytesRead);

            try {
                mReadBuffer.write(bytes);
            } catch (Exception e) {
                emitError(e);
            }
        } while (bytesRead == 2048);

        //Emit readyRead
        for (IBasicIODeviceListener listener : mListeners)
            listener.readyRead();
    }

    public void selectedForWrite() {
        ByteBuffer buffer = ByteBuffer.wrap(mWriteQueue.toByteArray());

        try {
            mChannel.write(buffer);
        } catch (Exception e) {
            emitError(e);
        }

        mWriteQueue.remove(0, buffer.position());

        if (buffer.hasRemaining())
            return;

        //Deregister write
        try {
            mKey = mChannel.register(mSelector, SelectionKey.OP_READ);
        } catch (Exception e) {
            emitError(e);
        }
    }

    public int writeBufferSize() {
        return mWriteQueue.size();
    }

    public int readBufferSize() {
        return mReadBuffer.size();
    }

    public void write(byte[] bytes) {

        if (bytes.length == 0)
            return;

        ByteBuffer buffer = ByteBuffer.wrap(bytes);

        if (mWriteQueue.size() == 0) {
            try {
                mChannel.write(buffer);
            } catch (Exception e) {
                emitError(e);
            }

            if (!buffer.hasRemaining())
                return;

            addToWriteQueue(buffer);

            //Register this socket for read/write
            try {
                mKey = mChannel.register(mSelector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
            } catch (Exception e) {
                emitError(e);
            }
        } else {
            addToWriteQueue(buffer);
        }
    }

    public byte[] readAll() {
        byte[] bytes = mReadBuffer.toByteArray();
        mReadBuffer.reset();
        return bytes;
    }

    public void addListener(IBasicIODeviceListener listener) {
        mListeners.add(listener);
    }

    public void removeListener(IBasicIODeviceListener listener) {
        mListeners.remove(listener);
    }

    private void addToWriteQueue(ByteBuffer buffer) {
        byte[] bufferBytes = new byte[buffer.remaining()];
        buffer.get(bufferBytes);
        try {
            mWriteQueue.write(bufferBytes);
        } catch (Exception e) {
            emitError(e);
        }
    }

    private void emitError(Exception e) {
        for (IBasicIODeviceListener listener : mListeners)
            listener.error(e);
    }
}
