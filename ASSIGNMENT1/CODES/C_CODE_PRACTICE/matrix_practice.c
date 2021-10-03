#include<stdio.h>
#include<stdlib.h>
#include<MatLib.h>
#include<math.h>
int main(void)
{
	struct Mat *A=rand(4,4,-5,5);	
	printf("A=");
	showmat(A);		
		getchar();
	return 0;
}