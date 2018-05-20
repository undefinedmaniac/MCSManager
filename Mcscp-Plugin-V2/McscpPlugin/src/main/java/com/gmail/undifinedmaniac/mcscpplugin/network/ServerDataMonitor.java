package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpDataFetcher;
import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpPlayerData;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;

import javafx.util.Pair;
import java.util.*;
import java.util.logging.Level;

class PlayerDataMonitor {
    private IMcscpPlayerData mData;
    private AbstractSet<PlayerDataType> mMonitorData;

    private Map<PlayerDataType, Object> mPlayerData = new HashMap<>();

    PlayerDataMonitor(IMcscpPlayerData playerData, AbstractSet<PlayerDataType> monitorData) {
        mData = playerData;
        mMonitorData = monitorData;
    }

    public void setPlayerDataTypes(AbstractSet<PlayerDataType> dataTypes) {
        if (mMonitorData.size() != 0) {
            mMonitorData.removeAll(dataTypes);

            for (PlayerDataType key : mMonitorData)
                mPlayerData.remove(key);

            mMonitorData.clear();
        }

        mMonitorData.addAll(dataTypes);
    }

    public List<Pair<PlayerDataType, Object>> pollPlayerChanges() {
        List<Pair<PlayerDataType, Object>> changes = new ArrayList<>();

        for (PlayerDataType type : mMonitorData) {
            Object newValue = fetchData(type);

            if (newValue == null)
                continue;

            Object oldValue = mPlayerData.put(type, newValue);

            if (!newValue.equals(oldValue))
                changes.add(new Pair<>(type, newValue));
        }

        return changes;
    }

    private Object fetchData(PlayerDataType type) {
        switch (type) {
            case ListName:
                return mData.getName();
            case DisplayName:
                return mData.getDisplayName();
            case IpAddress:
                return mData.getMaxHealth();
            case MaxHealth:
                return mData.getMaxHealth();
            case Health:
                return mData.getHealth();
            case Hunger:
                return mData.getHunger();
            case Level:
                return mData.getLevel();
            case World:
                return mData.getWorld();
            default:
                return null;
        }
    }
}

public class ServerDataMonitor {
    private IMcscpDataFetcher mFetcher;
    private AbstractSet<ServerDataType> mServerMonitorData = EnumSet.noneOf(ServerDataType.class);
    private AbstractSet<PlayerDataType> mPlayerMonitorData = EnumSet.noneOf(PlayerDataType.class);

    private Map<ServerDataType, Object> mServerData = new HashMap<>();
    private Map<String, PlayerDataMonitor> mPlayers = new HashMap<>();

    public ServerDataMonitor(McscpNetworkCore core) {
        mFetcher = core.getFetcher();
    }

    public void setServerDataTypes(AbstractSet<ServerDataType> dataTypes) {
        if (mServerMonitorData.size() != 0) {
            mServerMonitorData.removeAll(dataTypes);

            for (ServerDataType key : mServerMonitorData)
                mServerData.remove(key);

            mServerMonitorData.clear();
        }

        mServerMonitorData.addAll(dataTypes);
    }

    public List<Pair<ServerDataType, Object>> pollServerChanges() {
        List<Pair<ServerDataType, Object>> changes = new ArrayList<>();

        for (ServerDataType type : mServerMonitorData) {
            Object newValue = fetchData(type);

            if (newValue == null)
                continue;

            Object oldValue = mServerData.put(type, newValue);

            if (!newValue.equals(oldValue))
                changes.add(new Pair<>(type, newValue));
        }

        return changes;
    }

    public void setPlayerDataTypes(AbstractSet<PlayerDataType> dataTypes) {
        if (mPlayerMonitorData.size() != 0) {
            mPlayerMonitorData.removeAll(dataTypes);

            for (PlayerDataType key : mPlayerMonitorData)
                mPlayerMonitorData.remove(key);

            mPlayerMonitorData.clear();
        }

        mPlayerMonitorData.addAll(dataTypes);
    }

    public List<Pair<String, List<Pair<PlayerDataType, Object>>>> pollPlayerChanges() {
        List<Pair<String, List<Pair<PlayerDataType, Object>>>> changes = new ArrayList<>();

        for (Map.Entry<String, PlayerDataMonitor> entry : mPlayers.entrySet())
            changes.add(new Pair<>(entry.getKey(), entry.getValue().pollPlayerChanges()));

        return changes;
    }

    //Slots
    public void playerJoinEvent(String uuid) {
        PlayerDataMonitor player = new PlayerDataMonitor(mFetcher.getPlayerData(uuid), mPlayerMonitorData);
        mPlayers.put(uuid, player);
    }

    public void playerLeaveEvent(String uuid) {
        mPlayers.remove(uuid);
    }

    //Private functions
    private Object fetchData(ServerDataType type) {
        switch (type) {
            case MaxPlayers:
                return mFetcher.getMaxPlayers();
            case Motd:
                return mFetcher.getMotd();
            case MaxRam:
                return mFetcher.getMaxRam();
            case PlayerCount:
                return mFetcher.getPlayerCount();
            case Weather:
                return mFetcher.getWeather();
            case Tps:
                return mFetcher.getTps();
            case TotalRam:
                return mFetcher.getTotalRam();
            case UsedRam:
                return mFetcher.getUsedRam();
            default:
                return null;
        }
    }
}
