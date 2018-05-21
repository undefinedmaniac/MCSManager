package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.enums.EventType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.exceptions.HeaderOverflowException;
import com.gmail.undifinedmaniac.mcscpplugin.network.exceptions.InvalidHeaderException;
import com.gmail.undifinedmaniac.mcscpplugin.network.exceptions.MessageOverflowException;
import javafx.util.Pair;
import org.bukkit.Server;

import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;
import java.util.logging.Level;

public class McscpClientList {

    private McscpNetworkCore mCore;
    private List<McscpClient> mClients = new ArrayList<>();
    private McscpCommandProcessor mCommandProcessor;
    private AbstractSet<ServerDataType> mGlobalServerMonitorData = EnumSet.noneOf(ServerDataType.class);
    private AbstractSet<PlayerDataType> mGlobalPlayerMonitorData = EnumSet.noneOf(PlayerDataType.class);

    public McscpClientList(McscpNetworkCore core) {
        mCore = core;
        mCommandProcessor = new McscpCommandProcessor(mCore.getFetcher());
    }

    public void addClient(McscpClient client) {
        mClients.add(client);
    }

    public void removeClient(McscpClient client) {
        mClients.remove(client);
    }

    public McscpCommandProcessor getCommandProcessor() {
        return mCommandProcessor;
    }

    public void disconnectAllClients() {
        //Copy our list to prevent concurrent access errors
        List<McscpClient> clients = new ArrayList<>(mClients);

        for (McscpClient client : clients)
            client.getBasicSocket().close();
    }

    public void clientServerDataTypesChanged(AbstractSet<ServerDataType> oldTypes,
                                             AbstractSet<ServerDataType> newTypes, McscpClient sender) {
        oldTypes.removeAll(newTypes);

        boolean updateNeeded = false;

        if (removeClientServerTypes(oldTypes))
            updateNeeded = true;

        EnumSet<ServerDataType> existingTypes = EnumSet.noneOf(ServerDataType.class);

        for (ServerDataType type : mGlobalServerMonitorData) {
            if (newTypes.contains(type))
                existingTypes.add(type);
        }

        for (ServerDataType type : existingTypes) {
            sender.getListStream().writeList(McscpMessageFormatter.formatServerChangeMessage(
                    new Pair<>(type, mCore.getMonitor().getServerData(type))));
        }

        if (mGlobalServerMonitorData.addAll(newTypes))
            updateNeeded = true;

        if (updateNeeded)
            mCore.getMonitor().setServerDataTypes(oldTypes, mGlobalServerMonitorData);
    }

    public void clientPlayerDataTypesChanged(AbstractSet<PlayerDataType> oldTypes,
                                             AbstractSet<PlayerDataType> newTypes, McscpClient sender) {
        oldTypes.removeAll(newTypes);

        boolean updateNeeded = false;

        if (removeClientPlayerTypes(oldTypes))
            updateNeeded = true;

        EnumSet<PlayerDataType> existingTypes = EnumSet.noneOf(PlayerDataType.class);

        for (PlayerDataType type : mGlobalPlayerMonitorData) {
            if (newTypes.contains(type))
                existingTypes.add(type);
        }

        for (PlayerDataType type : existingTypes) {
            for (Pair<String, Object> pair : mCore.getMonitor().getPlayerData(type)) {
                sender.getListStream().writeList(McscpMessageFormatter.formatPlayerChangeMessage(
                        pair.getKey(), new Pair<>(type, pair.getValue())));
            }
        }

        if (mGlobalPlayerMonitorData.addAll(newTypes))
            updateNeeded = true;

        if (updateNeeded)
            mCore.getMonitor().setPlayerDataTypes(oldTypes, mGlobalPlayerMonitorData);
    }

    public void sendServerChanges(List<Pair<ServerDataType, Object>> changes) {
        for (Pair<ServerDataType, Object> change : changes) {
            List<String> list = McscpMessageFormatter.formatServerChangeMessage(change);

            byte[] message = TcpListStream.formatStringlist(list);

            for (McscpClient client : mClients) {
                if (client.getRequestedServerData().contains(change.getKey()))
                    client.getBasicSocket().write(message);
            }
        }
    }

    public void sendPlayerChanges(List<Pair<String, List<Pair<PlayerDataType, Object>>>> changes) {
        for (Pair<String, List<Pair<PlayerDataType, Object>>> player : changes) {
            for (Pair<PlayerDataType, Object> change : player.getValue()) {
                List<String> list = McscpMessageFormatter.formatPlayerChangeMessage(player.getKey(), change);

                byte[] message = TcpListStream.formatStringlist(list);

                for (McscpClient client : mClients) {
                    if (client.getRequestedPlayerData().contains(change.getKey()))
                        client.getBasicSocket().write(message);
                }
            }
        }
    }

    public void sendPlayerJoinEvent(String uuid) {
        sendEventHelper(EventType.JoinEvent,
                McscpMessageFormatter.formatPlayerJoinEvent(uuid));
    }

    public void sendPlayerLeaveEvent(String uuid) {
        sendEventHelper(EventType.LeaveEvent,
                McscpMessageFormatter.formatPlayerLeaveEvent(uuid));
    }

    public void sendDeathEvent(String uuid, String message) {
        sendEventHelper(EventType.DeathEvent,
                McscpMessageFormatter.formatDeathEvent(uuid, message));
    }

    public void sendChatEvent(String uuid, String message) {
        sendEventHelper(EventType.ChatEvent,
                McscpMessageFormatter.formatChatEvent(uuid, message));
    }

    public void sendLogEvent(String newData) {
        sendEventHelper(EventType.LogEvent,
                McscpMessageFormatter.formatLogEvent(newData));
    }

    public void clientClosedConnection(McscpClient client) {
        mCore.getFetcher().logMessage(Level.INFO, String.format("Client disconnected: %s",
                client.getBasicSocket().getChannel().socket().getRemoteSocketAddress()));
        removeClient(client);

        clientServerDataTypesChanged(client.getRequestedServerData(), EnumSet.noneOf(ServerDataType.class), null);
        clientPlayerDataTypesChanged(client.getRequestedPlayerData(), EnumSet.noneOf(PlayerDataType.class), null);
    }

    public void clientException(Exception e, McscpClient client) {
        if (e instanceof HeaderOverflowException || e instanceof InvalidHeaderException ||
                e instanceof MessageOverflowException) {
            client.getBasicSocket().close();
        }

        String message = e.getMessage();

        if (message != null)
            mCore.getFetcher().logMessage(Level.WARNING, String.format("ERROR: Exception in client: %s", message));
    }

    private void sendEventHelper(EventType type, List<String> list) {
        List<McscpClient> receivers = new ArrayList<>();

        for (McscpClient client : mClients) {
            if (client.getRequestedEvents().contains(type))
                receivers.add(client);
        }

        if (receivers.isEmpty())
            return;

        byte[] message = TcpListStream.formatStringlist(list);

        for (McscpClient client : receivers)
            client.getBasicSocket().write(message);
    }

    private boolean removeClientServerTypes(AbstractSet<ServerDataType> serverTypes) {
        boolean changesMade = false;

        for (ServerDataType type : serverTypes) {
            boolean hasType = false;

            for (McscpClient localClient : mClients) {
                if (localClient.getRequestedServerData().contains(type)) {
                    hasType = true;
                    break;
                }
            }

            if (!hasType) {
                mGlobalServerMonitorData.remove(type);
                changesMade = true;
            }
        }

        return changesMade;
    }

    private boolean removeClientPlayerTypes(AbstractSet<PlayerDataType> playerTypes) {
        boolean changesMade = false;

        for (PlayerDataType type : playerTypes) {
            boolean hasType = false;

            for (McscpClient localClient : mClients) {
                if (localClient.getRequestedPlayerData().contains(type)) {
                    hasType = true;
                    break;
                }
            }

            if (!hasType) {
                mGlobalPlayerMonitorData.remove(type);
                changesMade = true;
            }
        }

        return changesMade;
    }
}
