package com.gmail.undifinedmaniac.mcscpplugin.network.interfaces;

import java.io.IOException;
import java.net.SocketAddress;
import java.nio.channels.SocketChannel;

public interface IBasicTcpSocket extends IBasicIODevice {
    boolean isConnected();
    boolean connect(SocketAddress remote) throws IOException;
    void close();

    SocketChannel getChannel();

    void selectedForRead();
    void selectedForWrite();
}
