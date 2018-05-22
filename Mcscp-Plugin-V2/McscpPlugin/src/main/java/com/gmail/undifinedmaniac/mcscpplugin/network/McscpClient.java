package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.enums.EventType;
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
    private McscpHandshake mHandshake;
    private AbstractSet<ServerDataType> mRequestedServerData = EnumSet.noneOf(ServerDataType.class);
    private AbstractSet<PlayerDataType> mRequestedPlayerData = EnumSet.noneOf(PlayerDataType.class);
    private AbstractSet<EventType> mRequestedEvents = EnumSet.noneOf(EventType.class);

    public McscpClient(IBasicTcpSocket socket, McscpClientList list) {
        mSocket = socket;
        mList = list;
        mStream.setSocket(mSocket);
        mStream.addListener(this);

        mHandshake = new McscpHandshake(this, mList.getCore());

        //Start the handshake
        directWriteList(mHandshake.getFirstMessage());
    }

    public SocketAddress getAddress() {
        return mSocket.getChannel().socket().getRemoteSocketAddress();
    }

    public void writeBytes(byte[] data) {
        if (mHandshake.isComplete())
            directWriteBytes(data);
    }

    public void writeList(List<String> list) {
        if (mHandshake.isComplete())
            directWriteList(list);
    }

    public void close() {
        mSocket.close();
    }

    public boolean isConnected() {
        return mSocket.isConnected();
    }

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
        if (mHandshake.isComplete()) {
            mList.getCommandProcessor().command(mStream.readList(), this);
        } else {
            List<String> message = mHandshake.processHandshake(mStream.readList());

            if (message == null) {
                close();
                return;
            }

            if (!message.isEmpty())
                directWriteList(message);
        }
    }

    public void closed() {
        mList.clientClosedConnection(this);
    }

    public void error(Exception e) {
        mList.clientException(e, this);
    }

    private void directWriteBytes(byte[] data) {
        mSocket.write(data);
    }

    private void directWriteList(List<String> list) {
        mStream.writeList(list);
    }
}
