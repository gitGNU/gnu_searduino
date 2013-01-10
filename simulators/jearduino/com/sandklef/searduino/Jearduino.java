package com.sandklef.searduino;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.BoxLayout;
import javax.swing.SwingUtilities;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.FlowLayout;
import javax.swing.JScrollPane;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JLabel;


public class Jearduino extends JFrame implements SearduinoObserver, ExecEvent, PinEvent, BoardEvent, ActionListener {

    Searduino searduino ;
    PinTable pins;
    Logger serial ;
    Logger logger ;
    JPanel infoPanel;
    Container pane; 

    private int nrpins = 0;
    public String version;
    public String boardname;

    JPanel topPanel;
    JPanel controlPanel;
    JPanel pinPanel;
    JPanel logPanel;

    ExecControl ec;
    Board board;


    static int appSizeHeight = 1200;
    static int appSizeWidth  = 1500;

    static int infoSizeHeight = 20;
    static int infoSizeWidth  = 800;

    JLabel infoLabel;

    public Jearduino() {

	pane = getContentPane();

	pane.setLayout(new GridBagLayout());

	GridBagConstraints c;
	c = new GridBagConstraints();

	/* Menu */

	JMenuBar menuBar = new JMenuBar();
	JMenu menu = new JMenu("Board");
	menuBar.add(menu);
	JRadioButtonMenuItem leoItem = new JRadioButtonMenuItem("Leonardo");
	JRadioButtonMenuItem unoItem = new JRadioButtonMenuItem ("Uno");
	JRadioButtonMenuItem megaItem = new JRadioButtonMenuItem ("Mega");
	JRadioButtonMenuItem mega2560Item = new JRadioButtonMenuItem("Mega 2560");

	menu.add(leoItem);
	leoItem.addActionListener(this);

	menu.add(unoItem);
	menu.add(megaItem);
	menu.add(mega2560Item);
	setJMenuBar(menuBar);

	//	add(topmostPanel);

	/*  info */

	infoPanel = new JPanel();
	
	infoLabel = new JLabel("Crappy crap");
	infoPanel.add(infoLabel);
	infoPanel.setMaximumSize(new Dimension(infoSizeWidth, infoSizeHeight ));
	infoPanel.add(infoLabel);

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

	board = new Board(this);
	//	controlPanel.add(board);

	searduino = new Searduino();

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



        setTitle("Jearduino - Searduino's Java frontend for Arduino simulation");

        setLocationRelativeTo(null);
	setDefaultCloseOperation(EXIT_ON_CLOSE);

	

		
	searduino.setWriteTimelimit(0);
	searduino.disableStreamedOutput();

	searduino.registerPinModeCallback(this);
	searduino.registerPinOutCallback(this);
	searduino.registerPinTypeCallback(this);
	searduino.registerLogCallback(this);


    }

    public void setup()
    {
	/*
	JScrollPane pinScroller = new JScrollPane(pins);
	pinScroller.setPreferredSize(new Dimension(1000,1000)); 
	pinScroller.setVisible(true);
	*/

	/*
	pinScroller.revalidate();
	pinScroller.repaint();
	pane.validate();
	*/

	/*
	pinScroller.setMaximumSize(new Dimension(900, 1000));
	pinScroller.setMinimumSize(new Dimension(900, 100));
	*/

	/* 2nd row */


    }


    private void setupBoard(String boardName)
    {

	String ver = searduino.getSearduinoVersion();
	System.out.println("---------------------------------- SETUP BOARD \"" + ver + "\"  0\n"); 
	System.out.println("---------------------------------- SETUP BOARD \"" + boardName + "\"  1\n"); 
	searduino.setBoardName(""+boardName);
	System.out.println("---------------------------------- SETUP BOARD \"" + boardName + "\"  2\n"); 
	nrpins = searduino.getNrOfPins();
	System.out.println("---------------------------------- SETUP BOARD \"" + boardName + "\"  3   pins=\n" + nrpins); 

	version = searduino.getSearduinoVersion();
	boardname = searduino.getBoardName();

	System.out.println("---------------------------------- SETUP BOARD \"" + boardName + "\"  4\n"); 
	pins.setupPins(nrpins);

	for (int i=1;i<nrpins;i++)
	    {
		System.out.println("Pin: " + i  + " " + searduino.getCurrentPinType(i) + "(" +  searduino.getCurrentPinTypeString(i)  + ")\n");
	    }
	
    }


    public void handlePinTypeEvent(int pin, int type)
    {
	pins.setTypeInputPin(pin, type);
	// System.out.println("EVENT: PIN TYPE-------------> JAVA (really) pin[" + pin + "]: type=" + type );
    }
    
    public void handleLogEvent(int level, String msg)
    {
	// System.out.println("EVENT: LOG MESSAGE-------------> " + level + "  " + msg );

	// HESA HESA HESA
	serial.addLog(msg);
    }
    

    public void handleBoardChoiceEvent(String boardName)
    {
	// System.out.println("EVENT: Board choice -------------> BOARD: " + board );
	setupBoard(""+boardName);
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
	    }
	else if (type==ExecControl.EXEC_CONTROL_START)
	    {
		System.out.println("START");
		searduino.startArduinoCode();
	    }
    }

    
    public void actionPerformed(ActionEvent e) {
	System.out.println("MENU");
    }


    public static void main(String[] args) {

	final Jearduino jearduino ;
	jearduino = new Jearduino();
	jearduino.setupBoard("Leonardo");
	//	jearduino.setup();

	jearduino.infoLabel.setText("Searduino: "      + jearduino.version + 
				    "  Board: "        + jearduino.boardname + 
				    "  Arduino code: " + jearduino.searduino.getArduinoCodeName());

	System.out.println("Searduino version: " + jearduino.version);
	System.out.println("Searduino board:   " + jearduino.boardname);

        SwingUtilities.invokeLater(new Runnable() {
		public void run() {
		    jearduino.setVisible(true);
		}
	    });
    }
}
