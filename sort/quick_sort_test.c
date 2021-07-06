#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"quick_sort.h"
#define NDEBUG

void Test_sort(int *data)
{
	int i=0;
	QuickSort(data, 0, 19);
	while (i < 20){
		if (data[i] < data[i + 1])
			i++;
		else break;
	}
	assert(i < 20);
	return;
}
void Test_func_time()
{
	double cost_time;
	clock_t start, end;
	start = clock();
	int *data = InitArray(100000);
	QuickSort(data, 0, 99999);
	end = clock();
	cost_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000 datas quicksort cost: %f\n", cost_time);
}
void main()
{
	srand((unsigned)time(NULL));
	int *data = InitArray(20);
	Test_sort(data);
	Test_func_time();
	system("pause");
	return;
}
