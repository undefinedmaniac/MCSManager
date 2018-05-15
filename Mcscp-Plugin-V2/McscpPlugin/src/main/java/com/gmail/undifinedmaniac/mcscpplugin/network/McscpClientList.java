package com.gmail.undifinedmaniac.mcscpplugin.network;

import java.util.ArrayList;
import java.util.List;

public class McscpClientList {

    private List<McscpClient> mClients = new ArrayList<>();

    public McscpClientList() {}

    public void addClient(McscpClient client) {
        mClients.add(client);
    }

    public void removeClient(McscpClient client) {
        mClients.remove(client);
    }
}
