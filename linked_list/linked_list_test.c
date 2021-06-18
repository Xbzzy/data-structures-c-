#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"linked_list.h"

void PrintList(List L)
{
	printf("List : \n");
	Position P = L->Next;
	while (P!= NULL)
	{
		printf("%d ->", P->val);
		P = P->Next;
	}
	printf("NULL\n");
}
void Test_Insert(List L)
{
	int i,random;
	printf("Insert Test begin.....\n");
	for (i = 0; i < 10; i++)
	{
		random = rand() % 11;
		Insert(random, L, L);
	}
	PrintList(L);
}
void Test_Find(List L)
{
	int i, random;
	printf("Find Test begin.....\n");
	PrintList(L);
	for (i = 0; i < 5; i++)
	{
		random = rand() % 11;
		Position P = Find(random, L);
		if (P != NULL) printf("Find success,the value = %d\n", P->val);
		else printf("Find not successful!\n");
	}
}
void Test_Delete(List L)
{
	int i, random;
	printf("Delete Test begin.....\n");
	PrintList(L);
	for (i = 0; i < 5; i++)
	{
		random = rand() % 11;
		int Tmp = Delete(random, L);
		if (Tmp==1)
			printf("Delete success,the value = %d\n", random);
		else printf("Delete not successful,the value %d not find!\n",random);
	}
	PrintList(L);
}
void Test_func_time(List L)
{
	int i;
	double cost_time;
	clock_t start, end;
	start = clock();
	printf("100000 Times Test :\n");
	for (i = 0; i < 100000; i++)
	{
		Insert(i, L, L);
		Find(i, L);
		Delete(i, L);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 datas operation(insert/find/delete) spend: %f ms\n", cost_time);
}
void main()
{
	srand((unsigned)time(NULL));
	List L=CreateEmptyList();
	Test_Insert(L);
	Test_Find(L);
	Test_Delete(L);
	Test_func_time(L);
	system("pause");
	return;
}
