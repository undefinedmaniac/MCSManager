import java.util.Collection;
import java.util.List;

public interface ITcpListStream {
    void setSocket(BasicTcpSocket socket);
    BasicTcpSocket getSocket();

    void writeList(List<String> list);
    List<String> readList();
    List<List<String>> readAll();

    //readyRead signal
    void addListener(IBasicIODeviceListener listener);
    void removeListener(IBasicIODeviceListener listener);
}
