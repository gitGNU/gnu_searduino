/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013, 2014 Henrik Sandklef 
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
import javax.swing.JTabbedPane;

import com.sandklef.searduino.Searduino;
import com.sandklef.searduino.SearduinoObserver;

import java.io.File;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;


public class Jearduino extends JFrame implements SearduinoObserver, ExecEvent, PinEvent, BoardEvent, FileEvent, DirEvent, InoDirEvent, ArduinoCodeNameEvent, JearduinoEvent {

    Searduino searduino ;
    
    JearduinoPreferences jpref;
    JearduinoMenu        jmenu;
    GridBagConstraints constraints;

    PinTable pins;
    Logger serial ;
    Logger logger ;
    FileLogger fileLogger ;
    LCD    lcd ;
    InfoPanel infoPanel;
    ProjectPanel projectPanel;

    Container topPane; 
    JPanel    pane;
    JTabbedPane tabbedPane;

    private int codeNamesToStore ;
    private int nrpins = 0;
    public String version;
    //    public String boardName;

    JPanel topPanel;
    JPanel controlPanel;
    JPanel pinPanel;
    JPanel logPanel;
    JPanel loggerPanel;
    JPanel fileLoggerPanel;

    ExecControl ec;
    Board       board;
    
    String currentSearduinoProject = "";

    static int appSizeHeight = 700;
    static int appSizeWidth  = 1080;

    static int infoSizeHeight = 20;
    static int infoSizeWidth  = 800;

    public Jearduino() {

	jpref = new JearduinoPreferences();

	codeNamesToStore = jpref.getArduinoCodeNameCount();
	constraints = new GridBagConstraints();
	
	
	pane = new JPanel();

	JTabbedPane tabbedPane = new JTabbedPane();
	topPane = getContentPane();
	topPane.add (tabbedPane);

	pane.setLayout(new GridBagLayout());

	/*  info */

	setSize(appSizeHeight, appSizeWidth);


        controlPanel = new JPanel();
	controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.PAGE_AXIS));

	pinPanel = new JPanel();
	logPanel = new JPanel();

	loggerPanel = new JPanel();
	fileLoggerPanel = new JPanel();


	pinPanel.setVisible(true);
	pinPanel.setLayout(new GridLayout());

	logPanel.setLayout(new BoxLayout(logPanel, BoxLayout.PAGE_AXIS));


	ec = new ExecControl(this);
	controlPanel.add(ec);
	controlPanel.setVisible(true);
	

	jmenu = new JearduinoMenu(this, this, this, this, this, this);
	setJMenuBar(jmenu);

	board = new Board(this);
	
	//	controlPanel.add(board);

	searduino = new Searduino();
	infoPanel = new InfoPanel();
	projectPanel = new ProjectPanel();

	logger    = new Logger( "Log");
	fileLogger = new FileLogger( "File Log");
	serial = new Logger( "Serial");
	lcd    = new LCD( "LCD");

	serial.setMaximumSize(new Dimension(200, 400)); 
	logger.setMaximumSize(new Dimension(200, 400)); 
	fileLogger.setMaximumSize(new Dimension(200, 1000)); 
	lcd.setMaximumSize(new Dimension(200, 400)); 

	serial.setPreferredSize(new Dimension(200, 100)); 
	logger.setPreferredSize(new Dimension(600, 150)); 
	fileLogger.setPreferredSize(new Dimension(600, 400)); 
	lcd.setPreferredSize(new Dimension(200, 100)); 

	logPanel.add(serial);
	logPanel.add(lcd);

	loggerPanel.add(logger);
	fileLoggerPanel.add(fileLogger);

	pins = new PinTable(this, searduino);
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
	searduino.registerLCDCallback(this);

	projectPanel.setArduinoCodeName(searduino.getArduinoCodeName());
	infoPanel.setSearduinoVersion(searduino.getSearduinoVersion());

	tabbedPane.addTab("Control", null, pane,
			  "Main tab");

	tabbedPane.addTab("Log", null, fileLoggerPanel,
			  "Log tab");

	setupSizes();
    }

    public void addLog(String data) {
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-M-dd hh:mm:ss");
	String date = sdf.format(new Date());
	String text =  "[" + date + " jearduino-logger]: " + data + "\n";
	System.out.println("Logger:   " + data);
	System.out.flush();

	logger.addLog(text);
	fileLogger.addLog(text);
    }


    void tailLog() {
	;
    }

    public void setupSizes()
    {
	/*
	logger.setMaximumSize(new Dimension(200, 400));
	logger.setMinimumSize(new Dimension(200, 400));

	serial.setMaximumSize(new Dimension(200, 500));
	serial.setMinimumSize(new Dimension(200, 400));
	*/
	projectPanel.setMinimumSize(new Dimension( 400, 50));
	projectPanel.setMaximumSize(new Dimension( 400, 50));

	infoPanel.setMinimumSize(new Dimension( 400, 50));
	infoPanel.setMaximumSize(new Dimension( 400, 50));

	pinPanel.setMaximumSize(new Dimension(400, 600));
	pinPanel.setMinimumSize(new Dimension(400, 600));

	controlPanel.setMaximumSize(new Dimension(400, 80));
	controlPanel.setMinimumSize(new Dimension(400, 80));

	logger.setMaximumSize(new Dimension(500, 300));
	logger.setMinimumSize(new Dimension(500, 300));

	loggerPanel.setMaximumSize(new Dimension(800, 300));
	loggerPanel.setMinimumSize(new Dimension(800, 300));

	serial.setMaximumSize(new Dimension(300, 300));
	serial.setMinimumSize(new Dimension(300, 300));

	int he = 0;

	/* Row 0 */

	constraints.fill = GridBagConstraints.HORIZONTAL;
	constraints.ipady = he;      //
	constraints.ipadx = 0;      //
	constraints.weightx = 0.0;

	constraints.gridx = 0;
	constraints.gridy = 0;

	constraints.gridwidth = 2;
	System.out.println("projectPanel" + projectPanel + " c " + constraints);
	pane.add(projectPanel, constraints);


	/*  row  1*/

	constraints.fill = GridBagConstraints.HORIZONTAL;
	constraints.ipady = he;      //
	constraints.ipadx = 0;      //
	constraints.weightx = 0.0;

	constraints.gridx = 0;
	constraints.gridy = 1;

	constraints.gridwidth = 2;
	pane.add(controlPanel, constraints);


	/*  row  2*/

	constraints.fill = GridBagConstraints.HORIZONTAL;
	constraints.ipady = he;      //
	constraints.ipadx = 1;      //
	constraints.weightx = 0.0;

	constraints.gridx = 0;
	constraints.gridy = 2;

	constraints.gridwidth = 1;
	pane.add(pinPanel, constraints);

	constraints.fill = GridBagConstraints.HORIZONTAL;
	constraints.ipady = he;      //
	constraints.ipadx = 0;      //
	constraints.weightx = 0.0;

	constraints.gridx = 1;
	constraints.gridy = 2;

	constraints.gridwidth = 1;
	pane.add(logPanel, constraints);



	/* 3 nd row */
	constraints.fill = GridBagConstraints.HORIZONTAL;
	constraints.ipady = 0;      //
	constraints.weightx = 0.0;
	constraints.gridwidth = 2;

	constraints.gridx = 0;
	constraints.gridy = 3;

	pane.add(loggerPanel, constraints);


	constraints.fill = GridBagConstraints.HORIZONTAL;
	constraints.ipady = 0;      //
	constraints.weightx = 0.0;
	constraints.gridwidth = 0;

	constraints.gridx = 0;
	constraints.gridy = 4;
	pane.add(infoPanel, constraints);

    }


    private void setupBoardPins()
    {
	logger.addLog("setupBoardPins() <---------------");

	String bName  = searduino.getBoardName();
	if (bName==null) {
	    return ;
	}
	
	jpref.setBoard(bName);
	infoPanel.setBoardName(bName);
	
	nrpins = searduino.getNrOfPins();

	version = searduino.getSearduinoVersion();

	pins.setupPins();
    }
	
    

    private void setupBoard(String bName)
    {
	String ver = searduino.getSearduinoVersion();
	searduino.setBoardName(bName);

	setupBoardPins();
    }


    public void handlePinTypeEvent(int pin, int type)
    {	
	//	System.out.println("EVENT: PIN TYPE-------------> JAVA (really) pin[" + pin + "]: type=" + type );
	pins.setTypeInputPin(pin, type, true);
    }
    
    public void handleLogEvent(int level, String msg)
    {
	// System.out.println("EVENT: LOG MESSAGE-------------> " + level + "  " + msg );

	// HESA HESA HESA
	serial.addLog(msg);
    }
    
    public void handleLCDEvent(String row1, String row2)
    {
	//	System.out.println("EVENT: LCD MESSAGE-------------> " + row1 + "  " + row2 );
	lcd.setText(row1, row2);
    }


    public void handleBoardChoiceEvent(String bName)
    {
	//	System.out.println("EVENT: Board choice -------------> BOARD: " + bName );
	setupBoard(bName);
    }

    public void handlePinModeEvent(int pin, int mode) {
	if (pin==0) return;

	// HESA HESA HESA
	addLog("EVENT: PIN MODE JAVA (really) pin[" + pin + "]: mode=" + mode );

	// System.out.println("JAVA (really) pin[" + pin + "]: mode=" + mode );
	pins.setMode(pin,mode);
    }

    public void handlePinOutEvent(int pin, int value, int type) {
	// System.out.println("OUT: " + pin + "  VALUE: " + value);
	//	addLog("JAVA (really) out[" + pin + "]: value=" + value +"\n");
	pins.setPinValue(pin, value, type);
    }


    public void inputValueEvent(int pin, int val)
    {
	//	System.out.println("PIN: " + pin + "  VALUE: " + val);
	searduino.setInputPinValue(pin, 
				   val, 
				   pins.getInputPinTypeLocal(pin));
    }

    public void ExecEvent(int type)
    {
	if (type==ExecControl.EXEC_CONTROL_PAUSE)
	    {
		addLog("PAUSE");
		searduino.pauseArduinoCode();
	    }
	else if (type==ExecControl.EXEC_CONTROL_RESUME)
	    {
		addLog("RESUME");
		searduino.resumeArduinoCode();
	    }
	else if (type==ExecControl.EXEC_CONTROL_HALT)
	    {
		addLog("HALT");
		stopArduinoCode(false);
	    }
	else if (type==ExecControl.EXEC_CONTROL_START)
	    {
		addLog("START");
		searduino.startArduinoCode();
	    }
    }

    public void getAndUseArduinoCodeName(String code)
    {
	int ret;
	String codeName;

	stopArduinoCode(true);
	//	waitAWhile(500);

	/* If no code, use latest */
	if (code==null) {
	    codeName = jpref.getArduinoCodeName(1);
	} else {
	    codeName = code;
	}
	
	/* Open file */
	File f = new File(codeName);
	if (f==null) {
	    addLog("Couldn't open Arduino file: " + code);
	    return ;
	}
	
	/* Load code */
	openArduinoFileEvent(f);
    }
    
    
    public void showArduinoCodeNameMenu()
    {
	/* update all menu items from jprefs */

	jmenu.removeCodeItems();
	
	for (int i=0;i<codeNamesToStore;i++) {
	    jmenu.updateCodeItem(i, 
				 jpref.getArduinoCodeName(i));
	}
    }


    /*
     * Method to remove faulty/duplicate entries from jpref
     *
     */ 
    public void removeJPrefFawlty()
    {
	for (int i=0; i<codeNamesToStore;i++) {
	    int next = i+1;
	    if (next==codeNamesToStore) {
		break;
	    }
	    
	    if (i!=codeNamesToStore) {
		File f = new File(jpref.getArduinoCodeName(i));
		boolean exists = f.isFile() && f.canRead() ;
		/*
		 *
		 * Check if duplicate entry or non-existing
		 *
		 */
		if ( 
		    (jpref.getArduinoCodeName(next).length() != 0 ) && 
		    jpref.getArduinoCodeName(i).equals(jpref.getArduinoCodeName(next)) ||
		    (!exists)
		     ) {
		    
		    for (int j=next;j<codeNamesToStore;j++) {
			//System.out.println("        MOVE   : " + (j+1) + " to " + j);  
			jpref.setArduinoCodeName(j,jpref.getArduinoCodeName(j+1));
			
			//System.out.println("        REMOVE : " + (j+1) );  
			jpref.unsetArduinoCodeName(j+1);
		    }
		}
	    }
	}
	
    }
    
    public void saveArduinoCodeName(String canonName, String shortName)
    {
	int ret;
	boolean found=false;

	/* remove duplicate/faulty entries if any */
	removeJPrefFawlty();

	/* Check if current code is already stored */
	for (int i=0; i<codeNamesToStore;i++) {
	    int next = i+1;
	    if (canonName.equals(jpref.getArduinoCodeName(i))) {
		found=true;
	    }
	}

	/* Ok, code is already stored, ... leave */
	if(found) { 
	    //	    System.out.println(" Not adding menu item, since it's already there: " 
	    //		       + canonName); 
	    return ; 
	}

	/* Move all items down one step */
	for (int i=(codeNamesToStore-1);i>-1;i--)
	    {
		/*		System.out.println("UPDATE MENU["+(i+1)+"]  " + 
				jpref.getArduinoCodeName(i) + 
				" prev: [ " + i + "]" + 
				jpref.getArduinoCodeName(i+1));  
		*/
		jpref.setArduinoCodeName(i+1, 
					 jpref.getArduinoCodeName(i));
		
	    }
	/* Store the new one in the first spot */
	jpref.setArduinoCodeName(0, canonName);
	
	/* DIsplay code name in project panel */
	projectPanel.setArduinoCodeName(shortName);

	/* Update menu items */
	showArduinoCodeNameMenu();
    }

    public void setSearduinoProjectInfo(String s) {
	if (s==null) { 
	    s=""; 
	}
	if ( s.equals("") ) { 
	    searduino.closeArduinoCode();
	}
	
	/* Set current project name */
	currentSearduinoProject = s;
	projectPanel.setProjectName(s);
    }
    
    public void handleArduinoFileEvent(File f) {
	
	stopArduinoCode(true);
	//	waitAWhile(500);

	/* Set up pins */
	setupBoardPins();

	openArduinoFileEvent(f);
	setArduinoFileInfo("");
	setSearduinoProjectInfo("");
    }

    public void setArduinoFileInfo(String s) {
	projectPanel.setArduinoCodeName(s);
	projectPanel.setProjectName("");
	setSearduinoProjectInfo(s);
    }

    public void openArduinoFileEvent(File f)
    {
	String boardCode = "";
	int ret = 0;

	addLog("Opening file: " + f);

	setArduinoFileInfo("");

	try {
	    boardCode = f.getCanonicalPath();
	    ret = searduino.setArduinoCodeName(boardCode);
	}
	catch (java.lang.UnsatisfiedLinkError e) {
	    projectPanel.setArduinoCodeName("");
	    addLog("Failed loading Arduino code: " + f);
	    return ;
	}
	catch (java.io.IOException e)  {
	    System.out.println("Uh oh... could not get file name" );
	    addLog("Failed loading Arduino code: " + f.toString());
	}
	
	if (ret != 0 ) {
	    setArduinoFileInfo("");
	    addLog("Failed loading Arduino code: " + f);
	    ec.unsetAll();
	} else {
	    addLog("Loaded Arduino code: " + f);

	    /* Set up pins */
	    setupBoardPins();

	    projectPanel.setProjectName("");
	    setArduinoFileInfo(boardCode);
	    saveArduinoCodeName(boardCode, f.getName());
	    ec.setStartable();
	}
    }

    public void stopArduinoCode(boolean unsetAC) {
	addLog("---> stopArduinoCode");
	searduino.haltArduinoCode();
	
	if (unsetAC) {
	    addLog("---> unset");
	    // Unload arduino code 
	    searduino.closeArduinoCode();
	    addLog("<--- unset");
	}

	addLog("--- stopArduinoCode setup pins");
	setupBoardPins();
	

	addLog("--- stopArduinoCode setup pins done");
	addLog("<--- stopArduinoCode");
    }


    public void waitAWhile(int del) {
	try {
	    Thread.sleep(del);
	} catch (InterruptedException e) {
	    System.out.println("waitAWhile() - exception\n");
	}
    }

    public void handleArduinoCodeNameEvent(int codeIdx)
    {
	addLog("--- 1 handleArduinoCodeNameEvent");
	//waitAWhile(1000) ;
	addLog("---> handleArduinoCodeNameEvent");
	stopArduinoCode(true);
	addLog("---  handleArduinoCodeNameEvent ac stoped");

	//waitAWhile(500) ;
	

       	projectPanel.setArduinoCodeName(jpref.getArduinoCodeName(codeIdx));

	//	waitAWhile(500) ;

	addLog("--- 2 handleArduinoCodeNameEvent");
	projectPanel.setProjectName("");
	//waitAWhile(500) ;
	addLog("--- 3 handleArduinoCodeNameEvent");
	searduino.setArduinoCodeName(jpref.getArduinoCodeName(codeIdx));
	addLog("--- 4 handleArduinoCodeNameEvent");
	ec.setStartable();
	addLog("<--- handleArduinoCodeNameEvent");
    }


    public void execCommand(String cmd) throws IOException
    {
	String commandOutput = null ;
	Process process = null;
	BufferedReader inStream = null;
	String line;
	
	process = Runtime.getRuntime().exec(cmd);
	inStream = new BufferedReader(
				      new InputStreamReader( process.getInputStream() ));  
	commandOutput="Command: " + cmd + "\n";
	while((line=inStream.readLine())!=null){
	    commandOutput += line + "\n";
	}
	addLog(commandOutput);
	System.out.println(" Output from: " + cmd);
	System.out.println(" 	 " + commandOutput);
    }

    public void craeteSearduinoProjectFromIno()
    {
    }
    

    public void handleJearduinoEvent(int i, Object o) {
	if (i==JearduinoEvent.JEARDUINO_EVENT_BUILD_PROJECT) {
	    try {
		if (currentSearduinoProject!=null) {
		    buildSearduinoProject(new File(currentSearduinoProject));
		    
		}
	    }
	    catch (IOException e) {
		addLog("Failed opening file: " + currentSearduinoProject);
	    }
	}
    }

    

    private void getAndUseSearduinoDir(File dir)
    {
	String searduinoDir = System.getProperty("searduino.project.dir") ;
	String shortDir     = dir.getName();
	String libName      = searduinoDir + "/" + shortDir  + "/lib" + shortDir.toLowerCase() + ".so";

	stopArduinoCode(true);
	
	getAndUseArduinoCodeName(libName);
    }

    public void handleSearduinoDirEvent(File dir)
    {
	stopArduinoCode(true);

	getAndUseSearduinoDir(dir);
	setSearduinoProjectInfo(dir.toString());
    }	


    private void buildSearduinoProject(File  dir) throws IOException
    {
	String shortDir     = dir.getName();
	String searduinoDir = System.getProperty("searduino.project.dir") ;
	String buildCommand = System.getProperty("searduino.dir") + "/bin/searduino-builder " ;
	String buildArgs    = searduinoDir + "/" + shortDir;

	buildCommand = buildCommand + " " + buildArgs;

	execCommand(buildCommand);

	getAndUseSearduinoDir(dir);
    }

    private void createSearduinoFromIno(File dir) throws IOException
    {
	String shortDir      = dir.getName();
	String createCommand = System.getProperty("searduino.dir") + "/bin/searduino-builder";
	String createArgs = "--ino-dir " + dir;

	createCommand = createCommand + " " + createArgs;

	execCommand(createCommand);
    }

    

    public void handleInoDirEvent(File dir) {
	try {
	    createSearduinoFromIno(dir);
	    buildSearduinoProject(dir);
	    getAndUseSearduinoDir(dir);
	    setSearduinoProjectInfo(dir.toString());
	} catch(IOException e) {
	    addLog("ERROR when building from INO file");
	    e.printStackTrace();  
	    return;
	}
    }

   public static void main(String[] args) {

	final Jearduino jearduino ;
	jearduino = new Jearduino();
	boolean startDirect = false;
	int nrArgs     = args.length;
	String board   = null;
	String code    = null;
	String project = null;

	for (int i=0; i<nrArgs; i++)  {
	    if (args[i].equals("--board")) {
		if (i+1<nrArgs) 			    {
		    board = args[i+1];
		    i++;
		} else  {
		    System.err.println("Missing args to --board");
		    System.exit(1);
		}
	    }
	    else if (args[i].equals("--arduino-code")) {
		if (i+1<nrArgs) 			    {
		    code = args[i+1];
		    i++;
		} else  {
		    System.err.println("Missing args to --arduino-code");
		    System.exit(1);
		}
	    }
	    else if (args[i].equals("--searduino-project")) {
		if (i+1<nrArgs) 			    {
		    project = args[i+1];
		    i++;
		} else  {
		    System.err.println("Missing args to --arduino-code");
		    System.exit(1);
		}
	    }
	    else if (args[i].equals("--start")) {
		startDirect=true;
	    }
	    else {
		System.err.println("Error when pasing command line '" + args[i] + "'");
		System.exit(1);
	    }
	}


	if ( (project!=null) && (code!=null) ){
	    System.out.println("You can't supply both"+
			       " --arduino-code and --searduino-project arguments");
	    System.exit(1);
	}
	
	if (board==null) {
		jearduino.setupBoard(jearduino.jpref.getBoard());
	} else {
	    jearduino.setupBoard(board);
	}

	if (project!=null) {
	    jearduino.handleSearduinoDirEvent(new File(project));
	} else if (code!=null) {
	    jearduino.getAndUseArduinoCodeName(code);
	} else {
	    /* If no code supplied on cli - use latest */
	    jearduino.getAndUseArduinoCodeName(null);
	}

	jearduino.fileLogger.start();

	/* Update menu items */
	jearduino.showArduinoCodeNameMenu();

	System.out.println("Searduino version: " + jearduino.version);
	System.out.println("Searduino board:   " + jearduino.searduino.getBoardName());

	if (startDirect) {
	    jearduino.ec.sendStart();
	}

        SwingUtilities.invokeLater(new Runnable() {
		public void run() {
		    jearduino.setVisible(true);
		}
	    });
    }
}
