package com.gmail.undifinedmaniac.mcscpplugin.network;

import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;

public class McscpMessageFormatter {
    public static List<String> formatServerChangeMessage(Pair<ServerDataType, Object> change) {
        List<String> list = new ArrayList<>();

        list.add("c");
        list.add(formatServerDataType(change.getKey()));
        list.add(String.valueOf(change.getValue()));

        return list;
    }

    public static List<String> formatPlayerChangeMessage(String uuid, Pair<PlayerDataType, Object> change) {
        List<String> list = new ArrayList<>();

        list.add("d");
        list.add(uuid);
        list.add(formatPlayerDataType(change.getKey()));
        list.add(String.valueOf(change.getValue()));

        return list;
    }

    private static String formatServerDataType(ServerDataType type) {
        switch (type) {
            case MaxPlayers:
                return "a";
            case Motd:
                return "b";
            case PlayerCount:
                return "c";
            case Weather:
                return "d";
            case Tps:
                return "e";
            case MaxRam:
                return "f";
            case TotalRam:
                return "g";
            case UsedRam:
                return "h";
            default:
                return null;
        }
    }

    private static String formatPlayerDataType(PlayerDataType type) {
        switch (type) {
            case ListName:
                return "a";
            case DisplayName:
                return "b";
            case IpAddress:
                return "c";
            case MaxHealth:
                return "d";
            case Health:
                return "e";
            case Hunger:
                return "f";
            case Level:
                return "g";
            case World:
                return "h";
            default:
                return null;
        }
    }
}
