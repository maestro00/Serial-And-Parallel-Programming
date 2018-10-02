#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
	double pi;
	double sum=0;
	int i;
	if (argc<2) {
		printf("Usage: ./serial numberOfIterations\n");
		return 0;
	}
	int iteration=atoi(argv[1]);
	double divided=1;
	
	for(i=0;i<iteration;i++){
		sum+=pow((-1),i)*(1/divided); // Leibniz formula
		divided+=2;
 	}
	pi=sum*4; 
	printf("%1.51f\n",pi);	
}
