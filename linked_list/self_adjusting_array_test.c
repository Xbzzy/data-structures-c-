#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"self_adjusting_array.h"

void PrintArray(SelfAdj S)
{
	int i;
	printf("Array:");
	for (i = 0; i < S->Size; i++)
	{
		printf("%d ->", S->Array[i]);
	}
	printf("end\n");
}
void Test_Add(SelfAdj S)
{
	int i, random;
	printf("Add Test begin...\n");
	for (i = 0; i < 10; i++)
	{
		random = rand() % 11;
		AddInHeader(random, S);
	}
	PrintArray(S);
}
void Test_Visit(SelfAdj S)
{
	int i,random;
	printf("5 times visit random Test begin...\n");
	PrintArray(S);
	for (i = 0; i < 5; i++)
	{
		random = rand() % 11;
		if (Visit(random, S))
		{
			printf("Visit %d:\n", random);
			PrintArray(S);
		}
		else printf("Not find value!\n");
	}
}
void Test_Delete(SelfAdj S)
{
	int i,random;
	printf("5 times delete random Test begin...\n");
	for (i = 0; i < 5; i++)
	{
		random = rand() % 11;
		if (Delete(random, S))
		{
			printf("Delete %d:\n", random);
			PrintArray(S);
		}
		else printf("Not find!\n");
	}
}
void Test_func_time(SelfAdj S)
{
	int i,random;
	double cost_time;
	clock_t start, end;
	printf("100000 times visit test begin...\n");
	start = clock();
	for (i = 0; i < 100000; i++)
	{
		random = rand() % 11;
		Visit(random, S);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 times visit spend: %f ms", cost_time);
}
void main()
{
	srand((unsigned)time(NULL));
	SelfAdj S = CreateSelfAdj(10);
	Test_Add(S);
	Test_Visit(S);
	Test_Delete(S);
	Test_func_time(S);
	system("pause");
	return;
}