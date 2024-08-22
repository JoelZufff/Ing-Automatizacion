#include <stdio.h>
#include <iostream>

using namespace std;

double LagrangeInterpolation(int n, double* x, double* y, double xvalue) 
{
    double result = 0;
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term = term * (xvalue - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }

    printf("\n\nLa ecuacion de interpolacion de Lagrange es:\n");
    printf("\nf(x) = ");

    for (int i = 0; i < n; i++) 
    {
        printf("(%g) * ", y[i]);

        for (int j = 0; j < n; j++)
            if (i != j)
                printf("(x - %g) / (%g - %g)", x[j], x[i], x[j]);

        if (i < n - 1)
            printf(" + ");
    }

    return result;
}

int main()
{
    cout << "Programa hecho para calcular la interpolacion de Lagrange.\n\n";

Points:
    int n;
    cout << "Ingresa el numero de puntos:\t\t";
    cin >> n;

    if (n <= 0)
        goto Points;

    // Creamos arreglos de memoria dinamica
    double* x = new double[n];
    double* y = new double[n];

    // Pedimos al usuario que ingrese los puntos
    for (int i = 0; i < n; i++)
    {
        cout << "\n\nIngrese x_" << i << " =\t\t";      cin >> x[i];
        cout << "Ingrese f(x_" << i << ") =\t";         cin >> y[i];
    }

    // Ingreso de valor de x
    double xvalue;

    cout << "\n\nIngresa el valor de x para la interpolacion: ";
    cin >> xvalue;

    double result = LagrangeInterpolation(n, x, y, xvalue);

    printf("\n");

    printf("\n\nEl valor interpolado en x = %g es: %g\n", xvalue, result);

    // Liberamos memoria dinamica
    delete[] x;
    delete[] y;

    return 0;
}
