package com.sandklef.searduino;

public interface SearduinoObserver
{
    public void handlePinModeEvent(int pin, int mode);
    public void handlePinOutEvent(int pin, int value, int type);
    public void handlePinTypeEvent(int pin, int type);
    public void handleLogEvent(int level, String msg);
}

