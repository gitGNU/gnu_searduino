package com.sandklef.searduino;

import javax.swing.JButton;
import javax.swing.JPanel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.border.Border;
import javax.swing.BorderFactory;
import java.awt.GridLayout;
import java.awt.Dimension;

public class ExecControl extends JPanel implements ActionListener
{
    private JButton pause; 
    private JButton resume;
    private JButton halt  ;
    private JButton start  ;

    public static final int EXEC_CONTROL_START  = 1;
    public static final int EXEC_CONTROL_PAUSE  = 2;
    public static final int EXEC_CONTROL_RESUME = 3;
    public static final int EXEC_CONTROL_HALT   = 4;

    private ExecEvent ee ; 

    public ExecControl(ExecEvent e)
    {
	
	//	super(new GridLayout(1, 4));    
	setBorder(BorderFactory.createTitledBorder("Execution"));
	
	// setMaximumSize(new Dimension(500, 200));
	// setMinimumSize(new Dimension(200, 50));

	start  = new JButton("Start");
	//        start.setPreferredSize(new Dimension(80, 20));

	pause  = new JButton("Pause");
        //pause.setPreferredSize(new Dimension(80, 20));

	resume = new JButton("Resume");
        //resume.setPreferredSize(new Dimension(80, 20));

	halt   = new JButton("Stop");
        //halt.setPreferredSize(new Dimension(70, 20));

	ee = e;

	add(start);
	add(pause);
	add(resume);
	add(halt);
	
	start.addActionListener(this);
	pause.addActionListener(this);
	resume.addActionListener(this);
	halt.addActionListener(this);

	start.setEnabled(true);
	pause.setEnabled(false);
	resume.setEnabled(false);
	halt.setEnabled(false);
    }



    public void actionPerformed(ActionEvent e) {
	int type = 0 ; 

	System.out.println("action");

	if (e.getSource() == pause) {
	    start.setEnabled(false);
	    pause.setEnabled(false);
	    resume.setEnabled(true);
	    halt.setEnabled(true);
	    type = EXEC_CONTROL_PAUSE;
	}
	else if (e.getSource() == resume) {
	    type = EXEC_CONTROL_RESUME;
	    start.setEnabled(false);
	    pause.setEnabled(true);
	    resume.setEnabled(false);
	    halt.setEnabled(true);
	}
	else if (e.getSource() == halt) {
	    type = EXEC_CONTROL_HALT;
	    start.setEnabled(true);
	    pause.setEnabled(false);
	    resume.setEnabled(false);
	    halt.setEnabled(false);
	}
	else if (e.getSource() == start) {
	    type = EXEC_CONTROL_START;
	    start.setEnabled(false);
	    pause.setEnabled(true);
	    resume.setEnabled(false);
	    halt.setEnabled(true);
	}

	System.out.println("action sending");

	ee.ExecEvent(type);

    }
}