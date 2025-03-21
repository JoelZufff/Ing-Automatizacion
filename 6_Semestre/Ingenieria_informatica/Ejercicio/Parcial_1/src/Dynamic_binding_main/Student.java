package Dynamic_binding_main;

public class Student extends Person
{
	private String state;
	
	
	Student(String name, String adress, String phoneNumber, String email, int year)
	{
		super(name, adress, phoneNumber, email);
		
		switch(year)
		{
			case 1:
				this.state = "freshman";
				break;
			case 2:
				this.state = "sophomore";
				break;
			case 3:
				this.state = "junior";
				break;
			case 4:
				this.state = "senior";
				break;
			default: break;
		}
	}
}
