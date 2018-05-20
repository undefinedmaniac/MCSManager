package com.gmail.undifinedmaniac.mcscpplugin.network;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.logging.Level;

public class McscpServer {

    private McscpNetworkCore mCore;
    private ServerSocketChannel mChannel = null;
    private SelectionKey mKey = null;

    private boolean mStarted = false;

    public McscpServer(McscpNetworkCore core) {
        mCore = core;
    }

    public void start(InetSocketAddress address) throws IOException {
        mChannel = ServerSocketChannel.open();
        mChannel.configureBlocking(false);
        mChannel.socket().bind(address);
        mKey = mChannel.register(mCore.getSelector(), SelectionKey.OP_ACCEPT);
        mStarted = true;
    }

    public void stop() throws IOException {
        mStarted = false;

        if (mChannel == null || mKey == null)
            return;

        mChannel.close();
        mKey.cancel();
    }

    public boolean isStarted() {
        return mStarted;
    }

    public void selectedForAccept() {
        try {
            SocketChannel channel = mChannel.accept();
            BasicTcpSocket socket = new BasicTcpSocket(channel, mCore.getSelector());
            McscpClient client = new McscpClient(socket, mCore.getClientList());
            socket.getKey().attach(socket);
            mCore.getClientList().addClient(client);
            SocketAddress remoteAddress = channel.socket().getRemoteSocketAddress();
            mCore.getFetcher().logMessage(Level.INFO, "Client connected: " + remoteAddress);
        } catch (Exception e) {
            mCore.getFetcher().logMessage(Level.WARNING, "ERROR: IOException while accepting client connection");
        }
    }
}
