import javax.swing.JOptionPane;

public class ShowLogicErrors {

	public static void main(String[] args) 
	{
		// add number1 to number2
        //int number1=3;
        //int number2=3;
        //number2+=number1+number2;
        //System.out.println("number2 is "+number2);
		String input = JOptionPane.showInputDialog("Introduce un valor");
		int num = Integer.parseInt(input);
		System.out.println(num);
	}
}
