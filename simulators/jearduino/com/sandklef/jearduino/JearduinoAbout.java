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

import javax.swing.JDialog;
import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextArea;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import java.awt.Dimension;

import javax.swing.JComponent;
import javax.swing.JTabbedPane;
   
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.awt.GridLayout;

public class JearduinoAbout extends JDialog {
    
    protected JComponent makeAboutPanel() {
        JPanel panel = new JPanel(false);
        JLabel filler = new JLabel("Jearduino - GUI front end to Searduino");
        filler.setHorizontalAlignment(JLabel.CENTER);
        panel.setLayout(new GridLayout(1, 1));
        panel.add(filler);
        return panel;
    }

    protected JComponent makeAuthortPanel() {
        JPanel panel = new JPanel(false);


        JLabel filler = new JLabel("Searduino was written by:");
        filler.setHorizontalAlignment(JLabel.CENTER);
        panel.setLayout(new GridLayout(1, 2));
        panel.add(filler);

	JTextArea textArea = new JTextArea(5, 20);
	JScrollPane scrollPane = new JScrollPane(textArea); 
	textArea.setEditable(false);
        panel.add(textArea);

	textArea.append("Henrik Sandklef\nViktor Green\nPeter Myllykoski" );

        return panel;
    }

    public JearduinoAbout()
    {        

	JTabbedPane tabbedPane = new JTabbedPane();

        JComponent aboutPanel = makeAboutPanel();
        JComponent authorPanel = makeAuthortPanel();

	tabbedPane.addTab("About", aboutPanel);
	tabbedPane.addTab("Authors", authorPanel);

	//	add(tabbedPane);

	JLabel title = new JLabel ("Searduino");

	getContentPane().add(tabbedPane, "Center");

	JPanel p2 = new JPanel();
	JButton ok = new JButton("Ok");

	p2.add(ok);
	getContentPane().add(p2, "South");

	ok.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent evt) {
		    setVisible(false);
		}
	    });

	setMinimumSize(new Dimension(400, 400));
    }
}