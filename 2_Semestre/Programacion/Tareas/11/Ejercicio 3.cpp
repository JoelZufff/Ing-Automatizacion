#include <stdio.h>
int main()
{
	int T,*iE,*i,*f,*c,*pos,res;
	
	// Pedimos el tamaño del arreglo al usuario
	do
	{
		printf("Ingrese el tamaño del vector del que se sacara el valor minimo: ");
		scanf("%d",&T);
	}
	while (T<2);
	
	int A[T];
	
	// Le pedimos al usuario que llene todos los valores del arreglo
	for(int k=0;k<T;k++)
	{
		printf("\nIngrese el valor %d del arreglo: ",k+1);
		scanf("%d",&A[k]);
	}
	
	// Definimos 2 apuntadores a la direccion del valor inicial y final del arreglo
	i=&A[0];
	f=&A[T-1];
	
	// Iniciamos un ciclo for para seleccionar el elemento "Insertado" hasta que el ultimo elemento lo sea
	for(iE=&A[1];iE<=f;iE++)
	{
		// Definimos un apuntador posicion a la direccion donde el elemento seleccionado debe ir (Asumiendo que esta en el lugar correcto)
		pos=iE;
		// Inciamos un ciclo for para comparar el elemento "Insertado" con todos los valores anteriores a este en el arreglo
		for(c=iE-1;c>=i;c--)
		{
			// Si algun valor anterior al arreglo es menor al valor "Insertado", cambiamos el apuntador posicion para guardar la direccion en la que debe ir
			if(*iE<*c)
				pos=c;
		}
		// Si la direccion del apuntador posicion es diferente a la direccion del apuntador del valor "Insertado", hacemos el swap para acomodarlo en su lugar
		if(pos!=iE)
		{
			res=*iE;
			for(c=iE;c>pos;c--)
			{
				*c=*(c-1);
			}
			*pos=res;
		}
	}
		
	printf("\nEl arreglo ordenado es: (%d",A[0]);
	
	for(int k=1;k<T;k++)
		printf(", %d",A[k]);
		
	printf(")");
	
	return 0;
}
