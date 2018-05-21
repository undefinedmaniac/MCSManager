package com.gmail.undifinedmaniac.mcscpplugin.network;

import java.util.ArrayList;
import java.util.List;

public class McscpHandshake {

    private static final String PROTOCOL = "MCSCPV1.0.0";

    private enum State {
        Idle, WaitForProtocol, WaitForReady, Complete
    }

    private State mState = State.Idle;

    public List<String> getFirstMessage() {
        mState = State.WaitForProtocol;

        List<String> list = new ArrayList<>();

        list.add("a");
        list.add("a");
        list.add(PROTOCOL);

        return list;
    }

    public List<String> processHandshake(List<String> rececivedMessage) {
        switch (mState) {
            case WaitForProtocol: {

            }
        }
    }
}
