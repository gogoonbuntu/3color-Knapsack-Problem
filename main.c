#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define swap(a, b) {int t; t = a; a = b; b = t;}

int weight[10000] = {0, };
int benefit[10000] = {0, };
int Capacity = 0;
char answer_DP[100];
char answer_BB[100];
char answer_GR[100];

int randomGenerate(int itemNum);
void printArray(int a[]);
char* DP(int itemNum);
char* BB(int itemNum);
char* GR(int itemNum);
void quickSort(float *base, int n);

typedef struct{
	int benefitTotal;
	int weightTotal;
	float bound;
} node;

int main(void){
	randomGenerate(10);
	DP(10);
	BB(10);
	GR(10);
}


int randomGenerate(int itemNum){

	srand((unsigned int)time(NULL));
	memset(weight, 0, sizeof(weight));
	memset(benefit, 0, sizeof(benefit));

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
	sprintf(answer_DP, "%d / %.3f", B[itemNum][Capacity], time_DP);
	printf("answer_DP = %s\n", answer_DP);
	return answer_DP;
}

char* BB(int itemNum){
	clock_t start_BB = clock();
	int Bmax = 0;

	float* benefitOverWeight = malloc(sizeof(float) * itemNum);

	for(int i=1; i<=itemNum; i++){
		benefitOverWeight[i] = (float)benefit[i]/weight[i];
	}
	quickSort(benefitOverWeight, itemNum);
	
	node* 

	clock_t end_BB = clock();
	float time_BB = end_BB - start_BB;
	answer_BB[0] = '\0';
	sprintf(answer_BB, "%d / %.3f", Bmax, time_BB);
	printf("answer_BB = %s\n", answer_BB);
	return answer_BB;
}

char* GR(int itemNum){
	clock_t start_GR = clock();

	float* benefitOverWeight = malloc(sizeof(float) * itemNum);
	for(int i=1; i<=itemNum; i++){
		benefitOverWeight[i] = (float)benefit[i]/weight[i];
	}
	quickSort(benefitOverWeight, itemNum);

	int capacityLeft = Capacity;
	float Bmax = 0;
	int i = 0;
	while(weight[i]<=capacityLeft){
		Bmax += benefit[i];
		capacityLeft -= weight[i];
		i++;
	}

	Bmax += (float)capacityLeft/weight[i] * benefitOverWeight[i];

	clock_t end_GR = clock();
	float time_GR = end_GR - start_GR;
	answer_GR[0] = '\0';
	sprintf(answer_GR, "%.3f / %.3f", Bmax, time_GR);
	printf("answer_GR = %s\n", answer_GR);
	return answer_GR;
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

void quickSort(float *base, int n)

{
    int pivot = 0;
    int left = 0, right = 0; 
    if (n <= 1)
    {
        return;
    }
    left = 0;
    right = n;
    while (1)

    {
        for (left++; (left<n) && (base[0] >= base[left]); left++);
        for (right--; (right>0) && (base[0]<base[right]); right--);
        if (left<right)
        {
            swap(base[left], base[right]);
			swap(benefit[left], benefit[right]);
			swap(weight[left], weight[right]);
        }
        else {
            break;
        }
    }

    swap(base[0], base[right]);

    quickSort(base, right);
    quickSort(base + left, n - left);
}