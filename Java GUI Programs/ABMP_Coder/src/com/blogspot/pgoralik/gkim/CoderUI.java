package com.blogspot.pgoralik.gkim;

import java.beans.PropertyChangeEvent;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import sun.security.util.Cache;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author pawel
 */
public class CoderUI extends javax.swing.JFrame {
    
    /**
     * Creates new form CoderUI
     */
    public CoderUI() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jFileChooserBMP = new javax.swing.JFileChooser();
        jFileChooserABMP = new javax.swing.JFileChooser();
        KonwertujButton = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        Polozenie = new javax.swing.JLabel();
        ABMPTextField = new javax.swing.JTextField();
        ABMPButton = new javax.swing.JButton();
        PrzestrzenBarw = new javax.swing.JLabel();
        BarwaComboBox = new javax.swing.JComboBox();
        FiltrComboBox = new javax.swing.JComboBox();
        Filtr = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        BMPImage = new javax.swing.JLabel();
        jProgressBar1 = new javax.swing.JProgressBar();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("ABMP Koder - WIEiK PK GKiM Zespół 19");

        KonwertujButton.setText("Konwertuj");
        KonwertujButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                KonwertujButtonActionPerformed(evt);
            }
        });

        jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder("Plik wyjściowy ABMP"));

        Polozenie.setText("Położenie:");

        ABMPButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/com/blogspot/pgoralik/gkim/res/dir.png"))); // NOI18N
        ABMPButton.setToolTipText("");
        ABMPButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ABMPButtonActionPerformed(evt);
            }
        });

        PrzestrzenBarw.setText("Przestrzeń barw");

        BarwaComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "RGB", "HSV", "HSL", "YUV" }));

        FiltrComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Brak", "Różnicowy", "Różnica linii", "Uśredniający", "Paetha" }));

        Filtr.setText("Filtr");

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addComponent(Polozenie)
                        .addGap(3, 3, 3)
                        .addComponent(ABMPTextField)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(ABMPButton, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addComponent(PrzestrzenBarw)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(BarwaComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 69, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 83, Short.MAX_VALUE)
                        .addComponent(Filtr)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(FiltrComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 135, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap())
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(Polozenie)
                    .addComponent(ABMPTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(ABMPButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(FiltrComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(Filtr))
                    .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(BarwaComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(PrzestrzenBarw)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jScrollPane1.setBorder(null);

        BMPImage.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        BMPImage.setText("Kliknij aby wybrać konwertowany plik BMP");
        BMPImage.setBorder(javax.swing.BorderFactory.createTitledBorder("Plik wejściowy BMP"));
        BMPImage.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                BMPImageMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(BMPImage);

        jProgressBar1.setStringPainted(true);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1)
                    .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(jProgressBar1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(KonwertujButton)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 347, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(KonwertujButton)
                    .addComponent(jProgressBar1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(6, 6, 6))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void KonwertujButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_KonwertujButtonActionPerformed
        // TODO add your handling code here:
        KonwertujButton.setEnabled(false);
        
        String filter = (String) FiltrComboBox.getSelectedItem();
        if(filter.equals("Brak"))
            filter = "NONE";
        else
        if(filter.equals("Różnicowy"))
            filter = "DIFFERENTIAL";
        else
        if(filter.equals("Różnica linii"))
            filter = "LINE_DIFFERENCE";
        else
        if(filter.equals("Uśredniający"))
            filter = "AVERAGING";
        else
        if(filter.equals("Paetha"))
            filter = "PAETH";
            
        new Coder().execute(BMPImage.getToolTipText(),
                      ABMPTextField.getText(),
                      (String) BarwaComboBox.getSelectedItem(),
                      filter
                );
    }//GEN-LAST:event_KonwertujButtonActionPerformed

    private void ABMPButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ABMPButtonActionPerformed
        jFileChooserABMP.setFileFilter(new FileNameExtensionFilter("Alternative BMP", "abmp"));
        jFileChooserABMP.setSelectedFile(new File(System.getProperty("java.class.path")));
        String s = ABMPTextField.getText();
        if(s != null)
            jFileChooserABMP.setSelectedFile(new File(s));
        int result = jFileChooserABMP.showSaveDialog(this);
        if(result ==  JFileChooser.APPROVE_OPTION) {
            File abmpPath = jFileChooserABMP.getSelectedFile();
            ABMPTextField.setText(abmpPath.toString());
        }
    }//GEN-LAST:event_ABMPButtonActionPerformed

    private void BMPImageMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_BMPImageMouseClicked
        jFileChooserBMP.setSelectedFile(new File(System.getProperty("java.class.path")));
        jFileChooserBMP.setFileFilter(new FileNameExtensionFilter("BMP", "bmp"));
        int result = jFileChooserBMP.showOpenDialog(this);
        if(result ==  JFileChooser.APPROVE_OPTION) {
            File bmpPath = jFileChooserBMP.getSelectedFile();
            BMPImage.setToolTipText(bmpPath.toString());
            BMPImage.setText(null);
            try {
                BMPImage.setIcon(new ImageIcon(ImageIO.read(bmpPath)));
                String initialPathToOutput = bmpPath.toString().split(".bmp")[0];
                initialPathToOutput += ".abmp";
                ABMPTextField.setText(initialPathToOutput);
                
            } catch (IOException ex) {
                Logger.getLogger(CoderUI.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }//GEN-LAST:event_BMPImageMouseClicked

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /*
         * Set the Nimbus look and feel
         */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /*
         * If Nimbus (introduced in Java SE 6) is not available, stay with the
         * default look and feel. For details see
         * http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(CoderUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(CoderUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(CoderUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(CoderUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /*
         * Create and display the form
         */
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                new CoderUI().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton ABMPButton;
    private javax.swing.JTextField ABMPTextField;
    private javax.swing.JLabel BMPImage;
    private javax.swing.JComboBox BarwaComboBox;
    private javax.swing.JLabel Filtr;
    private javax.swing.JComboBox FiltrComboBox;
    public static javax.swing.JButton KonwertujButton;
    private javax.swing.JLabel Polozenie;
    private javax.swing.JLabel PrzestrzenBarw;
    private javax.swing.JFileChooser jFileChooserABMP;
    private javax.swing.JFileChooser jFileChooserBMP;
    private javax.swing.JPanel jPanel2;
    public static javax.swing.JProgressBar jProgressBar1;
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables
}
