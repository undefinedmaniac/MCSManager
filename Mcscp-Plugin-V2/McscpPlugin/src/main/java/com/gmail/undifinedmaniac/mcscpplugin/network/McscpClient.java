package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicIODeviceListener;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicTcpSocket;

import java.net.SocketAddress;
import java.util.*;

public class McscpClient implements IBasicIODeviceListener {

    private IBasicTcpSocket mSocket;
    private McscpClientList mList;
    private TcpListStream mStream = new TcpListStream();
    private AbstractSet<ServerDataType> mRequestedServerData = EnumSet.noneOf(ServerDataType.class);
    private AbstractSet<PlayerDataType> mRequestedPlayerData = EnumSet.noneOf(PlayerDataType.class);

    public McscpClient(IBasicTcpSocket socket, McscpClientList list) {
        mSocket = socket;
        mList = list;
        mStream.setSocket(mSocket);
        mStream.addListener(this);
    }

    public void close() {
        mSocket.close();
    }

    public void setRequestedServerData(AbstractSet<ServerDataType> requestedData) {
        mRequestedServerData = requestedData;
        mList.clientServerDataTypesChanged(mRequestedServerData);
    }

    public void setRequestedPlayerData(AbstractSet<PlayerDataType> requestedData) {
        mRequestedPlayerData = requestedData;
        mList.clientPlayerDataTypesChanged(mRequestedPlayerData);
    }

    public AbstractSet<ServerDataType> getRequestedServerData() {
        return mRequestedServerData;
    }

    public AbstractSet<PlayerDataType> getRequestedPlayerData() {
        return mRequestedPlayerData;
    }

    public SocketAddress getAddress() {
        return mSocket.getAddress();
    }

    public void writeList(List<String> stringList) {
        mStream.writeList(stringList);
    }

    public void writeBytes(byte[] bytes) {
        mSocket.write(bytes);
    }

    public void readyRead() {

    }

    public void closed() {
        mList.clientClosedConnection(this);
    }

    public void error(Exception e) {
        mList.clientException(e);
    }
}
