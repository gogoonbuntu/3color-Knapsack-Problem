#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int weight[10000] = {0, };
int benefit[10000] = {0, };
int Capacity = 0;
char answer_DP[100];

int randomGenerate(int itemNum);
void printArray(int a[]);
char* DP(int itemNum);

int main(void){
	randomGenerate(10);
	printArray(weight);
	printArray(benefit);
	DP(10);
	
}


int randomGenerate(int itemNum){

	srand((unsigned int)time(NULL));

	for(int i=1; i<=itemNum; i++){
		weight[i] = rand()%99+1;
		benefit[i] = rand()%299+1;
	}
	
	Capacity = itemNum*40;
	printf("random generated\n");
	return 0;
}

char* DP(int itemNum) {
	clock_t start_DP = clock();

	//동적배열 생성
	int** B = malloc(sizeof(int*) * itemNum);
	for(int i=0; i<=itemNum; i++){
		B[i] = malloc(sizeof(int) * Capacity);
		//B[item][weight]
	}

	printf("B array generated\n");

	for(int j=0; j<=Capacity; j++){
		B[0][j] = 0;
	}
	for(int i=1; i<=itemNum; i++){
		B[i][0] = 0;
		for(int j=1; j<=Capacity; j++){
			if(weight[i]<=j){
				int option1 = benefit[i]+B[i-1][j-weight[i]];
				int option2 = B[i-1][j];
				B[i][j]= option1 > option2 ? option1 : option2;
			} else {
				B[i][j]= B[i-1][j];
			}
			//printf("B[%d][%d] : %d\n", i, j, B[i][j]);
		}
	}
	clock_t end_DP = clock();

	float time_DP = end_DP - start_DP;

	answer_DP[0] = '\0';
	sprintf(answer_DP, "%d / %.3f", B[10][400], time_DP);
	printf("answer_DP = %s\n", answer_DP);
	return answer_DP;
}


void printArray(int a[]) {
	printf("print start\n");
	int i=1;
	while(a[i]>0){
		printf("%d: %-5d", i, a[i]);
		i++;
		i%5==1 ? printf("\n") : 0;
	}
}