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
#include <assert.h>

typedef struct node{
    float max_value; //maximum value of objects we can get at this node of the grid 
    int previous_level_node; //node from the previous level.Transition from this node gave the max value 
    int number_of_items_taken; //how many items of previous node were taken (o elegxos)
} node;

int main(){
	
	int K, B, k;
	int i, j, m; //counters
	
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
	NodesPerLevel[0] = 1;
	for (k=1; k<K; k++)
		NodesPerLevel[k] = (B/b[k])+1;
	
	/* Allocate memory for node grid*/
	node ** grid = (node **)malloc(K * sizeof(node *));
 	for (i = 0; i < K; i++)  // was: i <= K ? If we want this: malloc needs to change
		assert(grid[i] = (node *)malloc(NodesPerLevel[i]* sizeof(node)));

	/*Initialize nodes*/
	for (i = 0; i < K; i++){  // was: i <= K ? If we want this: malloc needs to change
		for (j = 0; j < NodesPerLevel[i]; j++){ // was: i++
			grid[i][j].max_value = 0;
			grid[i][j].previous_level_node = 0; 
			grid[i][j].number_of_items_taken = 0;
		}
	}

	/*
	* Dynamic Programming
	*/
	int transition_value;
	for (i = 0; i <= K; i++){
		for (j = 0; j <= NodesPerLevel[i] - 1; j++){ 
			for (m = 0; m <= NodesPerLevel[j+1]; m++){
				//calculate transition
				transition_value = grid[i][j].max_value + (m*w[i]);
				//check that transition is withind limits
				if (transition_value <= B){
					//if transition is better than before update node at level j+1
					if(transition_value >= grid[i+1][j+m].max_value){
						grid[i+1][j+m].max_value = transition_value;
						grid[i+1][j+m].previous_level_node = j;
						grid[i+1][j+m].number_of_items_taken = m;
					}
				}
			}
		}
	}

	/* Print result */
	printf("best value is : %d \n",grid[K][NodesPerLevel[K]-1].max_value );
	int arrow = NodesPerLevel[K];
	for(i = K; i>=0; i--){
		printf("taken %d objects of type %d \n", grid[i][arrow].number_of_items_taken, i-1 );
		arrow = grid[i][arrow].previous_level_node;
	}
	
	
	printf("\n\nPress enter to exit.\n"); //did not work... terminated without waiting
	fflush(stdin);
	getchar();
	return 0;
}
