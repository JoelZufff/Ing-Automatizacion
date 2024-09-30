#ifndef _LibreriaYOUL
#define _LibreriaYOUL

void IMPRESION(int A[100][100], int f, int c);
void LECTURA(int A[100][100], int f, int c, int a);
void SUMA(int A[100][100],int B[100][100],int C[100][100], int f, int c);
void RESTA(int A[100][100],int B[100][100],int C[100][100], int f, int c);
void MULTIPLICACION(int A[100][100],int B[100][100],int C[100][100], int f, int c, int cb);
void TRANSPUESTA(int A[100][100],int C[100][100], int f, int c);
int DETERMINANTE2X2(int A[100][100]);
int DETERMINANTE3X3(int A[100][100]);

#include "libreriayoul.cpp"
#endif
