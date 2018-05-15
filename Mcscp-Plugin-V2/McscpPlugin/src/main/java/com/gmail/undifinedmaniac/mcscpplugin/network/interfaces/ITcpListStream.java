package com.gmail.undifinedmaniac.mcscpplugin.network.interfaces;

import java.util.List;

public interface ITcpListStream {
    void setSocket(IBasicTcpSocket socket);
    IBasicTcpSocket getSocket();

    void writeList(List<String> list);
    List<String> readList();
    List<List<String>> readAll();

    //readyRead signal
    void addListener(IBasicIODeviceListener listener);
    void removeListener(IBasicIODeviceListener listener);
}
