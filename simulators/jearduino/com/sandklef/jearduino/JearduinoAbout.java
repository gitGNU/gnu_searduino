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

import com.sandklef.searduino.Searduino;

import java.awt.GridLayout;

public class JearduinoAbout extends JDialog {
    
    protected JComponent makeAboutPanel() {
        JPanel panel = new JPanel(false);
        JLabel name = new JLabel("Jearduino - GUI front end to Searduino");
        JLabel version = new JLabel("Version: " + 
				   Jearduino.getSearduinoInstance().getSearduinoVersion());
        name.setHorizontalAlignment(JLabel.CENTER);
        version.setHorizontalAlignment(JLabel.CENTER);
        panel.setLayout(new GridLayout(2, 1));
        panel.add(name);
        panel.add(version);
        return panel;
    }

    protected JComponent makeAuthortPanel() {
        JPanel panel = new JPanel(false);


        JLabel filler = new JLabel("Searduino was written by:");
        filler.setHorizontalAlignment(JLabel.CENTER);
        panel.setLayout(new GridLayout(2, 1));
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
        JComponent licensePanel = makeLicensePanel();

	tabbedPane.addTab("About", aboutPanel);
	tabbedPane.addTab("Authors", authorPanel);
	tabbedPane.addTab("Copyright and License", licensePanel);

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


    protected JComponent makeLicensePanel() {
        JPanel panel = new JPanel(false);

	JTextArea infoArea = new JTextArea();
	JTextArea licenseArea = new JTextArea();

        panel.setLayout(new GridLayout(2, 1));
        panel.add(infoArea);
        panel.add(licenseArea);

	JScrollPane scrollPane = new JScrollPane(licenseArea); 
	licenseArea.setEditable(false);
	infoArea.setEditable(false);
        panel.add(infoArea);
        panel.add(licenseArea);

        infoArea.append("Searduino is currently copyrighted to the authors\n");
        infoArea.append(" * see individual files for more information\n");
	infoArea.append("Searduino is Free Software - software that gives you 4 freedoms:\n");
	infoArea.append(" * The freedom to run the program, for any purpose (freedom 0).\n");
	infoArea.append(" * The freedom to study how the program works, and change it so it does your computing as you wish (freedom 1).\n");
	infoArea.append(" * The freedom to redistribute copies so you can help your neighbor (freedom 2).\n");
	infoArea.append(" * The freedom to distribute copies of your modified versions to others (freedom 3).\n");
	infoArea.append("\nRead more about free software at http://www.gnu.org/philosophy/free-sw.html\n\n");
	
	licenseArea.append("Searduino is licensed under GPLv3\n");
	licenseArea.append(" See http://www.gnu.org/licenses/gpl-3.0.txt for more iformation\n");
	
        return panel;
    }

}