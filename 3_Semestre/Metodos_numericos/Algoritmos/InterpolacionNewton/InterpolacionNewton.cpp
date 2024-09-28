#include <stdio.h>
#include <iostream>

using namespace std;

double NewtonInterpolation(int n, double* x, double* y, double xvalue) 
{
    double result = 0;

    // Creamos matriz de memoria dinamica
    double** divDiff = new double* [n];
    for (int i = 0; i < n; i++)
        divDiff[i] = new double[n];

    // Inicializacion de la tabla de diferencias divididas
    for (int i = 0; i < n; i++) 
        divDiff[i][0] = y[i];

    // Calculo de las diferencias divididas
    for (int j = 1; j < n; j++) 
        for (int i = 0; i < n - j; i++)
            divDiff[i][j] = (divDiff[i + 1][j - 1] - divDiff[i][j - 1]) / (x[i + j] - x[i]);

    // Calcula la ecuación de interpolación
    cout << "\n\nLa ecuacion de interpolacion de Newton es:\n";
    printf("\nf(x) = %g", divDiff[0][0]);

    for (int j = 1; j < n; j++) 
    {
        cout << " + ";
        
        printf("(%g)", divDiff[0][j]);

        for (int i = 0; i < j; i++)
            printf("(x - %g)", x[i]);
    }
    cout << endl;

    // Calcula el resultado de la interpolación
    for (int j = 0; j < n; j++) 
    {
        double term = divDiff[0][j];

        for (int i = 0; i < j; i++)
            term *= (xvalue - x[i]);
        result += term;
    }

    // Liberamos memoria dinamica
    for (int i = 0; i < n; i++)
        delete[] divDiff[i];
    delete[] divDiff;
    
    return result;
}

int main() 
{
    cout << "Programa hecho para calcular la interpolacion de newton.\n\n";
    
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

    double result = NewtonInterpolation(n, x, y, xvalue);

    printf("\n\nEl valor interpolado en x = %g es: %g\n", xvalue, result);

    // Liberamos memoria dinamica
    delete[] x;
    delete[] y;

    return 0;
}
