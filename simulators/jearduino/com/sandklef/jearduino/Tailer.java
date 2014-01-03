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

package com.sandklef.jearduino;

import java.io.File;
import java.io.RandomAccessFile;

import com.sandklef.jearduino.TailerEvent;

public class Tailer implements Runnable {
    
    String fileName;
    File   file;
    private TailerEvent te;
    
    private boolean debug = false;

    private  int SEARDUINO_TAILER_RUNNING = 0;
    private  int SEARDUINO_TAILER_PAUSE   = 1;
    private  int SEARDUINO_TAILER_STOP    = 2;
    
    private int mode = SEARDUINO_TAILER_RUNNING;
    
    private long filePtr;
    
    public  Tailer(String inFileName, TailerEvent tEv) {
	te = tEv;
	fileName = inFileName;
	mode=SEARDUINO_TAILER_RUNNING;
    }
    
    public  Tailer(String inFileName) {
	te = null;
	fileName = inFileName;
	mode=SEARDUINO_TAILER_RUNNING;
    }
    
    public  Tailer(TailerEvent tEv) {
	this("/tmp/searduino-jearduino.log", tEv);
    }

    public void log(String s) {
	if(debug) System.out.println(s);
    }
       

    public void stop() {
	mode = SEARDUINO_TAILER_STOP;
    }

    public void run() {
	file = null;
	while (mode!=SEARDUINO_TAILER_STOP ) {
	    log (" ---  run(); while loop");	    
	    try {
		
		if (file==null) {
		    log(" ---  open file: " + fileName);
		    file = new File(fileName);
		}

		Thread.sleep(200);
		if (file==null) {
		    log(" ---  file still not there :(");
		    break;
		}

		long len = file.length();
		if (len < filePtr) {
		    log(" ---  file lenght odd, reopen next turn");
		    file=null;
		    break;
		}
		else if (len > filePtr) {
		    
		    /* OK, new entry in the file ..."
		       Use RAF to seek */
		    RandomAccessFile raFile = new RandomAccessFile(file, "r");
		    raFile.seek(filePtr);
		    
		    String line = null;
		    while ((line = raFile.readLine()) != null) {
			//			System.out.println("  FILE:  " + line);
			if (te!=null) {
			    te.handleFileInput(line);
			}
		    }
		    filePtr = raFile.getFilePointer();
		    raFile.close();
		}
	    }
	    catch (Exception e) {
		log("Warning - couldn't read file");
		file=null;
	    }
	}
    }
    
    /*
    

    public static void main(String args[]) {
	
	System.out.println("Starting...");
	Tailer tailer = new Tailer("/tmp/apa.log");

	Thread t = new Thread(tailer);
	t.start();

	for(int i=0;i<600;i++) {
	    //System.out.println(" --- while");
	    try {
		Thread.sleep(1000);
	    } catch (InterruptedException e) {
		System.out.println("waitAWhile() - exception\n");
	    }
	}
	System.out.println("Leaving...");
    }

    */
}


