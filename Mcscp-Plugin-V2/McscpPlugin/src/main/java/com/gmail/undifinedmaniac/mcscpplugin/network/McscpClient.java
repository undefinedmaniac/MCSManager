package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicIODeviceListener;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicTcpSocket;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class McscpClient implements IBasicIODeviceListener {

    private IBasicTcpSocket mSocket;
    private TcpListStream mStream = new TcpListStream();
    private Map<DataType, Boolean> mRequestedData = new HashMap<>();

    public McscpClient(IBasicTcpSocket socket) {
        mSocket = socket;
        mStream.setSocket(mSocket);
        mStream.addListener(this);
    }

    public void setRequestState(DataType type, boolean value) {
        mRequestedData.put(type, value);
    }

    public boolean getRequestState(DataType type) {
        Boolean value = mRequestedData.get(type);

        if (value == null)
            return false;

        return value;
    }

    public void writeList(List<String> stringList) {
        mStream.writeList(stringList);
    }

    public void writeBytes(byte[] bytes) {
        mSocket.write(bytes);
    }

    public void readyRead() {

    }

    public void error(Exception e) {

    }
}
