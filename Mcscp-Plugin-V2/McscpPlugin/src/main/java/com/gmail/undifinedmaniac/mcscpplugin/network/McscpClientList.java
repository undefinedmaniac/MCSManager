package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;
import javafx.util.Pair;

import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;
import java.util.logging.Level;

public class McscpClientList {

    private McscpNetworkCore mCore;
    private List<McscpClient> mClients = new ArrayList<>();
    private AbstractSet<ServerDataType> mGlobalServerMonitorData = EnumSet.noneOf(ServerDataType.class);
    private AbstractSet<PlayerDataType> mGlobalPlayerMonitorData = EnumSet.noneOf(PlayerDataType.class);

    public McscpClientList(McscpNetworkCore core) {
        mCore = core;
    }

    public void addClient(McscpClient client) {
        mClients.add(client);
    }

    public void removeClient(McscpClient client) {
        mClients.remove(client);
    }

    public void disconnectAllClients() {
        //Copy our list to prevent concurrent access errors
        List<McscpClient> clients = new ArrayList<>(mClients);

        for (McscpClient client : clients)
            client.close();
    }

    public void clientServerDataTypesChanged(AbstractSet<ServerDataType> newTypes) {
        if (mGlobalServerMonitorData.addAll(newTypes))
            mCore.serverDataTypesChanged(mGlobalServerMonitorData);
    }

    public void clientPlayerDataTypesChanged(AbstractSet<PlayerDataType> newTypes) {
        if (mGlobalPlayerMonitorData.addAll(newTypes))
            mCore.playerDataTypesChanged(mGlobalPlayerMonitorData);
    }

    public void sendServerChanges(List<Pair<ServerDataType, Object>> changes) {
        for (Pair<ServerDataType, Object> change : changes) {
            List<String> list = McscpMessageFormatter.formatServerChangeMessage(change);

            byte[] message = TcpListStream.formatStringlist(list);

            for (McscpClient client : mClients) {
                if (client.getRequestedServerData().contains(change.getKey()))
                    client.writeBytes(message);
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
                        client.writeBytes(message);
                }
            }
        }
    }

    public void clientClosedConnection(McscpClient client) {
        mCore.getFetcher().logMessage(Level.INFO, String.format("Client disconnected: %s", client.getAddress()));
        removeClient(client);
    }

    public void clientException(Exception e) {
        String message = e.getMessage();

        if (message != null)
            mCore.getFetcher().logMessage(Level.WARNING, String.format("ERROR: Exception in client: %s", message));
    }
}
