package com.gmail.undifinedmaniac.mcscpplugin.network.exceptions;

public class MessageOverflowException extends Exception {
    @Override
    public String getMessage() {
        return "The message length exceeded the limit";
    }
}
