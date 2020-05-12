#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int weight[10000] = {0, };
int benefit[10000] = {0, };

int randomGenerate(int num);
void printArray(int a[]);

int main(void){
	randomGenerate(10);
	printArray(weight);
	printArray(benefit);
}


int randomGenerate(int num){

	srand((unsigned int)time(NULL));
	
	for(int i=0; i<num; i++){
		weight[i] = (rand()+1)%100;
		benefit[i] = (rand()+1)%300;
	}
	
	return 0;
}

void printArray(int a[]) {
	int i=0;
	while(a[i]!=0){
		printf("%d: %d\n", i, a[i]);
		i++;
	}
	//printf("\n");
}