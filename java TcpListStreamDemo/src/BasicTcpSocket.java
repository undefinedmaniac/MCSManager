import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class BasicTcpSocket implements IBasicTcpSocket {

    private SocketChannel mChannel;
    private Selector mSelector;
    private SelectionKey mKey;

    private ByteArrayOutputStream mReadBuffer = new ByteArrayOutputStream();
    private Queue<ByteBuffer> mWriteQueue = new ArrayDeque<>();

    private List<IBasicIODeviceListener> mListeners = new ArrayList<>();

    public BasicTcpSocket(SocketChannel channel, Selector selector) {

        mChannel = channel;
        mSelector = selector;

        try {
            mChannel.configureBlocking(false);
            mKey = mChannel.register(mSelector, SelectionKey.OP_READ);
        } catch (Exception e) {
            e.printStackTrace();
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
            e.printStackTrace();
        }
    }

    public void selectedForRead() {

        int bytesRead = 0;

        //Loop until we cannot fill the buffer anymore
        do {
            ByteBuffer buffer = ByteBuffer.allocate(2048);

            try {
                bytesRead = mChannel.read(buffer);

                //End of stream
                if (bytesRead == -1)
                    return;

                byte[] bytes = new byte[bytesRead];
                buffer.get(bytes, 0, bytesRead);
                mReadBuffer.write(bytes);
            } catch (Exception e) {
                e.printStackTrace();
                return;
            }
        } while (bytesRead == 2048);

        //Emit readyRead
        for (IBasicIODeviceListener listener : mListeners)
            listener.readyRead();
    }

    public void selectedForWrite() {
        try {
            while (!mWriteQueue.isEmpty()) {
                ByteBuffer buffer = mWriteQueue.peek();

                mChannel.write(buffer);

                if (!buffer.hasRemaining())
                    mWriteQueue.poll();
                else
                    return;
            }
            //Deregister write
            mKey = mChannel.register(mSelector, SelectionKey.OP_READ);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public int writeBufferSize() {
        int sumBytes = 0;

        for (ByteBuffer buffer : mWriteQueue)
            sumBytes += buffer.remaining();

        return sumBytes;
    }

    public int readBufferSize() {
        return mReadBuffer.size();
    }

    public void write(byte[] bytes) {

        if (bytes.length == 0)
            return;

        ByteBuffer buffer = ByteBuffer.wrap(bytes);

        if (mWriteQueue.isEmpty()) {
            try {
                mChannel.write(buffer);

                if (!buffer.hasRemaining())
                    return;

                mWriteQueue.add(buffer);

                //Register this socket for read/write
                mKey = mChannel.register(mSelector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else {
            mWriteQueue.add(buffer);
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
}
