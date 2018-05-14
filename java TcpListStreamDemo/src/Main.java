import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

class TcpClient implements IBasicIODeviceListener {

    private TcpListStream mStream = new TcpListStream();

    TcpClient(IBasicTcpSocket socket) {
        mStream.setSocket(socket);

        mStream.addListener(this);

        List<String> stringList = new ArrayList<>();

        stringList.add("0");
        stringList.add("2");
        stringList.add("4");
        stringList.add("6");

        mStream.writeList(stringList);
    }

    public void readyRead() {

        final List<String> stringList = mStream.readList();
        System.out.println(stringList);

        List<String> newStringList = new ArrayList<>(stringList.size());

        for (String number : stringList)
            newStringList.add(String.valueOf(Integer.valueOf(number) + 1));

        mStream.writeList(newStringList);
    }

    public void error(Exception e) {
        e.printStackTrace();
    }
}

class TcpServer {

    private Selector mSelector;

    public void start() {
        try {
            mSelector = Selector.open();

            InetSocketAddress hostAddress = new InetSocketAddress("127.0.0.1", 54620);
            ServerSocketChannel server = ServerSocketChannel.open();
            server.configureBlocking(false);
            server.socket().bind(hostAddress);
            server.register(mSelector, SelectionKey.OP_ACCEPT);

            while (true) {
                int numberOfKeys = mSelector.selectNow();

                if (numberOfKeys > 0) {
                    Iterator keys = mSelector.selectedKeys().iterator();

                    while (keys.hasNext()) {
                        SelectionKey key = (SelectionKey) keys.next();

                        keys.remove();

                        if (!key.isValid())
                            continue;

                        if (key.isAcceptable()) {
                            ServerSocketChannel serverChannel = (ServerSocketChannel) key.channel();
                            SocketChannel client = serverChannel.accept();
                            BasicTcpSocket socket = new BasicTcpSocket(client, mSelector);
                            SelectionKey clientKey = client.keyFor(mSelector);
                            clientKey.attach(socket);

                            new TcpClient(socket);
                        } else if (key.isReadable()) {
                            ((IBasicTcpSocket) key.attachment()).selectedForRead();
                        } else if (key.isWritable()) {
                            ((IBasicTcpSocket) key.attachment()).selectedForWrite();
                        }
                    }
                }

                //Thread.sleep(1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        TcpServer server = new TcpServer();
        server.start();
    }
}
