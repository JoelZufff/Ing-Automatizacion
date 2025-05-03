import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import java.awt.GridLayout;

public class MyFrame extends JFrame 
{
	private ImageIcon ukIcon = new ImageIcon("media/ukbandera.jpg");
	private ImageIcon frIcon = new ImageIcon("media/franciabandera.jpg");
	private ImageIcon chIcon = new ImageIcon("media/chinabandera.jpg");
	private ImageIcon caIcon = new ImageIcon("media/canadabandera.jpg");
	private ImageIcon mxIcon = new ImageIcon("media/bandera-mexico.jpg");
	
	MyFrame()
	{
		setTitle("TestImageIcon");
		setSize(500, 125);
		setLocationRelativeTo(null); // Center the frame
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setLayout(new GridLayout(1, 5, 5, 5));
		add(new JButton(ukIcon ));
		add(new JButton(frIcon));
		add(new JButton(chIcon));
		add(new JButton(caIcon));
		add(new JButton(mxIcon));
		
		setVisible(true);
	}
}
