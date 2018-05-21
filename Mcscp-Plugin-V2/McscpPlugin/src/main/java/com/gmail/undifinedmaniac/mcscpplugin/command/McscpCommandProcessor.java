package com.gmail.undifinedmaniac.mcscpplugin.command;

import com.gmail.undifinedmaniac.mcscpplugin.interfaces.IMcscpDataFetcher;
import com.gmail.undifinedmaniac.mcscpplugin.network.McscpClient;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.EventType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.PlayerDataType;
import com.gmail.undifinedmaniac.mcscpplugin.network.enums.ServerDataType;

import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;
import java.util.logging.Level;

public class McscpCommandProcessor {

    private IMcscpDataFetcher mFetcher;

    public McscpCommandProcessor(IMcscpDataFetcher fetcher) {
        mFetcher = fetcher;
    }

    public void command(List<String> stringList, McscpClient sender) {
        if (stringList.isEmpty()) {
            invalidCommandError(sender);
            return;
        }

        final int size = stringList.size();

        boolean success = true;

        switch (stringList.get(0)) {
            case "b": {
                if (size >= 2) {
                    switch (stringList.get(1)) {
                        case "a": {
                            if (size >= 3)
                                mFetcher.sendConsoleCmd(stringList.get(2));
                            else
                                success = false;

                            break;
                        }
                        case "b": {
                            if (size >= 3)
                                mFetcher.broadcastMessage(stringList.get(2));
                            else
                                success = false;

                            break;
                        }
                        case "c": {
                            mFetcher.stop();
                            break;
                        }
                        default: {
                            success = false;
                            break;
                        }
                    }
                } else {
                    success = false;
                }
                break;
            }
            case "f": {
                if (size >= 2) {
                    switch (stringList.get(1)) {
                        case "a": {
                            List<String> ping = new ArrayList<>();

                            ping.add("f");
                            ping.add("a");

                            sender.writeList(ping);
                            break;
                        }
                        case "b": {
                            if (size >= 3)
                                sender.setRequestedServerData(getServerDataTypes(stringList.get(2)));
                            else
                                sender.setRequestedServerData(EnumSet.noneOf(ServerDataType.class));

                            break;
                        }
                        case "c": {
                            if (size >= 3)
                                sender.setRequestedPlayerData(getPlayerDataTypes(stringList.get(2)));
                            else
                                sender.setRequestedPlayerData(EnumSet.noneOf(PlayerDataType.class));

                            break;
                        }
                        case "d": {
                            if (size >= 3) {
                                sender.setRequestedEvents(getEventTypes(stringList.get(2)));
                            } else {
                                sender.setRequestedEvents(EnumSet.noneOf(EventType.class));
                            }

                            break;
                        }
                    }
                } else {
                    success = false;
                }
                break;
            }
            default: {
                success = false;
                break;
            }
        }

        if (!success)
            invalidCommandError(sender);
    }

    private void invalidCommandError(McscpClient sender) {
        mFetcher.logMessage(Level.WARNING, String.format("ERROR: client sent invalid command: %s",
                sender.getAddress()));
    }

    private AbstractSet<ServerDataType> getServerDataTypes(String dataString) {
        EnumSet<ServerDataType> types = EnumSet.noneOf(ServerDataType.class);

        String[] terms = dataString.split("\\|");

        for (int i = 0; i < terms.length; i++) {
            switch (terms[i]) {
                case "a": {
                    types.add(ServerDataType.MaxPlayers);
                    break;
                }
                case "b": {
                    types.add(ServerDataType.Motd);
                    break;
                }
                case "c": {
                    types.add(ServerDataType.PlayerCount);
                    break;
                }
                case "d": {
                    types.add(ServerDataType.Weather);
                    break;
                }
                case "e": {
                    types.add(ServerDataType.Tps);
                    break;
                }
                case "f": {
                    types.add(ServerDataType.MaxRam);
                    break;
                }
                case "g": {
                    types.add(ServerDataType.TotalRam);
                    break;
                }
                case "h": {
                    types.add(ServerDataType.UsedRam);
                    break;
                }
                default:
                    break;
            }
        }

        return types;
    }

    private AbstractSet<PlayerDataType> getPlayerDataTypes(String dataString) {
        EnumSet<PlayerDataType> types = EnumSet.noneOf(PlayerDataType.class);

        String[] terms = dataString.split("\\|");

        for (int i = 0; i < terms.length; i++) {
            switch (terms[i]) {
                case "a": {
                    types.add(PlayerDataType.ListName);
                    break;
                }
                case "b": {
                    types.add(PlayerDataType.DisplayName);
                    break;
                }
                case "c": {
                    types.add(PlayerDataType.IpAddress);
                    break;
                }
                case "d": {
                    types.add(PlayerDataType.MaxHealth);
                    break;
                }
                case "e": {
                    types.add(PlayerDataType.Health);
                    break;
                }
                case "f": {
                    types.add(PlayerDataType.Hunger);
                    break;
                }
                case "g": {
                    types.add(PlayerDataType.Level);
                    break;
                }
                case "h": {
                    types.add(PlayerDataType.World);
                    break;
                }
                default:
                    break;
            }
        }

        return types;
    }

    private AbstractSet<EventType> getEventTypes(String dataString) {
        EnumSet<EventType> types = EnumSet.noneOf(EventType.class);

        String[] terms = dataString.split("\\|");

        for (int i = 0; i < terms.length; i++) {
            switch (terms[i]) {
                case "a": {
                    types.add(EventType.JoinEvent);
                    break;
                }
                case "b": {
                    types.add(EventType.LeaveEvent);
                    break;
                }
                case "c": {
                    types.add(EventType.DeathEvent);
                    break;
                }
                case "d": {
                    types.add(EventType.ChatEvent);
                    break;
                }
                case "e": {
                    types.add(EventType.LogEvent);
                    break;
                }
                default:
                    break;
            }
        }

        return types;
    }
}
