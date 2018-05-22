package com.gmail.undifinedmaniac.mcscpplugin.network;

public abstract class DelayedTask {

    private boolean mCanceled = false;

    public abstract void run();

    public boolean isCanceled() {
        return mCanceled;
    }

    public void cancel() {
        mCanceled = true;
    }
}
