#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void MatrixPrint(double* matriz, int f, int c);
void MatrixInversa(double* matriz, int n);

int main()
{
    int n;
    printf("Ingrese el orden de la matriz cuadrada: ");
    scanf("%d", &n);

    double* matriz = (double*)malloc(n * n * sizeof(double));

    printf("\n\nIngrese los elementos de la matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Ingrese el elemento (%d, %d): ", i, j);
            scanf("%lf", (matriz + i * n + j));
        }
    }

    printf("\nMatriz original:\n");
    MatrixPrint(matriz, n, n);

    MatrixInversa(matriz, n);

    free(matriz);
    return 0;
}

void MatrixPrint(double* matriz, int f, int c)
{
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            printf("%.2lf\t", *(matriz + i * c + j));
        }
        printf("\n");
    }
}

void MatrixInversa(double* matriz, int n)
{
    double* matriz_inversa = (double*)malloc(n * n * sizeof(double));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                *(matriz_inversa + i * n + j) = 1.0;
            }
            else {
                *(matriz_inversa + i * n + j) = 0.0;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        double pivote = *(matriz + k * n + k);
        for (int j = 0; j < n; j++) {
            *(matriz + k * n + j) /= pivote;
            *(matriz_inversa + k * n + j) /= pivote;
        }

        for (int i = 0; i < n; i++) {
            if (i != k) {
                double factor = *(matriz + i * n + k);
                for (int j = 0; j < n; j++) {
                    *(matriz + i * n + j) -= factor * *(matriz + k * n + j);
                    *(matriz_inversa + i * n + j) -= factor * *(matriz_inversa + k * n + j);
                }
            }
        }

        printf("\nPaso %d:\n", k + 1);
        MatrixPrint(matriz_inversa, n, n);
    }

    printf("\nMatriz inversa:\n");
    MatrixPrint(matriz_inversa, n, n);

    free(matriz_inversa);
}
