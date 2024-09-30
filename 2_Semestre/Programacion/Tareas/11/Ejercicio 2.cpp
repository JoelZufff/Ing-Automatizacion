#include <stdio.h>
int main()
{
	int T,*minIndex,*j,*i,*t,res;
	
	do
	{
		printf("Ingrese el tamaño del vector del que se sacara el valor minimo: ");
		scanf("%d",&T);
	}
	while (T<2);
	
	int A[T];
	
	for(int k=0;k<T;k++)
	{
		printf("\nIngrese el valor %d del arreglo: ",k+1);
		scanf("%d",&A[k]);
	}
	
	// Definimos apuntadores con la direccion del valor inicial y final del arreglo
	i=&A[0];
	t=&A[T-1];
	// Creamos un ciclo for para seleccionar cada valor del arreglo menos el ultimo, para comparar este con su valor siguiente
	for(i;i<t;i++)
	{
		// Definimos el apuntador minimo a la direccion del valor seleccionado (i) asumiendo que este es el menor del arreglo
		minIndex=i;
		// Creamos un ciclo for para comparar los valores siguientes (j) con el valor seleccionado (i)
		for(j=i+1;j<t+1;j++)
		{
			// Si el valor siguiente (j) es menor que el valor seleccionado (i) apuntamos el valor minimo a la direccion del valor siguiente (j)
			if(*minIndex>*j)
				minIndex=j;
		}
		// Si la direccion del valor seleccionado (i) es diferente a la del valor minimo, realizamos el swap
		if(i!=minIndex)
		{
			res=*minIndex;
			for(minIndex;minIndex>i;minIndex--)
			{
				*minIndex=*(minIndex-1);
			}
			*i=res;
		}
	}
		
	printf("\nEl arreglo ordenado es: (%d",A[0]);
	
	for(int k=1;k<T;k++)
		printf(", %d",A[k]);
		
	printf(")");
	
	return 0;
}
