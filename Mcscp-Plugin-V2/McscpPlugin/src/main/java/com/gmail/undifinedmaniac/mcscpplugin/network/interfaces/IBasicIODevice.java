package com.gmail.undifinedmaniac.mcscpplugin.network.interfaces;

public interface IBasicIODevice {
    boolean isConnected();

    int writeBufferSize();
    int readBufferSize();
    void write(byte[] bytes);
    byte[] readAll();

    //readyRead signal
    void addListener(IBasicIODeviceListener listener);
    void removeListener(IBasicIODeviceListener listener);
}
