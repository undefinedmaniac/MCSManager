package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.enums.EventType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicIODeviceListener;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicTcpSocket;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.ITcpListStream;

import java.util.*;

public class McscpClient implements IBasicIODeviceListener {

    private IBasicTcpSocket mSocket;
    private McscpClientList mList;
    private TcpListStream mStream = new TcpListStream();
    private AbstractSet<ServerDataType> mRequestedServerData = EnumSet.noneOf(ServerDataType.class);
    private AbstractSet<PlayerDataType> mRequestedPlayerData = EnumSet.noneOf(PlayerDataType.class);
    private AbstractSet<EventType> mRequestedEvents = EnumSet.noneOf(EventType.class);

    public McscpClient(IBasicTcpSocket socket, McscpClientList list) {
        mSocket = socket;
        mList = list;
        mStream.setSocket(mSocket);
        mStream.addListener(this);
    }

    public IBasicTcpSocket getBasicSocket() { return mSocket; }

    public ITcpListStream getListStream() { return mStream; }

    public void setRequestedServerData(AbstractSet<ServerDataType> requestedData) {
        EnumSet<ServerDataType> oldTypes = EnumSet.copyOf(mRequestedServerData);
        mRequestedServerData = requestedData;
        mList.clientServerDataTypesChanged(oldTypes, mRequestedServerData, this);
    }

    public void setRequestedPlayerData(AbstractSet<PlayerDataType> requestedData) {
        EnumSet<PlayerDataType> oldTypes = EnumSet.copyOf(mRequestedPlayerData);
        mRequestedPlayerData = requestedData;
        mList.clientPlayerDataTypesChanged(oldTypes, mRequestedPlayerData, this);
    }

    public void setRequestedEvents(AbstractSet<EventType> requestedData) {
        mRequestedEvents = requestedData;
    }

    public AbstractSet<ServerDataType> getRequestedServerData() {
        return mRequestedServerData;
    }

    public AbstractSet<PlayerDataType> getRequestedPlayerData() {
        return mRequestedPlayerData;
    }

    public AbstractSet<EventType> getRequestedEvents() {
        return mRequestedEvents;
    }

    public void readyRead() {
        mList.getCommandProcessor().command(mStream.readList(), this);
    }

    public void closed() {
        mList.clientClosedConnection(this);
    }

    public void error(Exception e) {
        mList.clientException(e, this);
    }
}
