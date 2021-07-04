#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<time.h>
#include"hashmap.h"
#define NDEBUG
int Count(HashMap hashmap)
{
	int i,sum=hashmap->len;
	for (i = 0; i < hashmap->len; i++){
		Position tmp = &(hashmap->map[i]);
		while (tmp->next != NULL){
			sum++;
			tmp = tmp->next;
		}
	}
}
void Test_Insert(HashMap hashmap)
{
	int i, random,sum;
	for (i = 0; i < 20; i++){
		random = rand() % 101;
		Insert(hashmap, random);
	}
	sum = Count(hashmap);
	assert(sum == 20);
}
void Test_Find(HashMap hashmap)
{
	int i,sum=0,random;
	for (i = 0; i < 100; i++){
		random = rand() % 101;
		Position tmp = Find(hashmap, random);
		if (tmp == NULL)continue;
		else sum++;
	}
}
void Test_func_time(HashMap hashmap)
{
	int i,random;
	double cost_time;
	clock_t start, end;
	start = clock();
	for (i = 0; i < 100000; i++){
		Insert(hashmap, i);
	}
	for (i = 0; i < 100000; i++){
		random = rand() % 150001;
		Find(hashmap, random);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 times operation cost: %f", cost_time);
}
void main()
{
	srand((unsigned)time(NULL));
	HashMap hashmap = InitMap(10);
	Test_Insert(hashmap);
	Test_Find(hashmap);
	Test_func_time(hashmap);
}
