import java.util.Scanner;

public class PentagonalNumbers 
{
    public static int getPentagonalNumber(int n) 
    {
        return n * (3 * n - 1) / 2;
    }

    public static void main(String[] args) 
    {
    	Scanner scanner = new Scanner(System.in);
        System.out.print("Ingrese el número de términos: ");
        int n = scanner.nextInt();

        for (int i = 1; i <= n ; i++)
            System.out.printf("%6d\t", getPentagonalNumber(i));
    }
}