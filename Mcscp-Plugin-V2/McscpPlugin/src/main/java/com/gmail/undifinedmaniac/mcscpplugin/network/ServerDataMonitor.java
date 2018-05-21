package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpDataFetcher;
import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpPlayerData;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;

import javafx.util.Pair;
import org.bukkit.entity.Player;

import java.util.*;

class PlayerDataMonitor {
    private IMcscpPlayerData mData;
    private AbstractSet<PlayerDataType> mMonitorData;

    private Map<PlayerDataType, Object> mPlayerData = new HashMap<>();

    PlayerDataMonitor(IMcscpPlayerData playerData, AbstractSet<PlayerDataType> monitorData) {
        mData = playerData;
        mMonitorData = monitorData;
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

    public Object getPlayerData(PlayerDataType type) {
        return mPlayerData.get(type);
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

    public void setServerDataTypes(AbstractSet<ServerDataType> removedTypes, AbstractSet<ServerDataType> dataTypes) {
        for (ServerDataType key : removedTypes)
            mServerData.remove(key);

        mServerMonitorData.clear();
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

    public void setPlayerDataTypes(AbstractSet<PlayerDataType> removedTypes, AbstractSet<PlayerDataType> dataTypes) {
        for (PlayerDataType key : removedTypes)
            mPlayerMonitorData.remove(key);

        mPlayerMonitorData.clear();
        mPlayerMonitorData.addAll(dataTypes);
    }

    public List<Pair<String, List<Pair<PlayerDataType, Object>>>> pollPlayerChanges() {
        List<Pair<String, List<Pair<PlayerDataType, Object>>>> changes = new ArrayList<>();

        for (Map.Entry<String, PlayerDataMonitor> entry : mPlayers.entrySet())
            changes.add(new Pair<>(entry.getKey(), entry.getValue().pollPlayerChanges()));

        return changes;
    }

    public Object getServerData(ServerDataType type) {
        return mServerData.get(type);
    }

    public List<Pair<String, Object>> getPlayerData(PlayerDataType type) {
        List<Pair<String, Object>> data = new ArrayList<>();

        for (Map.Entry<String, PlayerDataMonitor> entry : mPlayers.entrySet())
            data.add(new Pair<>(entry.getKey(), entry.getValue().getPlayerData(type)));

        return data;
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
