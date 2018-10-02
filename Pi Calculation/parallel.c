#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>


struct leibniz_args { 
    int start, iteration; 
    double divided; 
};

void *leibniz(void *arguments);
double sum=0;
pthread_mutex_t locker; 


void *leibniz(void *arguments)
{
	struct leibniz_args *args = (struct leibniz_args*) arguments; 
	double localsum = 0, nom=1;
	int i;
	for(i=(*args).start;i<(*args).iteration;i++)
	{
		localsum+=pow((-1),i)*(nom/(*args).divided); 
		(*args).divided+=2; 
	}
	pthread_mutex_lock(&locker);  
	sum+=localsum;				
	pthread_mutex_unlock(&locker); 
	free(arguments); 
}


int main(int argc, char **argv)
{
	double pi;
	int i,s=1;
	if (argc<3) 
	{
		printf("Usage: ./pi numberOfThreads numberOfIterations\n");
		return 0;
	}
	int nthreads = atoi(argv[1]);
	int iteration=atoi(argv[2]);
	pthread_t tHandles[nthreads];
	struct leibniz_args *args;
    pthread_mutex_init(&locker, NULL);
	
	for(i=0;i<nthreads;i++)
	{
		args = malloc(sizeof(struct leibniz_args)); 
		(*args).iteration = iteration/nthreads;
		s=1+(i*(*args).iteration); 
		(*args).start=(s+1)%2;
		(*args).divided=2*s-1;		
		pthread_create(&tHandles[i], NULL, leibniz, (void *)args);		
	}
	for ( i = 0; i < nthreads; i++ ) 
	{
		pthread_join(tHandles[i], NULL); 
	}
	
	pi=sum*4;
	printf("%1.51f\n",pi);
	pthread_mutex_destroy(&locker);	
}


