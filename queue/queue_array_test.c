#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"queue_array.h"

void PrintQueue(Queue Q)
{
	int i;
	printf("Front:");
	for (i = Q->Front; i!=Q->Rear ; i++)
	{
		i = i % (Q->Capacity);
		printf("%d <- ", Q->Array[i]);
	}
	printf("%d\n", Q->Array[i]);
}
void Test_Enqueue(Queue Q)
{
	int i, random;
	printf("Enqueue Test begin...\n");
	for (i = 0; i < 10; i++)
	{
		random = rand() % 101;
		Enqueue(random, Q);
	}
	PrintQueue(Q);
}
void Test_Dequeue(Queue Q)
{
	int i;
	printf("Dequeue Test begin...\n");
	for (i = 0; i < 5; i++)
	{
		Dequeue(Q);
	}
	printf("Dequeue half an queue :\n");
	PrintQueue(Q);
	MakeEmpty(Q);
}
void Test_func_time(Queue Q)
{
	int i;
	double cost_time;
	clock_t start, end;
	printf("100000 times Test begin:\n");
	start = clock();
	for (i = 0; i < 100000; i++)
	{
		Enqueue(i, Q);
		Dequeue(Q);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 times operation(enqueue/dequeue) spend: %f ms", cost_time);
}
void main()
{
	srand((unsigned)time(NULL));
	Queue Q = CreateQueue(10);
	Test_Enqueue(Q);
	Test_Dequeue(Q);
	Test_func_time(Q);
	system("pause");
	return;
}