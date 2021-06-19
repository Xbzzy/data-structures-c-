#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"stack_list.h"

void PrintStack(Stack S)
{
	printf("Stack :");
	PtrToNode P = S->Next;
	while (P != NULL)
	{
		printf("%d ->", P->val);
		P = P->Next;
	}
	printf("NULL\n");
}
void Test_Push(Stack S)
{
	int i, random;
	printf("Push Test begin...\n");
	for (i = 0; i < 10; i++)
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
	for (i = 0; i < 5; i++)
	{
		Pop(S);
	}
	printf("Pop 5 times:\n");
	PrintStack(S);
	MakeEmpty(S);
}
void Test_func_time(Stack S)
{
	int i;
	double cost_time;
	clock_t start, end;
	start = clock();
	printf("100000 Times Test :\n");
	for (i = 0; i < 100000; i++)
	{
		Push(i, S);
		Pop(S);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 datas operation(push/pop) spend: %f ms\n", cost_time);
}
void main()
{
	srand((unsigned)time(NULL));
	Stack S = CreateStack();
	Test_Push(S);
	Test_Pop(S);
	Test_func_time(S);
	system("pause");
	return;
}