package com.gmail.undifinedmaniac.mcscpplugin.network.interfaces;

import com.gmail.undifinedmaniac.mcscpplugin.network.DataType;

public interface IServerDataMonitorListener {
    void serverTableUpdate(DataType type, String value);
    void playerTableUpdate(String uuid, DataType type, String value);
}
