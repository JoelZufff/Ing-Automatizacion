#include <stdio.h>
#include <iostream>

using namespace std;

void SplineInterpolation(int n, double* x, double* y, double xvalue, int degree)
{
    double* a = new double[n];
    double* b = new double[n];
    double* c = new double[n];
    double* d = new double[n];

    for (int i = 0; i < n; i++)
        a[i] = y[i];

    // Calcula coeficientes para Splines de grado 1
    if (degree >= 1)
    {
        for (int i = 0; i < n - 1; i++)
        {
            b[i] = (a[i + 1] - a[i]) / (x[i + 1] - x[i]);
            c[i] = 0.0;
            d[i] = 0.0;
        }

        // Impresion de las ecuaciones de las Splines de grado 1
        cout << "\n\nEcuaciones de las Splines de Grado 1:\n";
        for (int i = 0; i < n - 1; i++)
            printf("Spline %d: f(x) = %g + %g(x - %g)\n", i + 1, a[i], b[i], x[i]);
    }

    // Calcula coeficientes para Splines de grado 2
    if (degree >= 2)
    {
        for (int i = 0; i < n - 1; i++)
        {
            c[i] = (b[i + 1] - b[i]) / (x[i + 1] - x[i]);
            d[i] = 0.0;
        }

        // Impresion de las ecuaciones de las Splines de grado 2
        cout << "\nEcuaciones de las Splines de Grado 2:\n";
        for (int i = 0; i < n - 1; i++)
            printf("Spline %d: f(x) = %g + %g(x - %g) + %g(x - %g)^2\n", i + 1, a[i], b[i], x[i], c[i], x[i]);
    }

    // Calcula coeficientes para Splines de grado 3
    if (degree == 3) {
        for (int i = 0; i < n - 1; i++) {
            d[i] = (c[i + 1] - c[i]) / (x[i + 1] - x[i]);
        }

        // Impresion de las ecuaciones de las Splines de grado 3
        cout << "\nEcuaciones de las Splines de Grado 3:\n";
        for (int i = 0; i < n - 1; i++)
            printf("Spline %d: f(x) = %g + %g(x - %g) + %g(x - %g)^2 + %g(x - %g)^3\n", i + 1, a[i], b[i], x[i], c[i], x[i], d[i], x[i]);
    }

    // Realiza la interpolación
    for (int i = 0; i < n - 1; i++)
    {
        if (xvalue >= x[i] && xvalue <= x[i + 1])
        {
            double xi = xvalue - x[i];
            double spline_result = a[i] + b[i] * xi;

            if (degree >= 2) {
                spline_result += c[i] * xi * xi;
            }

            if (degree == 3) {
                spline_result += d[i] * xi * xi * xi;
            }

            printf("\nEl valor interpolado en x = %g es: %g\n", xvalue, spline_result);

            delete[] a;
            delete[] b;
            delete[] c;
            delete[] d;

            return;
        }
    }

    cout << "\nEl valor de x está fuera del rango de interpolación.\n";
}


int main()
{
    cout << "Programa hecho para calcular la interpolacion de Splines.\n\n";

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

    cout << "\n\nIngresa el valor de x para la interpolacion:\t\t";
    cin >> xvalue;

    int degree;

    cout << "\n\nIngresa el grado maximo de las splines (1, 2 o 3):\t\t";
    cin >> degree;

    SplineInterpolation(n, x, y, xvalue, degree);

    // Liberamos memoria dinamica
    delete[] x;
    delete[] y;

    return 0;
}