import java.nio.charset.StandardCharsets;
import java.util.ArrayDeque;
import java.util.List;
import java.util.Queue;

public class TcpListStream implements ITcpListStream, IBasicIODeviceListener {

    private BasicTcpSocket mSocket = null;

    private Queue<List<String>> mReceivedLists = new ArrayDeque<>();

    public void setSocket(BasicTcpSocket socket) {
        if (mSocket != null)
            mSocket.removeListener(this);

        if (socket!= null)
            socket.addListener(this);

        mSocket = socket;
    }

    public BasicTcpSocket getSocket() {
        return mSocket;
    }

    public void readyRead() {

    }

    public void writeList(List<String> list) {

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

        mSocket.write(finalMessage);
    }

    public List<String> readList() {
        return null;
    }

    public List<List<String>> readAll() {
        return null;
    }

    //readyRead signal
    public void addListener(IBasicIODeviceListener listener) {

    }

    public void removeListener(IBasicIODeviceListener listener) {

    }
}
