package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.data.ServerDataMonitor;
import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpDataFetcher;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IBasicTcpSocket;

import java.net.InetSocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.util.ArrayDeque;
import java.util.Iterator;
import java.util.Queue;
import java.util.logging.Level;

class ScheduledTask {
    public DelayedTask task;
    public int tickDelay;
    public int tickCount = 0;
    public boolean repeat;
}

public class McscpNetworkCore {

    private IMcscpDataFetcher mFetcher;
    private InetSocketAddress mAddress;

    private Selector mSelector = null;

    private McscpServer mServer;
    private McscpClientList mClientList;
    private ServerDataMonitor mMonitor;

    private Queue<ScheduledTask> mTasks = new ArrayDeque<>();

    private int tickCount = 0;

    public McscpNetworkCore(IMcscpDataFetcher fetcher, String address, int port) {
        mFetcher = fetcher;
        mAddress = new InetSocketAddress(address, port);

        mClientList = new McscpClientList(this);
        mServer = new McscpServer(this);
        mMonitor = new ServerDataMonitor(this);
    }

    public void start() {
        try {
            mSelector = Selector.open();
            mServer.start(mAddress);
        } catch (Exception e) {
            mFetcher.logMessage(Level.SEVERE, "ERROR: IOException while starting TCP server on address: " + mAddress);
        }
    }

    public void stop() {
        try {
            mServer.stop();
        } catch (Exception e) {
            mFetcher.logMessage(Level.SEVERE, "ERROR: IOException while stopping TCP server on address: " + mAddress);
        } finally {
            mClientList.disconnectAllClients();
        }
    }

    public void scheduleTask(DelayedTask task, int secs) {
        scheduleTask(task, secs, false);
    }

    public void scheduleTask(DelayedTask task, int secs, boolean repeat) {
        scheduleTask(task, secs, repeat, false);
    }

    public void scheduleTask(DelayedTask task, int secs, boolean repeat, boolean runImmediately) {
        ScheduledTask scheduledTask = new ScheduledTask();
        scheduledTask.task = task;
        scheduledTask.tickDelay = secs * 20;
        scheduledTask.repeat = repeat;

        if (runImmediately)
            runTask(scheduledTask);
        else
            mTasks.add(scheduledTask);
    }

    public void processEvents() {
        if (!mServer.isStarted())
            return;

        int numberOfKeys = 0;

        try {
            numberOfKeys = mSelector.selectNow();
        } catch (Exception error) {
            mFetcher.logMessage(Level.SEVERE, "ERROR: IOException while processing events");
        }

        if (numberOfKeys > 0) {
            Iterator keys = mSelector.selectedKeys().iterator();

            while (keys.hasNext()) {
                SelectionKey key = (SelectionKey)keys.next();

                keys.remove();

                if (!key.isValid())
                    continue;

                if (key.isAcceptable())
                    mServer.selectedForAccept();
                else if (key.isReadable())
                    ((IBasicTcpSocket)key.attachment()).selectedForRead();
                else if (key.isWritable())
                    ((IBasicTcpSocket)key.attachment()).selectedForWrite();
            }
        }

        if (tickCount % 10 == 0) {
            mClientList.sendServerChanges(mMonitor.pollServerChanges());
            mClientList.sendPlayerChanges(mMonitor.pollPlayerChanges());
        }

        for (int i = 0; i < mTasks.size(); i++) {
            ScheduledTask scheduledTask = mTasks.remove();

            if (scheduledTask.tickCount == scheduledTask.tickDelay) {
                runTask(scheduledTask);
            } else {
                scheduledTask.tickCount++;
                mTasks.add(scheduledTask);
            }
        }

        if (tickCount >= 20)
            tickCount = 0;

        tickCount++;
    }

    public void playerJoinEvent(String uuid) {
        mMonitor.playerJoinEvent(uuid);
        mClientList.sendPlayerJoinEvent(uuid);
    }

    public void playerLeaveEvent(String uuid) {
        mMonitor.playerLeaveEvent(uuid);
        mClientList.sendPlayerLeaveEvent(uuid);
    }

    public void deathEvent(String uuid, String message) {
        mClientList.sendDeathEvent(uuid, message);
    }

    public void chatEvent(String uuid, String message) {
        mClientList.sendChatEvent(uuid, message);
    }

    public void logEvent(String newData) {
        mClientList.sendLogEvent(newData);
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

    public ServerDataMonitor getMonitor() { return mMonitor; }

    private void runTask(ScheduledTask scheduledTask) {
        if (scheduledTask.task.isCanceled())
            return;

        scheduledTask.task.run();

        if (scheduledTask.repeat) {
            scheduledTask.tickCount = 0;
            mTasks.add(scheduledTask);
        }
    }
}
