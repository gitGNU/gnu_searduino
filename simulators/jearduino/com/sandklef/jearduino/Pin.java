package com.sandklef.jearduino;

import javax.swing.JButton;

import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Pin extends JPanel
{
    JButton digValue;
    JLabel  typeLabel;
    JLabel  numberLabel;
    JLabel  modeLabel;

    public Pin(int pin)
    {
	System.out.println("Creating Pin" );

	typeLabel = new JLabel("Digital");
	typeLabel.setVisible(true);

	numberLabel = new JLabel("" + pin);
	numberLabel.setVisible(true);

	modeLabel = new JLabel("OUTPUT");
	modeLabel.setVisible(true);

	digValue = new JButton("0");
	digValue.setVisible(true);

	add(typeLabel);
	add(numberLabel);
	add(modeLabel);
	add(digValue);
    }


    public void setDigitalValue(int val)
    {
	digValue.setText(""+val);
    }

    public void setDigitalMode()
    {
	;
    }

    public void setAnalogMode()
    {
	;
    }

}
