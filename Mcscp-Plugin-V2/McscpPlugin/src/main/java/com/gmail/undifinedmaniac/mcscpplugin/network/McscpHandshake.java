package com.gmail.undifinedmaniac.mcscpplugin.network;

import java.util.ArrayList;
import java.util.List;

public class McscpHandshake {

    private static final String PROTOCOL = "MCSCPV1.0.0";

    private enum State {
        Idle, WaitForProtocol, WaitForReady, Complete
    }

    private State mState = State.Idle;
    private McscpClient mClient;
    private McscpNetworkCore mCore;
    private DelayedTask mTimeoutTask = new DelayedTask() {
        @Override
        public void run() {
            mClient.close();
        }
    };

    McscpHandshake(McscpClient client, McscpNetworkCore core) {
        mClient = client;
        mCore = core;
    }

    public boolean isComplete() {
        return mState == State.Complete;
    }

    public List<String> getFirstMessage() {
        mState = State.WaitForProtocol;

        mCore.scheduleTask(mTimeoutTask, 10);

        List<String> list = new ArrayList<>();

        list.add("a");
        list.add("a");
        list.add(PROTOCOL);

        return list;
    }

    public List<String> processHandshake(List<String> rececivedMessage) {
        switch (mState) {
            case WaitForProtocol: {
                if (rececivedMessage.size() >= 3 && rececivedMessage.get(0).equals("a") &&
                        rececivedMessage.get(1).equals("a") && rececivedMessage.get(2).toUpperCase().equals(PROTOCOL)) {
                    mState = State.WaitForReady;

                    List<String> list = new ArrayList<>();

                    list.add("a");
                    list.add("b");

                    return list;
                }

                return null;
            }
            case WaitForReady: {
                if (rececivedMessage.size() >= 2 && rececivedMessage.get(0).equals("a") && rececivedMessage.get(1).equals("b")) {
                    mState = State.Complete;

                    mTimeoutTask.cancel();

                    List<String> list = new ArrayList<>();

                    list.add("a");
                    list.add("c");

                    return list;
                }

                return null;
            }
            default:
                return null;
        }
    }
}
