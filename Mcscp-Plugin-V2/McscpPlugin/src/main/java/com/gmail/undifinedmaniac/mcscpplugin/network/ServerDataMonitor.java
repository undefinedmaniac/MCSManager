package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpDataFetcher;
import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpPlayerData;
import com.gmail.undifinedmaniac.mcscpplugin.network.interfaces.IServerDataMonitorListener;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

class PlayerDataMonitor {
    private ServerDataMonitor mParent;
    private String mUuid;
    private IMcscpPlayerData mData;
    private Map<DataType, Boolean> mMonitorData = null;

    private Map<DataType, String> mStringData = new HashMap<>();
    private Map<DataType, Integer> mIntData = new HashMap<>();

    PlayerDataMonitor(ServerDataMonitor parent, String uuid, IMcscpPlayerData playerData) {
        mParent = parent;
        mUuid = uuid;
        mData = playerData;
    }

    public void updateMonitorData(Map<DataType, Boolean> monitorData, Collection<DataType> removedTypes) {
        mMonitorData = monitorData;

        if (removedTypes != null) {
            for (DataType type : removedTypes) {
                mStringData.remove(type);
                mIntData.remove(type);
            }
        }
    }

    public void pollChanges() {

    }
}

public class ServerDataMonitor {

    private McscpNetworkCore mCore;
    private IMcscpDataFetcher mFetcher;
    private Collection<DataType> mMonitorData = null;

    private Map<DataType, String> mStringData = new HashMap<>();
    private Map<DataType, Integer> mIntData = new HashMap<>();
    private Map<DataType, Float> mFloatData = new HashMap<>();

    private Map<String, PlayerDataMonitor> mPlayers = new HashMap<>();

    private Collection<IServerDataMonitorListener> mListeners = new ArrayList<>();

    public ServerDataMonitor(McscpNetworkCore core) {
        mCore = core;
        mFetcher = mCore.getFetcher();
    }

    public void setMonitorData(Map<DataType, Boolean> monitorData) {
        if (mMonitorData != null) {
            Collection<DataType> removedTypes = getRemovedDataTypes(mMonitorData, monitorData);
            updateMonitorData(monitorData, removedTypes);
            return;
        }

        updateMonitorData(monitorData, null);
    }

    public void pollChanges() {

    }

    //Slots
    public void playerJoinEvent(String uuid) {
        PlayerDataMonitor player = new PlayerDataMonitor(this, uuid, mFetcher.getPlayerData(uuid));
        mPlayers.put(uuid, player);
    }

    public void playerLeaveEvent(String uuid) {
        mPlayers.remove(uuid);
    }

    //Signals
    public void addListener(IServerDataMonitorListener listener) {
        mListeners.add(listener);
    }

    public void removeListener(IServerDataMonitorListener listener) {
        mListeners.remove(listener);
    }

    public void emitServerTableUpdate(DataType type, String value) {
        for (IServerDataMonitorListener listener : mListeners)
            listener.serverTableUpdate(type, value);
    }

    public void emitPlayerTableUpdate(String uuid, DataType type, String value) {
        for (IServerDataMonitorListener listener : mListeners)
            listener.playerTableUpdate(uuid, type, value);
    }

    private void updateMonitorData(Map<DataType, Boolean> monitorData, Collection<DataType> removedTypes) {
        mMonitorData = monitorData;

        if (removedTypes != null) {
            for (DataType type : removedTypes) {
                mStringData.remove(type);
                mIntData.remove(type);
                mFloatData.remove(type);
            }
        }

        for (PlayerDataMonitor monitor : mPlayers.values())
            monitor.updateMonitorData(monitorData, removedTypes);
    }

    static private Collection<DataType> getRemovedDataTypes(Map<DataType, Boolean> oldTypes,
                                                            Map<DataType, Boolean> newTypes) {
        Collection<DataType> types = new ArrayList<>();

        for (DataType type : oldTypes.keySet()) {
            if (oldTypes.getOrDefault(type, false) &&
                    !newTypes.getOrDefault(type, false))
                types.add(type);
        }

        return types;
    }
}
