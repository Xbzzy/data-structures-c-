#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"binary_search.h"

void PrintData(Data D)
{
	int i;
	for (i = 0; i < D->KeyNum; i++)
	{
		printf("%d ", D->Key[i]);
	}
	printf("\n");
}
void Test_Find(Data D)
{
	int i, Tmp, random;
	for (i = 0; i < 20; i++)
	{
		random = rand() % 51;
		Tmp = Find(random, D);
		if (Tmp != -1)
			printf("%d find success!\n", random);
		else printf("%d not find!\n",random);
	}
}
void main()
{
	int i, random;
	Data D;
	srand((unsigned)time(NULL));
	D = InitData(20);
	for (i = 0; i < 20; i++)
	{
		D->Key[i] = i+1;
	}
	PrintData(D);
	Test_Find(D);
	system("pause");
	return;
}
