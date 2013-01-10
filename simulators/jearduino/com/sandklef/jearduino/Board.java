package com.sandklef.searduino;

import javax.swing.JButton;
import javax.swing.JPanel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.border.Border;
import javax.swing.BorderFactory;
import javax.swing.JComboBox;
import java.awt.*;

public class Board extends JPanel implements ActionListener
{
    JComboBox boardList ;
    BoardEvent be;

    public Board(BoardEvent e)
    {
	//	super(new GridLayout(1, 1));    
	setBorder(BorderFactory.createTitledBorder("Board"));

	be = e;
	
	String[] boards = { "Uno", "Leonardo", "Mega", "Mega2560" };
	boardList = new JComboBox(boards);
	
	//	boardList.setPreferredSize(new Dimension(100,20));
	boardList.setSelectedIndex(2);
	boardList.addActionListener(this);

	add(boardList);

    }

    public void actionPerformed(ActionEvent e) {
        JComboBox cb = (JComboBox)e.getSource();
        String boardName = (String)cb.getSelectedItem();
	System.out.println("Searduino board:   " + boardName);

	be.handleBoardChoiceEvent(boardName);

    }
    

}