#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"stack_array.h"

void PrintStack(Stack S)
{
	int i;
	for (i = S->TopOfStack; i >=0; i--)
	{
		printf("%d ->", S->Array[i]);
	}
	printf("NULL\n");
}
void Test_Push(Stack S)
{
	int i, random;
	printf("Push Test begin...\n");
	for (i = 0; i < S->Capacity; i++)
	{
		random = rand() % 101;
		Push(random, S);
	}
	PrintStack(S);
}
void Test_Pop(Stack S)
{
	int i;
	printf("Pop Test begin...\n");
	for (i = 0; i < S->Capacity / 2; i++)
	{
		Pop(S);
	}
	printf("Pop half a stack:\n");
	PrintStack(S);
}
void Test_func_time(Stack S)
{
	int i;
	double cost_time;
	clock_t start, end;
	printf("100000 times Test begin...\n");
	start = clock();
	for (i = 0; i < 100000; i++)
	{
		Push(i, S);
		Pop(S);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 times operation(push/pop) spend: %f ms\n", cost_time);
}
void main()
{
	Stack S = CreateStack(10);
	Test_Push(S);
	Test_Pop(S);
	Test_func_time(S);
	system("pause");
	return;
}