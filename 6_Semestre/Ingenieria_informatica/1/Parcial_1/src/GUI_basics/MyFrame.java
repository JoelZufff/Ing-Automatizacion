package GUI_basics;
import javax.swing.JButton;
import javax.swing.JFrame;
import java.awt.FlowLayout;

public class MyFrame extends JFrame 
{
	JButton btnOK;
	
	MyFrame()
	{
		FlowLayout mylayout = new FlowLayout(FlowLayout.LEFT, 5, 5);
		setLayout(mylayout);
				
		setTitle("MyFrame");
		setSize(1000,300);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JButton jbtOK = new JButton("Ok");
		add(jbtOK);
		
		JButton jbtCL = new JButton("Cancel");
		add(jbtCL);
		
		setVisible(true);
	}
}
