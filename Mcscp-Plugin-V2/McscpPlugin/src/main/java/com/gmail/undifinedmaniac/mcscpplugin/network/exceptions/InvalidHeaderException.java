package com.gmail.undifinedmaniac.mcscpplugin.network.exceptions;

public class InvalidHeaderException extends Exception {
    @Override
    public String getMessage() {
        return "The message header was invalid";
    }
}
