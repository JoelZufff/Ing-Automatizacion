package Containers;
//import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class MyFrame extends JFrame 
{	
	MyFrame()
	{
		// Configuracion de panel principal
		setTitle("MyFrame");
		setSize(1000,300);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setLayout(new BorderLayout());
		
		// Configuracion de subpanel
		JPanel loginPanel = new JPanel();
		
		GridLayout myLayout = new GridLayout(2,3);
		loginPanel.setLayout(myLayout);
				
		JLabel login = new JLabel("Login");
		loginPanel.add(login);
		JTextField password = new JTextField(8);
		loginPanel.add(password);
		JCheckBox confirm = new JCheckBox("Ok");
		loginPanel.add(confirm);
		
		// Añadimos el subpanel al panel principal
		add(loginPanel,BorderLayout.CENTER);
		
		setVisible(true);
	}
}