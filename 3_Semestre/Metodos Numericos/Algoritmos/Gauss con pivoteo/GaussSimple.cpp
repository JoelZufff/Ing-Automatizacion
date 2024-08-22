#include <conio.h>
#include <iostream>

using namespace std;

void IMPMATF(float* A, int f, int c);

void main()
{
	int B;
	do
	{
		int i, j, k, aux;
		float A[3][4], RES[4], det;

		system("cls");

		cout << "Este programa recibe un sistema de ecuaciones 3X3 y lo resuelve paso por paso.";

		for (i = 0; i < 3; i++) // Llenado de ecuaciones
		{
			cout << "\n\nEcuacion " << i + 1 << ":\n";
			cout << "\nIngrese el coeficiente de la 'x':\t"; cin >> A[i][0];
			cout << "\nIngrese el coeficiente de la 'y':\t"; cin >> A[i][1];
			cout << "\nIngrese el coeficiente de la 'z':\t"; cin >> A[i][2];
			cout << "\nIngrese el resultado de la ecuacion:\t"; cin >> A[i][3];

			cout << "\nLa ecuacion ingresada fue:\t(" << A[i][0] << "x) + (" << A[i][1] << "y) + (" << A[i][2] << "z) = " << A[i][3] << endl;
		}

		system("pause");
		system("cls");

		cout << "La matriz de las ecuaciones es:\n\n\tx\ty\tz\n\n";
		IMPMATF(*A, 3, 4);
		_getch();

		// Calculamos determinante para ver si el sistema tendra solucion

		det = A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]);
		det -= A[0][1] * (A[1][0] * A[2][2] - A[2][0] * A[1][2]);
		det += A[0][2] * (A[1][0] * A[2][1] - A[2][0] * A[1][1]);

		// Intercambiar filas si en algun valor de la diagonal hay 0 al comenzar
		for (i = 0; i < 3; i++)
		{
			if (A[i][i] == 0)
			{
				for (j = 0; (A[j][i] == 0) && (j < 3); j++);
				if (j == 3) // No encontro ningun numero diferente a 0 en su columna
					break;
				else // Intercambiar Filas i y j
				{
					for (k = 0; k < 4; k++)
					{
						RES[k] = A[i][k]; // RES = Fila i
						A[i][k] = A[j][k]; // Fila i = Fila j
						A[j][k] = RES[k]; // Fila j = RES
					}
					cout << "\nR" << i + 1 << " <--> R" << j + 1;
					cout << "\n\tx\ty\tz\n\n";
					IMPMATF(*A, 3, 4);
					_getch();
				}
			}
		}

		for (j = 0; j < 3; j++) // Desepejar las variables operando las filas
		{
			for (i = 0; i < 3; i++)
			{
				if ((i != j) && (A[i][j] != 0))
				{
					aux = A[i][j];
					for (k = 0; k < 4; k++)
					{
						A[i][k] = (A[j][j] * A[i][k]) - (aux * A[j][k]);
					}
					cout << "\nR" << i + 1 << " --> (" << A[j][j] << "R" << i + 1 << ") - (" << aux << "R" << j + 1 << ")\n";
					cout << "\n\tx\ty\tz\n\n";
					IMPMATF(*A, 3, 4);
					_getch();
				}
				else {}
			}
		}

		system("cls");

		if (det == 0)
			cout << "\tEL SISTEMA DE ECUACIONES NO TIENE SOLUCION";
		else
		{
			cout << endl << "R E S U L T A D O S:\n";
			for (i = 0; i < 3; i++)
			{
				aux = A[i][i];
				A[i][i] /= aux;
				A[i][3] /= aux;
			}
			cout << "\n\tx\ty\tz\n\n";
			IMPMATF(*A, 3, 4);
			cout << "\n\nPor lo tanto:\n\nx = " << A[0][3] << "\ny = " << A[1][3] << "\nz = " << A[2][3];
		}

		cout << "\n\nPresione la tecla '1' para repetir el proceso, de lo contrario presione '0' para salir";

		do
		{
			fflush(stdin);
			B = _getch();
		} while ((B != 48) && (B != 49));

	} while (B == 49);
}

void IMPMATF(float* A, int f, int c)
{
	int i, j;
	for (i = 0; i < f; i++)
	{
		cout << "\t";
		for (j = 0; j < c; j++)
			cout << A[i * c + j] << "\t";
		cout << "\t\n";
	}
}