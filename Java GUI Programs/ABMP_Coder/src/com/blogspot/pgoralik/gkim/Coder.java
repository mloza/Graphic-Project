package com.blogspot.pgoralik.gkim;

import java.io.*;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

/**
 *
 * @author pawel
 */
public class Coder {
    public static void main(String args[]) {
        CoderUI.main(args);
    }
    
    void execute(String bmpPath, String abmpPath, String colorSpace, String filter) {
        String[] arguments = new String[6];
	File jarPath = new File(System.getProperty("java.class.path"));
        
        String os = System.getProperty("os.name");
        if(os.toLowerCase().contains("linux"))
            arguments[0] = jarPath.getParentFile() + "/linux";
        else
        if(os.toLowerCase().contains("mac"))
            arguments[0] = jarPath.getParentFile() + "/mac";
        else
        if(os.toLowerCase().contains("windows"))
            arguments[0] = jarPath.getParentFile() + "/win.exe";
        else
        {
            JOptionPane.showMessageDialog(null, "Nie rozpoznano systemu operacyjnego", "Błąd!", JOptionPane.ERROR_MESSAGE);
            return;
        }
                
                
	arguments[1] = "CODER";
        arguments[2] = bmpPath;
        arguments[3] = abmpPath;
	arguments[4] = colorSpace;
        arguments[5] = filter;
	
        Thread t = new Thread(new CodeRunnable(arguments));
        t.start();
    }
    
    
}

class CodeRunnable implements Runnable {
    CodeRunnable(String[] arguments) {
        this.arguments = arguments;
    }
    
    String[] arguments;
    BufferedReader coderOutput;
    
    @Override
    public void run() {
        try {
            Process p = Runtime.getRuntime().exec(arguments);
            coderOutput = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String output;
            int progress = -5;
            while((output = coderOutput.readLine()) != null)
            {
                // Wypisuje co jeden procent i ma 5 linii zanim zacznie odliczac wiec
                progress++;
                if(progress > 0)
                {
                    final int value = progress;
                    java.awt.EventQueue.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            CoderUI.jProgressBar1.setValue(value);
                        } 
                    });
                    
                }
            }
            
            // Zakonczono tworzenie pliku wyjsciowego
            java.awt.EventQueue.invokeLater(new Runnable() {
                @Override
                public void run() {
                    CoderUI.jProgressBar1.setValue(0);
                    CoderUI.KonwertujButton.setEnabled(true);
                    JOptionPane.showMessageDialog(null, "Konwersja przebiegła pomyślnie", "Sukces!", JOptionPane.INFORMATION_MESSAGE);
                }       
            });
            
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
	}
    }
    
}