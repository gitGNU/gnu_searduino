/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2014 Henrik Sandklef 
 *                                                                   
 * This program is free software; you can redistribute it and/or     
 * modify it under the terms of the GNU General Public License       
 * as published by the Free Software Foundation; either version 3    
 * of the License, or any later version.                             
 *                                                                   
 *                                                                   
 * This program is distributed in the hope that it will be useful,   
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
 * GNU General Public License for more details.                      
 *                                                                   
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software       
 * Foundation, Inc., 51 Franklin Street, Boston,            
 * MA  02110-1301, USA.                                              
 ****/

package com.sandklef.searduino;

import com.sandklef.searduino.Searduino;
import com.sandklef.searduino.SearduinoObserver;


public class OpenCloseArduinoCode {

    Searduino            searduino ;

    public OpenCloseArduinoCode() {

	searduino = new Searduino();
	searduino.setBoardName("UnO");
    }

    public void waitAWhile(int del) {
	try {
	    Thread.sleep(del);
	} catch (InterruptedException e) {
	    System.out.println("waitAWhile() - exception\n");
	}
    }


    public void halt() {
	searduino.haltArduinoCode();
    }

    public void run() {
	searduino.startArduinoCode();
    }

    public void load() {
	int ret;
	ret = searduino.setArduinoCodeName("../../../test/shared/libtest.so");
    }

    public void close() {
	searduino.closeArduinoCode();
    }


    public static void main(String args[]) {
	int i ;
	int cnt=0;
	OpenCloseArduinoCode oc = new OpenCloseArduinoCode();

	for (i=0;i<100;i++) {
	    System.out.println("\n================Loading/closing: " + i + " cnt:" + cnt++);
	    oc.load();
	    oc.close();
	}

	//   oc.waitAWhile(2000);
	
	/*	for (i=300;i<400;i++) {
	    System.out.println("\n================Loading/running/closing: " + i + "  cnt:" + cnt++);
	    oc.load();
	    oc.run();
	    oc.waitAWhile(200);
	    oc.close();
	}*/
	for (i=500;i<1000;i++) {
	    System.out.println("\n================Loading/running/halting/closing: " + i + "  cnt:" + cnt++);
	    oc.load();
	    oc.run();
	    // oc.waitAWhile(200);
	    oc.halt();
	    //	    oc.waitAWhile(200);
	    oc.close();
	    oc.waitAWhile(100);
	}
	
    }

}

