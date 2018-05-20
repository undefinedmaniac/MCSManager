package com.gmail.undifinedmaniac.mcscpplugin.network.interfaces;

import java.io.IOException;
import java.net.SocketAddress;

public interface IBasicTcpSocket extends IBasicIODevice {
    boolean isConnected();
    boolean connect(SocketAddress remote) throws IOException;
    void close();

    SocketAddress getAddress();

    void selectedForRead();
    void selectedForWrite();
}
