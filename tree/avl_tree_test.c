#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<windef.h>
#include<time.h>
#include"avl_tree.h"

void LDR_PrintTree(AvlTree T)
{
	if (T != NULL)
	{
		LDR_PrintTree(T->Left);
		printf("%d ", T->val);
		LDR_PrintTree(T->Right);
	}
}
AvlTree Test_Insert(AvlTree T)
{
	int i, random;
	printf("Insert Test begin...\n");
	for (i = 0; i < 20; i++)
	{
		T=Insert(i+1, T);
	}
	LDR_PrintTree(T);
	printf("\n");
	return T;
}
AvlTree Test_Delete(AvlTree T)
{
	int i, random;
	Position TmpNode;
	printf("Delete Test begin...\n");
	for (i = 0; i < 10; i++)
	{
		random = rand() % 21;
		printf("Delete %d ...\n", random);
		TmpNode = Find(random, T);
		if (TmpNode == NULL){ printf("not find!\n"); continue; }
		else 
		{
			T=Delete(random, T);
			printf("delete success!\n");
		}
	}
	LDR_PrintTree(T);
	printf("\n");
}
void Test_func_time(AvlTree T)
{
	int i,j;
	double cost_time;
	printf("1000 times test begin...\n");
	clock_t start, end;
	start = clock();
	for (i = 0; i < 1000;i++)
	{
		T=Insert(i, T);
	}
	for (j = 100; j < 600; j++)
	{
		T=Delete(j, T);
	}
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("1000 times operation insert and 500 times delete spend: %f ms\n", cost_time);
}
void main()
{
	srand ((unsigned)time(NULL));
	AvlTree T = NULL;
	T=Test_Insert(T);
	T=Test_Delete(T);
	AvlTree T1=NULL;
	Test_func_time(T1);
	system("pause");
	return;
}