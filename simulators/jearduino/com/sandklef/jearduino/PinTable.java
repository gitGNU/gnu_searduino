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
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JTable;
import javax.swing.JLabel;
import java.awt.Dimension;
import java.awt.*;
import java.awt.Color;
import javax.swing.JComboBox;

import javax.swing.JScrollPane;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;
import javax.swing.*;
import java.awt.Graphics;
import javax.swing.JScrollPane;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;

import java.util.ArrayList;

import com.sandklef.searduino.Searduino;

public class PinTable extends JPanel implements ActionListener, ChangeListener
{
    //    public Pin[] pins;
    private Object[][] pins;

    String[] columnNames = {"Number",
			    "Type",
			    "Mode",
			    "Input",
			    "Value"};

    private JPanel panel;
    JScrollPane scrollPane;

    private final int TABLE_NUMBER_POS  = 0;
    private final int TABLE_TYPE_POS    = 1;
    private final int TABLE_MODE_POS    = 2;
    private final int TABLE_INPUT_POS   = 3;
    private final int TABLE_OUTPUT_POS  = 4;

    Searduino searduino;
    JearduinoState jState;
    private int[] pinMode;
    private int[] pinType;

    private PinEvent pe;

    public PinTable(PinEvent e, JearduinoState js, Searduino searduinoIn)    {
	super(new GridLayout(2, 1));    
	setBorder(BorderFactory.createTitledBorder("einar"));
	searduino = searduinoIn;
	panel = this; 
	    //new JPanel(new GridBagLayout());
	//scrollPane = new JScrollPane(panel, ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	//scrollPane.setPreferredSize(new Dimension(600, 600));

	//	add(panel);
	pe = e ;
	jState=js;
	setBorder(BorderFactory.createTitledBorder("Pins"));
    }

    private int getItemPosFromCombo(JComboBox cb, String item) {
	for (int i=0;i<cb.getItemCount();i++) {
	    if (cb.getItemAt(i).equals(item)) {
		return i;
	    }
	}
	return 0;
    }

    public void setTypeInputPin(int pin, int type, boolean fromArduino)
    {
	if (pins==null) {
	    System.out.println("setTypeInputPin() .... pins not created  yet, bailing out");
	    return ;
	}
	
	if (!searduino.hasGenericPinTypeBoolean(pin, type)) {
	    System.out.println("\n\n *** ERROR: Can not set type " +
				   searduino.getPinType(type) + 
			       " on pin " + pin + " \n\n" );
	    return ;
	}

	//	System.out.println("Pin " + pin + ", items: " + ((JComboBox)pins[pin][TABLE_TYPE_POS]).getItemCount());

	/* 
	 * Change pin type called from Arduino code
	 *   update combobox
	 */
	if (fromArduino)    {
	    // System.out.println("setTypeInputPin() .... ARDUINO");
	    if (type==Searduino.SEARDUINO_PINTYPE_DIGITAL) {
		JComboBox cb = (JComboBox)pins[pin][TABLE_TYPE_POS];
		int pos = getItemPosFromCombo(cb, 
					      searduino.getPinType(Searduino.SEARDUINO_PINTYPE_DIGITAL));
		cb.setSelectedIndex(pos);
	    } else if (type==Searduino.SEARDUINO_PINTYPE_ANALOG) {
		JComboBox cb = (JComboBox)pins[pin][TABLE_TYPE_POS];
		int pos = getItemPosFromCombo(cb, 
					      searduino.getPinType(Searduino.SEARDUINO_PINTYPE_ANALOG));
		cb.setSelectedIndex(pos);
	    } else if (type==Searduino.SEARDUINO_PINTYPE_PWM) {
		JComboBox cb = (JComboBox)pins[pin][TABLE_TYPE_POS];
		int pos = getItemPosFromCombo(cb, 
					      searduino.getPinType(Searduino.SEARDUINO_PINTYPE_PWM));
		cb.setSelectedIndex(pos);
	    }
	}
	/* 
	 * Change pin type called from the GUI (simulator)
	 *   do NOT update combobox
	 */
 	else {
	    // System.out.println("setTypeInputPin() .... GUI");
		if (type==Searduino.SEARDUINO_PINTYPE_DIGITAL)
		    {
			setDigitalInputPin(pin);
		    }
		else if (type==Searduino.SEARDUINO_PINTYPE_ANALOG)
		    {
			setAnalogInputPin(pin);
		    }
		else if (type==Searduino.SEARDUINO_PINTYPE_PWM)
		    {
			setPwmPin(pin);
		    }
		panel.revalidate();
		panel.repaint();
	    }
    }
	
    public void setAnalogInputPin(int pin)
    {

	if (pins==null)
	    {
		return ;
	    }
	JSpinner spinner ;
	SpinnerModel model =
	    new SpinnerNumberModel(0, 
				   0,
				   1024,
				   10);        

	spinner = new JSpinner(model);
	spinner.setVisible(true);
	spinner.setEnabled(true);
	spinner.addChangeListener(this);

	GridBagLayout layout = (GridBagLayout)panel.getLayout();
	GridBagConstraints c = (GridBagConstraints) layout.getConstraints(panel);

	if (pins[pin][TABLE_INPUT_POS]!=null)
	    {
		remove((Component)pins[pin][TABLE_INPUT_POS]);
	    }
	try {
	    Thread.sleep(10);
	} catch (InterruptedException e) {
	    System.out.println(e);

	}

	c.gridx = 4;
	c.gridy = pin+1;	
	panel.add(spinner, c);
	((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(false);
	pins[pin][TABLE_INPUT_POS]=spinner;
	pinType[pin]=Searduino.SEARDUINO_PINTYPE_ANALOG;
	spinner.repaint();
    }

    
    public void setDigitalInputPin(int pin)
    {
	if (pins==null) {
	    return ;
	}

	    System.out.println("setDigitalInputPin()");
	
	JToggleButton input;
	input = new JToggleButton("");
	input.addActionListener(this);
	input.setEnabled(true);
	input.setVisible(true);

	GridBagLayout layout = (GridBagLayout)panel.getLayout();
	GridBagConstraints c = (GridBagConstraints) layout.getConstraints(panel);

	if (pins[pin][TABLE_INPUT_POS]!=null)
	    {
		remove((Component)pins[pin][TABLE_INPUT_POS]);
	    }
	c.gridx = 4;
	c.gridy = pin+1;	
	panel.add(input, c);

	((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(false);
	pins[pin][TABLE_INPUT_POS]=input;
	pinType[pin]=Searduino.SEARDUINO_PINTYPE_DIGITAL;
    }


    public void setPwmPin(int pin)
    {
	JLabel input;
	int pos = pin*5+TABLE_INPUT_POS+1;

	input = new JLabel("");
	input.setEnabled(true);	
	input.setVisible(true);

	if (pins[pin][TABLE_INPUT_POS]!=null)
	    {
		remove((Component)pins[pin][TABLE_INPUT_POS]);
	    }

	GridBagLayout layout = (GridBagLayout)panel.getLayout();
	GridBagConstraints c = (GridBagConstraints) layout.getConstraints(panel);

	panel.add(input, c);

	((JLabel)pins[pin][TABLE_MODE_POS]).setText("Output");
	pins[pin][TABLE_INPUT_POS]=input;
	((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(false);
	//	((JLabel)pins[pin][TABLE_TYPE_POS]).setText("PWM");
	pinType[pin]=Searduino.SEARDUINO_PINTYPE_PWM;
    }


    private void handlePinActionPerformed(ActionEvent e) 
    {
	for (char i=0; i<jState.getBoardPins();i++)
	    {
		if (e.getSource() == pins[i][TABLE_INPUT_POS]) 
		    {
			if (((JToggleButton)pins[i][TABLE_INPUT_POS]).isSelected())
			    {
				pe.inputValueEvent(i, (char)1);
			    }
			else
			    {
					pe.inputValueEvent(i, (char)0);
			    }
		    }  
	    }  
    }

    
    public void actionPerformed(ActionEvent e) 
    {
	String command = e.getActionCommand();

	if (command.equals("comboBoxChanged")) {
	    JComboBox cb   = (JComboBox)e.getSource();
	    String pinType = (String)cb.getSelectedItem();
	    int pinTypeInt = Searduino.getPinType(pinType);
	    //		System.out.println("comboBoxChanged::: " + pinType + " " + pinTypeInt);
	    
	    for (int i=0;i<jState.getBoardPins();i++) {
		//			System.out.println("  Trying to find cbox at " + i );
		
		if (pins[i][TABLE_TYPE_POS]==cb) {
		    //				System.out.println("   ---> found one at " + i + "  will change it to " + pinType + " / " + pinTypeInt );
		    setTypeInputPin(i, pinTypeInt, false);
		}
	    }
	} else {
	    handlePinActionPerformed(e);
	}
    }


    public void stateChanged(ChangeEvent e) {
	 
	for (int i=0; i<jState.getBoardPins();i++)
	    {
		if (e.getSource() == pins[i][TABLE_INPUT_POS]) 
		    {
			pe.inputValueEvent(i, (Integer)((JSpinner)pins[i][TABLE_INPUT_POS]).getValue());
		    }  
	    }  
    }


    public int getInputPinTypeLocal(int pin)
    {
	return pinType[pin];
    }

    public void setPinValue(int pin, int val, int type)
    {
	JLabel label = (JLabel)pins[pin][TABLE_OUTPUT_POS];
	//	System.out.println("PIN VALUE: " + pin + "  VALUE: " + val + " TYPE: " + type);
	label.setVisible(true);
	label.setText(""+val);
	if ( type == Searduino.SEARDUINO_PINTYPE_DIGITAL  ) 
	    {
		if (val==0) 
		    {
			label.setForeground(Color.green);
		    }
		else 
		    {
			label.setForeground(Color.red);
		    }
	    }
	else 
	    {
		label.setForeground(Color.black);
	    }
    }
    
    public void setPinTypeOBSOLETE(int pin, int type)
    {
	//	System.out.println("PIN: " + pin + "  TYPE: " + type);
	//	((JLabel)pins[pin][TABLE_TYPE_POS]).setVisible(true);
	//((JLabel)pins[pin][TABLE_TYPE_POS]).setText(""+type);
    }

    public void setInputMode(int pin)
    {
	setMode(pin, 0);
    }

    public void setOutputMode(int pin)
    {
	setMode(pin, 1);
    }

    public void setMode(int pin, int mode)
    {
	//	System.out.println("---->SET PIN " + pin + " (" +  pinType[pin] + ")  to: " + mode);
	System.out.flush();
	/* INPUT */
	if (mode==0) {
	    /* Set input */
	    ((JLabel)pins[pin][TABLE_MODE_POS]).setText("INPUT");
	    pinMode[pin] = 0;

	    /* Unset output */
	    if ( pinType[pin] == Searduino.SEARDUINO_PINTYPE_DIGITAL )
		{
		    ((JToggleButton)pins[pin][TABLE_INPUT_POS]).setVisible(true);
		}
	    else if ( pinType[pin] == Searduino.SEARDUINO_PINTYPE_ANALOG )
		{
		    ((JSpinner)pins[pin][TABLE_INPUT_POS]).setVisible(true);
		}
	    else
		{
		    System.out.println("ERROR ---- SET PIN " + pin + " (" +  pinType[pin] + ")  to: " + mode);		    
		}
	    ((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(false);
	}

	/* OUTPUT */
	else {
	    
	    /* Set input */
	    ((JLabel)pins[pin][TABLE_MODE_POS]).setText("OUTPUT");
	    pinMode[pin] = 1;

	    /* Unset output */
	    if ( pinType[pin] == Searduino.SEARDUINO_PINTYPE_DIGITAL )
		{
		    ((JToggleButton)pins[pin][TABLE_INPUT_POS]).setVisible(false);
		}
	    else if ( pinType[pin] == Searduino.SEARDUINO_PINTYPE_ANALOG )
		{
		    ((JSpinner)pins[pin][TABLE_INPUT_POS]).setVisible(true);
		}
	    else
		{
		    System.out.println("ERROR ---- SET PIN " + pin + " (" +  pinType[pin] + ")  to: " + mode);		    
		}
	    ((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(true);
	    
	}
	//	System.out.println("<---- SET PIN " + pin + " (" +  pinType[pin] + ")  to: " + mode);
    }

    private void addTypeOnPin(ArrayList a, int pin, int type)
    {
	if (searduino.hasGenericPinTypeBoolean(pin, type))
	    {
		//		System.out.println("=========================== Adding type " + Searduino.getPinType(type) + " to pin " + pin);
		a.add(Searduino.getPinType(type));
	    }
    }

    public void setupPinTypes()
    {
	int nrPins = jState.getBoardPins();
	for (int i=0;i<nrPins;i++) {
	    setTypeInputPin(i, searduino.getCurrentPinType(i), false);
	}

    }

    public void setupPins()
    {

	//	jState.setBoardPins(jState.getBoardPins());
	int nrPins = jState.getBoardPins();

	/* +1 for the header row */
	panel.setLayout(new GridBagLayout());
	//	this.setLayout(new GridLayout(nrPins, 4));
	GridBagConstraints c = new GridBagConstraints();

	removeAll();

	pinMode = new int[nrPins];
	pinType = new int[nrPins];
	pins    = new Object[nrPins][5] ;
	
	//	c.fill = GridBagConstraints.HORIZONTAL;
	c.gridx = 0;
	c.gridy = 0;

	panel.add(new JLabel("Pin"), c);

	c.gridx = 1;
	panel.add(new JLabel("Type"), c);

	c.gridx = 2;
	panel.add(new JLabel("Mode"), c);

	c.gridx = 3;
	panel.add(new JLabel("Ouput"), c);

	c.gridx = 4;
	panel.add(new JLabel("Input"), c);

	for (int i=0;i<nrPins;i++) {
	    JLabel digValue;
	    JLabel numberLabel;
	    JLabel modeLabel;
	    JLabel inputLabel;
	    
	    /*
	      pinMode[i] = 0;
	      pinType[i] = 0;
	    */
	    numberLabel = new JLabel("" + i);
	    numberLabel.setVisible(true);
	    
	    JComboBox typeCombo ;
	    ArrayList<String> myTypes = new ArrayList<String>();
	    addTypeOnPin(myTypes, i, Searduino.SEARDUINO_PINTYPE_DIGITAL);
	    addTypeOnPin(myTypes, i, Searduino.SEARDUINO_PINTYPE_PWM);
	    addTypeOnPin(myTypes, i, Searduino.SEARDUINO_PINTYPE_ANALOG);
	    typeCombo = new JComboBox(myTypes.toArray());
	    //new JComboBox();
	    //new JComboBox(myTypes.toArray());
	    typeCombo.setVisible(true);
	    typeCombo.addActionListener(this);
	    
	    modeLabel = new JLabel("INPUT");
	    modeLabel.setVisible(true);
	    
	    digValue = new JLabel("0");
	    digValue.setVisible(false);
	    
	    inputLabel = new JLabel("<none>");
	    
	    c.gridy = i+1;
	    /* 1 Pin */
	    c.gridx = 0;
	    panel.add(numberLabel, c);
	    /* 2 Type */
	    c.gridx = 1;
	    panel.add(typeCombo, c);
	    /* 3 Mode */
	    c.gridx = 2;
	    panel.add(modeLabel, c);
	    /* 4 Output */
	    c.gridx = 3;
	    panel.add(digValue, c);
	    /* 5 Input */
	    c.gridx = 4;
	    panel.add(inputLabel, c);
	    
	    pins[i][TABLE_NUMBER_POS] = numberLabel;
	    pins[i][TABLE_TYPE_POS]   = typeCombo;
	    pins[i][TABLE_MODE_POS]   = modeLabel;
	    pins[i][TABLE_OUTPUT_POS] = digValue;
	    pins[i][TABLE_INPUT_POS]  = inputLabel;
	    
	    // done in setupPinType
	    //setTypeInputPin(i, searduino.getCurrentPinType(i), false);
	}
	
    }
    
}