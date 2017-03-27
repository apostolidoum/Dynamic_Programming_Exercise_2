/*
	* Technical University of Crete
	* School of ECE
	* Dynamic Programming Course - Exercise 2: Optimal Load Distribution
	* Authors: Maria Apostolidou (apostolidoum@github), Nick Kyparissas (nkyparissas@github), Sofia Maragkou (MaSof@github)
	* 
	* Description: This program was implemented as part of the Dynamic Programming undergraduate course 
	* at the Technical University of Crete.
	* 
	* By using the method of Dynamic Programming, the program finds the optimal load distribution for a load 
	* weighing B units, consisting of different objects, each with its own value and weight.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node{
    float max_value; //maximum value of objects we can get at this node of the grid 
    float weight_for_max_value; //the objects' weight for the max value
    int previous_level_node; //node from the previous level.Transition from this node gave the max value 
    int number_of_items_taken; //how many items of previous node were taken
} node;

//prints the grid's state
void print_grid(node ** grid, int * NodesPerLevel, int K);

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
		
	printf("Number of items: %d, Load's Maximum Weight': %d\n", K, B);
	
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
	printf("Number of nodes in level %d: %d\n", 0, 1);
	for (k=1; k<=K; k++){
		NodesPerLevel[k] = (B/b[k-1])+1;
		printf("Number of nodes in level %d: %d\n", k, NodesPerLevel[k]);
	}
	
	/* Allocate memory for node grid*/
	node ** grid = (node **)malloc((K+1) * sizeof(node *));
 	for (i = 0; i <= K; i++)  // was: i <= K ? If we want this: malloc needs to change
		assert(grid[i] = (node *)malloc(NodesPerLevel[i]* sizeof(node)));

	/*Initialize nodes*/
	for (i = 0; i <= K; i++){  // was: i <= K ? If we want this: malloc needs to change
		for (j = 0; j < NodesPerLevel[i]; j++){ // was: i++
			grid[i][j].max_value = 0;
			grid[i][j].previous_level_node = 0; 
			grid[i][j].number_of_items_taken = 0;
			grid[i][j].weight_for_max_value = 0;
		}
	}

	print_grid(grid, NodesPerLevel, K);
	
	/*
	* Dynamic Programming
	*/
	float transition_value;
	
	for (i = 1; i <= K; i++){ //for every level of the graph
		for (m = 0; m < NodesPerLevel[i-1]; m++){ //for every node of the previous level
			for (j = 0; j < NodesPerLevel[i]; j++){ //for every node of the current level
				//calculate transition
				if (grid[i-1][m].weight_for_max_value + j*b[i-1] <= B){ //check that the transition is within weight limits
					transition_value = j*w[i-1] + grid[i-1][m].max_value; //number of items * their value + the maximum value of the previous node up to this point.
						//if the transition is more valuable than the previous one update node 
						if(transition_value >= grid[i][j].max_value){
							grid[i][j].max_value = transition_value;
							grid[i][j].weight_for_max_value = grid[i-1][m].weight_for_max_value + j*b[i-1];
							grid[i][j].previous_level_node = m;
							grid[i][j].number_of_items_taken = j;
					}
				}
			}
		}
	}
	
	/*
	* locate the path to find the components of the most valuable load
	*/
	float max = -1;
	int max_position = -1;
	for(j = 0; j<NodesPerLevel[K]; j++){
		if (grid[K][j].max_value > max){
			max = grid[K][j].max_value;	
			max_position = j;
		}
	}
	
	print_grid(grid, NodesPerLevel, K);
	
	/* Print result */
	printf("best value is : %f \n", max);
	for(i = K; i>0; i--){
		printf("taken %d objects of type %d \n", grid[i][max_position].number_of_items_taken, i-1 );
		max_position = grid[i][max_position].previous_level_node;
	}
	
	printf("\n\nPress enter to exit.\n"); 
	fflush(stdin);
	getchar();
	return 0;
}

void print_grid( node ** grid,int * NodesPerLevel, int K ){
	printf("---- GRID VALUES -------------------------------------------------------------------------\n");
	int i,j;
	for (i = 0; i<= K; i++){
		for (j = 0; j < NodesPerLevel[i]; j++){
			printf("grid[%d][%d] max_value: %f, previous_level_node: %d, number_of_items_taken: %d, weight_for_max_value: %f \n", i,j, grid[i][j].max_value,grid[i][j].previous_level_node, grid[i][j].number_of_items_taken, grid[i][j].weight_for_max_value);
		}
	}
	printf("------------------------------------------------------------------------------------------\n");

	return;
}
