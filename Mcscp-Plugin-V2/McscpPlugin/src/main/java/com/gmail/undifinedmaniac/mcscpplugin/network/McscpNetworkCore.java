package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpDataFetcher;

import java.net.InetSocketAddress;
import java.nio.channels.Selector;

public class McscpNetworkCore {

    private IMcscpDataFetcher mFetcher;
    private InetSocketAddress mAddress;

    private Selector mSelector = null;

    private McscpServer mServer = new McscpServer(this);
    private McscpClientList mClientList = new McscpClientList();

    public McscpNetworkCore(IMcscpDataFetcher fetcher, String address, int port) {
        mFetcher = fetcher;
        mAddress = new InetSocketAddress(address, port);
    }

    public void start() {

    }

    public void stop() {

    }

    public void processEvents() {
    }

    public void playerJoinEvent(String uuid) {

    }

    public void playerLeaveEvent(String uuid) {

    }

    public void chatEvent(String uuid, String message) {

    }

    public void deathEvent(String uuid, String message) {

    }

    public void logEvent(String newData) {

    }

    public IMcscpDataFetcher getFetcher() {
        return mFetcher;
    }

    public Selector getSelector() {
        return mSelector;
    }

    public McscpServer getServer() {
        return mServer;
    }

    public McscpClientList getClientList() {
        return mClientList;
    }
}
