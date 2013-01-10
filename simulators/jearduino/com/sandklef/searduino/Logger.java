package com.sandklef.searduino;

import javax.swing.JTextArea;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import java.awt.Dimension;

class Logger extends JPanel {
    private JTextArea textArea = new JTextArea();

    public Logger(String str) {

	super(new GridLayout(1, 2));    
	setBorder(BorderFactory.createTitledBorder(str));

	add(new JScrollPane(textArea));
	setVisible(true);
    }

    public void addLog(String data) {
	textArea.append(data);
	this.validate();
	textArea.setCaretPosition(textArea.getDocument().getLength());
    }
}
