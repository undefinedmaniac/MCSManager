package com.gmail.undifinedmaniac.mcscpplugin.network.exceptions;

public class HeaderOverflowException extends Exception {

    @Override
    public String getMessage() {
        return "The header length exceeded the limit";
    }
}
