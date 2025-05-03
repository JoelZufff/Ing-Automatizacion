import java.util.Scanner;

public class pesitos {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		float w, h,BMI;
		Scanner input = new Scanner(System.in);
		System.out.println("Introduce tu peso en kg\n");
		w = input.nextFloat();
		System.out.println("Introduce tu altura en m\n");
		h = input.nextFloat();
		BMI = (float) (w / Math.pow(h, 2));
		
		System.out.println("TU BMI es: \t" + BMI);
	if(BMI >=35)
		System.out.println("Estas bien panzon");
	else if(BMI>=29)
		System.out.println("Eres pazoncito");
	else if(BMI>=24)
		System.out.println("YA se nota la cena navidena");
	else if(BMI>=18)
		System.out.println("Estas chido");
	else if(BMI>=16)
		System.out.println("Come mas mijo tas flaco");
	else
		System.out.println("Denle un pan a esta pobre alama");
		
	}

}
