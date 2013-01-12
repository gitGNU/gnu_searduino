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

import javax.swing.border.Border;
import javax.swing.border.LineBorder;
import javax.swing.*;
import java.awt.Graphics;
import javax.swing.JScrollPane;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;

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
    private int nrPins ;
    
    private final int TABLE_NUMBER_POS  = 0;
    private final int TABLE_TYPE_POS    = 1;
    private final int TABLE_MODE_POS    = 2;
    private final int TABLE_INPUT_POS   = 3;
    private final int TABLE_OUTPUT_POS  = 4;

    private int[] pinMode;
    private int[] pinType;

    private PinEvent pe;

    public PinTable(PinEvent e)
    {
	pe = e ;
	setBorder(BorderFactory.createTitledBorder("Pins"));
    }

    public void setTypeInputPin(int pin, int type)
    {
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
	else 
	    {
		System.out.println("\n\n\n\n\tERROR - we should not be here\n\n\n\n");
		
	    }
    }
    
    public void setAnalogInputPin(int pin)
    {
	JSpinner spinner ;
	SpinnerModel model =
	    new SpinnerNumberModel(0, 
				   0,
				   1024,
				   10);        
	spinner = new JSpinner(model);
	spinner.addChangeListener(this);

	System.out.println("ADD ANALOG PIN AT:  " + pin);

	if (pins[pin][TABLE_INPUT_POS]!=null)
	    {
		System.out.println("REMOVE ANALOG PIN AT:  " + (pin*5+TABLE_INPUT_POS+1));
		this.remove(pin*5+TABLE_INPUT_POS+1);
	    }
	
	System.out.println("ADD ANALOG PIN AT: " + pin + " " + (pin*5+TABLE_INPUT_POS+1));
	this.add(spinner, pin*5+TABLE_INPUT_POS+1);
	pins[pin][TABLE_INPUT_POS]=spinner;
	((JLabel)pins[pin][TABLE_TYPE_POS]).setText("Analog");
	pinType[pin]=Searduino.SEARDUINO_PINTYPE_ANALOG;
    }

    
    public void setDigitalInputPin(int pin)
    {

	if (pins==null)
	    {
		return ;
	    }

	JToggleButton input;
	input = new JToggleButton("");
	input.addActionListener(this);
	input.setEnabled(true);
	
	input.setVisible(true);


	
	System.out.println("SET DIGITAL PIN AT: " + pin);
	System.out.println("SET DIGITAL PIN ON: " + pins);
	System.out.println("SET DIGITAL PIN   : " + pins[pin][TABLE_INPUT_POS]);
	

	if (pins[pin][TABLE_INPUT_POS]!=null)
	    {
		this.remove(pin*5+TABLE_INPUT_POS+1);
	    }
	System.out.println("SET DIGITAL PIN AT: " + pin + " " + (pin*5+TABLE_INPUT_POS+1));
	this.add(input, pin*5+TABLE_INPUT_POS+1);
	pins[pin][TABLE_INPUT_POS]=input;
	JLabel lab = ((JLabel)pins[pin][TABLE_TYPE_POS]);
	if (lab!=null)
	    {
		lab.setText("Digital");
	    }
	pinType[pin]=Searduino.SEARDUINO_PINTYPE_DIGITAL;
    }


    public void setPwmPin(int pin)
    {
	JLabel input;

	input = new JLabel("");
	input.setEnabled(true);	
	input.setVisible(true);

	if (pins[pin][TABLE_INPUT_POS]!=null)
	    {
		this.remove(pin*5+TABLE_INPUT_POS+1);
	    }

	System.out.println("ADD PWN PIN AT: " + pin + " " + (pin*5+TABLE_OUTPUT_POS+1));

	this.add(input, pin*5+TABLE_INPUT_POS+1);

	((JLabel)pins[pin][TABLE_MODE_POS]).setText("Output");
	pins[pin][TABLE_INPUT_POS]=input;
	((JLabel)pins[pin][TABLE_TYPE_POS]).setText("PWM");
	pinType[pin]=Searduino.SEARDUINO_PINTYPE_PWM;
    }


    public void actionPerformed(ActionEvent e) {
	
	for (char i=1; i<nrPins;i++)
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


    public void stateChanged(ChangeEvent e) {
	 
	for (char i=1; i<nrPins;i++)
	    {
		if (e.getSource() == pins[i][TABLE_INPUT_POS]) 
		    {
			Character val = (Character)((JSpinner)pins[i][TABLE_INPUT_POS]).getValue();
			pe.inputValueEvent(i, val);
		    }  
	    }  
    }


    public int getInputPinTypeLocal(int pin)
    {
	return pinType[pin];
    }

    public void setPinValue(int pin, int val, int type)
    {
	// System.out.println("PIN VALUE: " + pin + "  VALUE: " + val);
	((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(true);
	((JLabel)pins[pin][TABLE_OUTPUT_POS]).setText(""+val);
    }

    public void setPinType(int pin, int type)
    {
	System.out.println("PIN: " + pin + "  TYPE: " + type);
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
	System.out.println("SET PIN " + pin + " (" +  pinType[pin] + ")  to: " + mode);
	
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
	    else
		{
		    ((JSpinner)pins[pin][TABLE_INPUT_POS]).setVisible(true);
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
	    else
		{
		    ((JSpinner)pins[pin][TABLE_INPUT_POS]).setVisible(false);
		}
	    ((JLabel)pins[pin][TABLE_OUTPUT_POS]).setVisible(true);
	    
	}
    }

    public void setupPins(int nrOfPins)
    {
	nrPins = nrOfPins;
	System.out.println("=========================== Creating PinTable (" + nrOfPins +") 1"  );
	this.setLayout(new GridLayout(nrPins, 5));
	System.out.println("=========================== Creating PinTable (" + nrOfPins +") 2" );

	removeAll();
	System.out.println("=========================== Creating PinTable (" + nrOfPins +") 3" );

	pinMode = new int[nrPins];
	pinType = new int[nrPins];
	pins = new Object[nrPins][5] ;
	
	System.out.println("=========================== Creating PinTable (" + nrOfPins +") 4" );
	add(new JLabel("Pin"));

	add(new JLabel("Type"));

	add(new JLabel("Mode"));

	add(new JLabel("Ouput"));

	add(new JLabel("Input"));

	for (int i=1;i<nrPins;i++)
	    {
		JLabel digValue;
		JLabel typeLabel;
		JLabel numberLabel;
		JLabel modeLabel;

		pinMode[i] = 0;
		pinType[i] = 0;

		numberLabel = new JLabel("" + i);
		numberLabel.setVisible(true);
		add(numberLabel);
		
		typeLabel = new JLabel("");
		typeLabel.setVisible(true);
		add(typeLabel);
		
		modeLabel = new JLabel("INPUT");
		modeLabel.setVisible(true);
		add(modeLabel);
		
		digValue = new JLabel("0");
		digValue.setVisible(false);
		add(digValue);
		
		pins[i][TABLE_TYPE_POS]=typeLabel;
		pins[i][TABLE_NUMBER_POS]=numberLabel;
		pins[i][TABLE_MODE_POS]=modeLabel;
		pins[i][TABLE_OUTPUT_POS]=digValue;

		/* UNO
		   Digital pins: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
		   PWM pins:     3, 6, 9, 10, 11, 
		   Analog pins:  14 (A0), 15 (A1), 16 (A2), 17 (A3), 18 (A4), 19 (A5), 
		*/
	
		if (i < 31)
		    {
			setDigitalInputPin(i);
		    }
		else if (i > 14)
		    {
			setAnalogInputPin(i);
		    }
		else
		    {
			setPwmPin(i);
		    }
		  ((JLabel)pins[i][TABLE_TYPE_POS]).setMaximumSize(new Dimension(100, 10));
		  ((JLabel)pins[i][TABLE_TYPE_POS]).setMinimumSize(new Dimension(100, 10));
	    }


    }
    
}