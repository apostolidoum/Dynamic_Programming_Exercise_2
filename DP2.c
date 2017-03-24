/*
	* Technical University of Crete
	* School of ECE
	* Dynamic Programming Course - Exercise 2: Optimal Load Distribution
	* Authors: Maria Apostolidou (apostolidoum@github), Nick Kyparissas (nkyparissas@github), Sofia Maragkou (https://github.com/MaSof)
	* 
	* Description: This program was implemented as part of the Dynamic Programming undergraduate course 
	* at the Technical University of Crete.
	* 
	* By using the method of Dynamic Programming, the program finds the optimal load distribution of a load 
	* weight B consisting of different objects, each with its own value and weight.
*/ 

#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int K, B, k;
	
	do{
		printf("Please give the number of objects and the load's maximum weight:\n");
		fflush(stdin);
		scanf("%d", &K);
		fflush(stdin);
		scanf("%d", &B);
		if((K<=0)||(B<0)) 
			printf("Both must be positive values. ");
	}while((K<=0)||(B<0));
		
	printf("K: %d, B: %d\n", K, B);
	
	//b[k] = weight of object k
	float *b = (float *)malloc(K * sizeof(float));
	
	//w[k] = value of object k
	float *w = (float *)malloc(K * sizeof(float));
	
	for (k=0; k<K; k++){	
		do{
			printf("Please give the weight and value of object %d:\n", k);
			fflush(stdin);
			scanf("%f", &b[k]);
			fflush(stdin);
			scanf("%f", &w[k]);
			if((K<=0)||(B<0)) 
				printf("Both must be positive values. ");
		}while((K<=0)||(B<0));	
	}
		
		
	//The Dynamic Programming graph will have K number of levels. 
	int *NodesPerLevel = (int *)malloc(K * sizeof(int));
	
	//Each level will have as many nodes as the number of the item k the load can carry 
	//(how many items of weight b[k] can fit in total load's weight B)
	NodesPerLevel[0] = 0;
	for (k=1; k<K; k++)
		NodesPerLevel[k] = (B/b[k])+1;
	
	
	
	
	printf("\n\nPress enter to exit.\n");
	fflush(stdin);
	getchar();
	return 0;
}
