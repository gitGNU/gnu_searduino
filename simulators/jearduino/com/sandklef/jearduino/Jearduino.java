/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013 Henrik Sandklef 
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

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.BoxLayout;
import javax.swing.SwingUtilities;
import java.awt.*;
import java.awt.FlowLayout;
import javax.swing.JScrollPane;
import javax.swing.JLabel;

import com.sandklef.searduino.Searduino;
import com.sandklef.searduino.SearduinoObserver;

import java.io.File;


public class Jearduino extends JFrame implements SearduinoObserver, ExecEvent, PinEvent, BoardEvent, FileEvent, ArduinoCodeNameEvent {

    Searduino searduino ;
    
    JearduinoPreferences jpref;
    JearduinoMenu        jmenu;
    GridBagConstraints c;

    PinTable pins;
    Logger serial ;
    Logger logger ;
    InfoPanel infoPanel;
    Container pane; 

    private int codeNamesToStore = 10;
    private int nrpins = 0;
    public String version;
    //    public String boardName;

    JPanel topPanel;
    JPanel controlPanel;
    JPanel pinPanel;
    JPanel logPanel;

    ExecControl ec;
    Board board;
    

    static int appSizeHeight = 700;
    static int appSizeWidth  = 800;

    static int infoSizeHeight = 20;
    static int infoSizeWidth  = 800;

    public Jearduino() {

	jpref = new JearduinoPreferences();

	pane = getContentPane();

	System.out.println("BOARD: " + jpref.getBoard());

	pane.setLayout(new GridBagLayout());

	c = new GridBagConstraints();


	/*  info */

	setSize(appSizeHeight, appSizeWidth);


        controlPanel = new JPanel();
	controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.PAGE_AXIS));

	pinPanel = new JPanel();
	logPanel = new JPanel();

	pinPanel.setVisible(true);
	pinPanel.setLayout(new GridLayout());

	
	logPanel.setLayout(new BoxLayout(logPanel, BoxLayout.PAGE_AXIS));


	ec = new ExecControl(this);
	controlPanel.add(ec);

	jmenu = new JearduinoMenu(this, this, this);
	setJMenuBar(jmenu);

	board = new Board(this);
	
	//	controlPanel.add(board);

	searduino = new Searduino();
	infoPanel = new InfoPanel();

	logger = new Logger( "Log");
	serial = new Logger( "Serial");

	serial.setMaximumSize(new Dimension(200, 400)); 
	logger.setMaximumSize(new Dimension(200, 400)); 

	logPanel.add(serial);
	logPanel.add(logger);

	pins = new PinTable(this);
	pins.setVisible(true);
	//	pinPanel.removeAll();
	pinPanel.add(pins);

        setTitle("Jearduino - Searduino's Java frontend for Arduino simulation");

        setLocationRelativeTo(null);
	setDefaultCloseOperation(EXIT_ON_CLOSE);

	

		
	searduino.setWriteTimelimit(0);
	searduino.disableStreamedOutput();

	searduino.registerPinModeCallback(this);
	searduino.registerPinOutCallback(this);
	searduino.registerPinTypeCallback(this);
	searduino.registerLogCallback(this);

	infoPanel.setArduinoCodeName(searduino.getArduinoCodeName());
	infoPanel.setSearduinoVersion(searduino.getSearduinoVersion());

	setupSizes();
    }

    public void setupSizes()
    {
	/*
	logger.setMaximumSize(new Dimension(200, 400));
	logger.setMinimumSize(new Dimension(200, 400));

	serial.setMaximumSize(new Dimension(200, 500));
	serial.setMinimumSize(new Dimension(200, 400));
	*/
	infoPanel.setMinimumSize(new Dimension( 400, 50));
	infoPanel.setMaximumSize(new Dimension( 400, 50));

	pinPanel.setMaximumSize(new Dimension(400, 600));
	pinPanel.setMinimumSize(new Dimension(400, 600));

	controlPanel.setMaximumSize(new Dimension(400, 80));
	controlPanel.setMinimumSize(new Dimension(400, 80));

	logger.setMaximumSize(new Dimension(300, 300));
	logger.setMinimumSize(new Dimension(300, 300));
	serial.setMaximumSize(new Dimension(300, 300));
	serial.setMinimumSize(new Dimension(300, 300));

	int he = 0;

	/*  row  1*/

	c.fill = GridBagConstraints.HORIZONTAL;
	c.ipady = he;      //
	c.ipadx = 1;      //
	c.weightx = 0.0;

	c.gridx = 0;
	c.gridy = 1;

	c.gridwidth = 1;
	pane.add(pinPanel, c);

	c.fill = GridBagConstraints.HORIZONTAL;
	c.ipady = he;      //
	c.ipadx = 0;      //
	c.weightx = 0.0;

	c.gridx = 1;
	c.gridy = 1;

	c.gridwidth = 1;
	pane.add(logPanel, c);

	/* 2nd row */


	c.fill = GridBagConstraints.HORIZONTAL;
	c.ipady = he;      //
	c.ipadx = 0;      //
	c.weightx = 0.0;

	c.gridx = 0;
	c.gridy = 0;

	c.gridwidth = 2;
	pane.add(controlPanel, c);

	/* 3nd row */
	c.fill = GridBagConstraints.HORIZONTAL;
	c.ipady = 0;      //
	c.weightx = 0.0;
	c.gridwidth = 1;

	c.gridx = 0;
	c.gridy = 2;

	c.gridwidth = 2;
	pane.add(infoPanel, c);



    }


    private void setupBoard(String bName)
    {

	String ver = searduino.getSearduinoVersion();

	searduino.setBoardName(bName);
	jpref.setBoard(bName);
	infoPanel.setBoardName(bName);

	nrpins = searduino.getNrOfPins();

	version = searduino.getSearduinoVersion();
	//	boardName = searduino.getBoardName();

	pins.setupPins(nrpins);
    }


    public void handlePinTypeEvent(int pin, int type)
    {
	pins.setTypeInputPin(pin, type);
	System.out.println("EVENT: PIN TYPE-------------> JAVA (really) pin[" + pin + "]: type=" + type );
    }
    
    public void handleLogEvent(int level, String msg)
    {
	// System.out.println("EVENT: LOG MESSAGE-------------> " + level + "  " + msg );

	// HESA HESA HESA
	serial.addLog(msg);
    }
    

    public void handleBoardChoiceEvent(String bName)
    {
	System.out.println("EVENT: Board choice -------------> BOARD: " + bName );
	setupBoard(bName);
    }

    public void handlePinModeEvent(int pin, int mode) {
	if (pin==0) return;

	// HESA HESA HESA
	logger.addLog("EVENT: PIN MODE JAVA (really) pin[" + pin + "]: mode=" + mode +"\n");

	// System.out.println("JAVA (really) pin[" + pin + "]: mode=" + mode );
	pins.setMode(pin,mode);
    }

    public void handlePinOutEvent(int pin, int value, int type) {
	// System.out.println("OUT: " + pin + "  VALUE: " + value);
	//	logger.addLog("JAVA (really) out[" + pin + "]: value=" + value +"\n");
	pins.setPinValue(pin, value, type);
    }


    public void inputValueEvent(int pin, int val)
    {
	// System.out.println("PIN: " + pin + "  VALUE: " + val);
	searduino.setInputPinValue(pin, 
				   val, 
				   pins.getInputPinTypeLocal(pin));
    }

    public void ExecEvent(int type)
    {
		System.out.println("---> ExecEvent" );
	
	if (type==ExecControl.EXEC_CONTROL_PAUSE)
	    {
		System.out.println("PAUSE");
		searduino.pauseArduinoCode();
	    }
	else if (type==ExecControl.EXEC_CONTROL_RESUME)
	    {
		System.out.println("RESUME");
		searduino.resumeArduinoCode();
	    }
	else if (type==ExecControl.EXEC_CONTROL_HALT)
	    {
		System.out.println("HALT");
		searduino.haltArduinoCode();
		System.out.println("HALTED");
	    }
	else if (type==ExecControl.EXEC_CONTROL_START)
	    {
		System.out.println("START");
		searduino.startArduinoCode();
	    }
	System.out.println("<--- ExecEvent" );
    }

    public void getAndUseArduinoCodeName()
    {
	int ret;
	String codeName = jpref.getArduinoCodeName(1);
	System.out.println("getAndUseArduinoCodeName: code -------------> CODe: " + codeName );
	
	ret = searduino.setArduinoCodeName(codeName);
	if (ret!=0)
	    {
		return ;
	    }
	infoPanel.setArduinoCodeName(codeName);
    }
    
    public void showArduinoCodeNameMenu()
    {
	jmenu.removeCodeItems();
	for (int i=0;i<codeNamesToStore;i++)
	    {
		System.out.println("UPDATE MENU (" + i + ") WITH: code -------------> CODe: " +  jpref.getArduinoCodeName(i));
		
		jmenu.updateCodeItem(i, 
				     jpref.getArduinoCodeName(i));
	    }
    }


    public void saveArduinoCodeName(String canonName, String shortName)
    {
	int ret;
	ret = searduino.setArduinoCodeName(canonName);
	if (ret!=0)
	    {
		return ;
	    }

	for (int i=(codeNamesToStore-1);i>-1;i--)
	    {
		System.out.println("CURRENT MENU["+(i+1)+"]"  + jpref.getArduinoCodeName(i+1) );  
	    }
	for (int i=(codeNamesToStore-1);i>-1;i--)
	    {
		System.out.println("UPDATE MENU["+(i+1)+"]  " + jpref.getArduinoCodeName(i) + " prev: [ " + i + "]" + jpref.getArduinoCodeName(i+1));  
		jpref.setArduinoCodeName(i+1, 
					 jpref.getArduinoCodeName(i));
	    }

	System.out.println("UPDATE MENU["+(0)+"]  " + canonName);  
	jpref.setArduinoCodeName(0, canonName);
	
	infoPanel.setArduinoCodeName(shortName);
	searduino.setArduinoCodeName(canonName);
	showArduinoCodeNameMenu();
    }

    public void handleArduinoFileEvent(File f)
    {
	String boardCode = "";
	try {
	    boardCode = f.getCanonicalPath();
	}
	catch (java.io.IOException e)
	    {
		System.out.println("Uh oh... could not get file name" );
	    }

	System.out.println("EVENT: Board code choice -------------> BOARD: " + boardCode );
	int ret = 0;
	try {
	    ret = searduino.setArduinoCodeName(boardCode);
	}
	catch (java.lang.UnsatisfiedLinkError e)
	    {
		System.out.println("EXCEPTION!  - FAILED SETTING arduino code -------------> BOARD: " + boardCode );
		infoPanel.setArduinoCodeName("");
		return ;
	    }
	System.out.println("New board code seems fine: " + f.getName() );
	saveArduinoCodeName(boardCode, f.getName());
	ec.setStartable();
    }

    public void handleArduinoCodeNameEvent(int codeIdx)
    {
	infoPanel.setArduinoCodeName(jpref.getArduinoCodeName(codeIdx));
	searduino.setArduinoCodeName(jpref.getArduinoCodeName(codeIdx));
	ec.setStartable();
    }
    
    public static void main(String[] args) {

	final Jearduino jearduino ;
	jearduino = new Jearduino();

	jearduino.setupBoard(jearduino.jpref.getBoard());
	jearduino.getAndUseArduinoCodeName();
	jearduino.showArduinoCodeNameMenu();

	System.out.println("Searduino version: " + jearduino.version);
	System.out.println("Searduino board:   " + jearduino.searduino.getBoardName());

        SwingUtilities.invokeLater(new Runnable() {
		public void run() {
		    jearduino.setVisible(true);
		}
	    });
    }
}
