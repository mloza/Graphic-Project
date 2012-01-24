package com.blogspot.pgoralik.gkim;

import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;


/**
 *
 * @author pawel
 */
public class Decoder {
    public static void main(String args[]) {
        DecoderUI.main(args);
    }
    
    void execute(String abmpPath, String bmpPath) {
        String[] arguments = new String[4];
	File jarPath = new File(System.getProperty("java.class.path"));
        
        String os = System.getProperty("os.name");
        if(os.toLowerCase().contains("linux"))
            arguments[0] = jarPath.getParentFile() + "/linux";
        else
        if(os.toLowerCase().contains("mac"))
            arguments[0] = jarPath.getParentFile() + "/mac";
        else
        if(os.toLowerCase().contains("windows"))
            arguments[0] = jarPath.getParentFile() + "/win";
        else
        {
            JOptionPane.showMessageDialog(null, "Nie rozpoznano systemu operacyjnego", "Błąd!", JOptionPane.ERROR_MESSAGE);
            return;
        }
                
                
	arguments[1] = "DECODER";
        arguments[2] = abmpPath;
        arguments[3] = bmpPath;
	
        Thread t = new Thread(new DecodeRunnable(arguments));
        t.start();
    }
    
    
}
class DecodeRunnable implements Runnable {
    DecodeRunnable(String[] arguments) {
        this.arguments = arguments;
    }
    
    String[] arguments;
    BufferedReader decoderOutput;
    
    @Override
    public void run() {
        try {
            Process p = Runtime.getRuntime().exec(arguments);
            decoderOutput = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String output;
            int progress = -6;
            while((output = decoderOutput.readLine()) != null)
            {
                System.out.println(output);
                // Wypisuje co jeden procent i ma 5 linii zanim zacznie odliczac wiec
                progress++;
                if(progress > 0)
                {
                    final int value = progress;
                    java.awt.EventQueue.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            DecoderUI.jProgressBar1.setValue(value);
                        } 
                    });
                    
                }
            }
            
            // Zakonczono tworzenie pliku wyjsciowego
            java.awt.EventQueue.invokeLater(new Runnable() {
                @Override
                public void run() {
                    DecoderUI.jProgressBar1.setValue(0);
                    DecoderUI.DekodujButton.setEnabled(true);
                    try {
                        DecoderUI.BMPImage.setIcon(new ImageIcon(ImageIO.read(new File(arguments[3]))));
                    } catch (IOException ex) {
                        Logger.getLogger(DecodeRunnable.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    JOptionPane.showMessageDialog(null, "Dekodowanie przebiegło pomyślnie. Obraz został także wyświetlony.", "Sukces!", JOptionPane.INFORMATION_MESSAGE);
                }       
            });
            
        } catch (IOException e) {
            String msg = "Nie można uruchomić programu\n\r";
            Pattern p = Pattern.compile("\".*\"");
            Matcher m = p.matcher(e.getMessage());
            m.find();
            msg += e.getMessage().substring(m.start(), m.end() - 1) + "\n\r";
            msg += "Upewnij się, że pod powyższą lokalizacją znajduje się odpowiedni plik.";
                    
            JOptionPane.showMessageDialog(null, msg, "Błąd!", JOptionPane.ERROR_MESSAGE);
	}
    }
    
}