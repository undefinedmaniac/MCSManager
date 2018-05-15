package com.gmail.undifinedmaniac.mcscpplugin.network.interfaces;

public interface IBasicIODeviceListener {
    void readyRead();
    void error(Exception e);
}
