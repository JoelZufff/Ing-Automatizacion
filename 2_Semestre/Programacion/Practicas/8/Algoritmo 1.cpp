#include <stdio.h>
const int T=9;

int main()
{
	int A[T]={1,2,3,4,5,6,7,8,9},res,j=T-1,i,*c,*c2;
	
	printf("\nEl vector original ordenado es = ");
	printf("(%d",A[0]);
	for(i=1;i<T;i++)
	{
		printf(", %d",A[i]);
	}
	printf(")\n");
	
	
	for(i=0;i<(T/2);i++)
	{
		c=&A[0];
		c2=c;
			
		c+=i;
		c2+=j;
		
		res=*c;
		
		*c=*c2;
		*c2=res;
		j--;
	}

	printf("\nEl vector invertido es = ");
	printf("(%d",A[0]);
	for(i=1;i<T;i++)
	{
		printf(", %d",A[i]);
	}
	printf(")\n");	
}
