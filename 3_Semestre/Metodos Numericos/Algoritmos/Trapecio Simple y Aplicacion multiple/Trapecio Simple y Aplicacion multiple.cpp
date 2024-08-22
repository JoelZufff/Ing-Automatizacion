#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

class function
{
	int degree;
	double* coefficients;

	public:
	
	function()
	{
		cout << "Ingrese el grado de la funcion:\t\t";	
		cin >> degree;

		coefficients = new double[degree + 1];

		for (int exponent = degree; exponent >= 0; exponent--)
		{
			if (exponent > 0)
				cout << "\nIngrese el coeficiente de x^" << exponent << ":\t\t";
			else
				cout << "\nIngrese el coeficiente sin x:\t\t";

			cin >> coefficients[exponent];
		}

		cout << "\n\nLa funcion ingresada es:\t";	this->print();
	}

	~function()
	{
		delete[] coefficients;
	}

	void print()
	{
		cout << "f(x) = ";
		for (int exponent = degree; exponent >= 0; exponent--)
		{
			if (exponent > 0)
				printf("(%g)x^%d + ", coefficients[exponent], exponent);
			else
				printf("(%g)", coefficients[exponent]);
		}
	}

	double evaluate(double x)
	{
		double result = 0.0;

		for (int exponent = degree; exponent >= 0; exponent--)
			result += pow(x, exponent) * coefficients[exponent];

		return result;
	}
};

int main()
{
	cout << "Programa para realizar regla de Trapecio Simple y multiple";

	cout << endl << "________________________________________________________________________________";
	cout << "\n\nCREACION DE FUNCION:\n\n";

	// Creamos una nueva funcion
	function fx;

	cout << endl << "________________________________________________________________________________";
	cout << "\n\nTRAPECIO MULTIPLE:\n\n";

	// Llenado de datos para el trapecio multiple o simple
	
	double a, b;

	cout << "Ingrese el limite inferior de la integral =\t\t";		cin >> a;
	cout << "\nIngrese el limite superior de la integral =\t\t";	cin >> b;

	int n;

	cout << "\nIngrese el numero de intervalos =\t\t\t";			cin >> n;

	double delta = (b - a) / n;

	// Aplicacion del metodo de trapecio multiple

	double aux = 0.0;

	for (int i = 1; i < n; i++)		// Desde el segundo segmento hasta el penultimo
		aux += fx.evaluate(a + (delta * i));

	double integral = (delta / 2) * (fx.evaluate(a) + (2 * aux) + fx.evaluate(b));	// El primer y ultimo intervalo no se multiplicaban por 2

	cout << "\n\nAproximacion de la integral de (" << a << ") -> (" << b << "), de la funcion: \n";		fx.print();
	cout << " = " << integral << endl << endl;

	system("pause");

	return 0;
}