package com.sandklef.searduino;

//import com.sandklef.searduino.Searduino;

public class SearduinoMain implements SearduinoObserver
{
    Searduino searduino ;

    public SearduinoMain()
    {
	searduino = new Searduino();
	//	searduino.registerObserver(this);
	System.loadLibrary("searduinojni");
    }

    public void setup()
    {
	searduino.registerPinModeCallback(this);
	searduino.registerDigitalOutCallback(this);
    }
    
    public void doer()
    {
	int i ;

	System.out.println(" seard main");

	for (i=0;i<10;i++)
	    {
		System.out.println(" pin mode [" + i + "]: " + searduino.getPinMode(i));
	    }
	System.out.println(" version:     " + searduino.getSearduinoVersion());
	System.out.println(" time limit:  " + searduino.getWriteTimelimit());

	try {
	    Thread.currentThread().sleep(4000);
	} catch (InterruptedException ie) {
	    System.out.println(ie.getMessage());
	}
    }

    public void handlePinModeEvent(int pin, int mode) {
	System.out.println("JAVA (mode) pin[" + pin + "]: mode=" + mode );
    }

    public void handleDigitalOutEvent(int pin, int value) {
	System.out.println("JAVA (digital) pin[" + pin + "]: value=" + value );
    }

    public void handleAnalogOutEvent(int pin, int value){
	System.out.println("JAVA (analog) pin[" + pin + "]: value=" + value );
    }

    public static void main(String[] args)
    {
	SearduinoMain searduinom ;
	searduinom = new SearduinoMain();
	searduinom.setup();
	searduinom.doer();
    }
}



