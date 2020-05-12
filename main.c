#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int weight[10000] = {0, };
int benefit[10000] = {0, };
int W = 0;

int randomGenerate(int itemNum);
void printArray(int a[]);
char* DP(int w, int itemNum);

int main(void){
	randomGenerate(10);
	DP(10, 10);
	//printArray(weight);
	//printArray(benefit);
}


int randomGenerate(int itemNum){

	srand((unsigned int)time(NULL));

	for(int i=1; i<=itemNum; i++){
		weight[i] = rand()%99+1;
		benefit[i] = rand()%299+1;
	}
	
	W = itemNum*40;
	printf("random generated\n");
	return 0;
}

char* DP(int w, int itemNum) {
	//동적배열 생성
	int** B = malloc(sizeof(int*) * itemNum);
	for(int i=0; i<itemNum; i++){
		B[i] = malloc(sizeof(int) * w);
		//B[item][weight]
	}

	printf("B array generated\n");

	for(int j=0; j<w; j++){
		B[0][j] = 0;
	}
	for(int i=1; i<itemNum; i++){
		B[i][0] = 0;
		for(int j=1; j<w; j++){
			if(weight[i]<=W){
				int option1 = benefit[i]+B[i-1][j-weight[i]];
				int option2 = B[i-1][j];
				printf("[%d][%d] op1 : %d, op2: %d\n", i, j, option1, option2);
				B[i][j]= option1 > option2 ? option1 : option2;
				//printf("B[%d][%d] : %d\n", i, j, B[i][j]);
			} else {
				B[i][j]= B[i-1][j];
			}
		}
	}
	return 0;
}


void printArray(int a[]) {
	int i=0;
	while(a[i]!=0){
		printf("%d: %d\n", i, a[i]);
		i++;
	}
}