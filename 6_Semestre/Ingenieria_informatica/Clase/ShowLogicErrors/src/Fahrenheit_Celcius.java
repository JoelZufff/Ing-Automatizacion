import java.util.Scanner;

public class Fahrenheit_Celcius {

	public static void main(String[] args) 
	{
		Scanner input = new Scanner(System.in);
		float fahrenheit = input.nextFloat();
		float celsius;
		
		celsius = (5.0f/9) * (fahrenheit - 32);
		
		System.out.println("El resultado es =\t" + celsius);
		
	}

}
