//普通快排，选取子序列第一位作为基准进行排序;
//对于渐进有序的序列排序效果较差，会造成子序列两边的不平衡从而导致时间复杂度趋近于（O(n²)）;
//测试用例由用户输入;
#include<stdio.h>
int put(int data[], int left, int right)
{
	int i = left, j = right;
	int norm = data[i];
	while (i<j)
	{
		while (i<j&&data[j] >= norm) j--;
		data[i] = data[j];
		while (i<j&&data[i] <= norm) i++;
		data[j] = data[i];
	}
	data[i] = norm;
	return i;
}
void sort(int data[], int left, int right)
{
	if (left<right)
	{
		int i = put(data, left, right);
		sort(data, left, i - 1);
		sort(data, i + 1,right );
	}
}
int *input(int len)
{
	int*data = (int*)malloc(len*(sizeof(int)));
	for (int i = 0; i < len; i++)
	{
		printf("第%d个元素：", i + 1);
		scanf("%d", &data[i]);
	}
	return data;
}
int main()
{
	int len;
	printf("输入数组长度：\n");
	scanf("%d", &len);
	int*data = input(len);
	printf("排序前:\n");
	for (int i = 0; i<len; ++i)
		printf(" %d ", data[i]);
	sort(data, 0, len-1);
	printf("\n排序后:\n");
	for (int i = 0; i<len; ++i)
		printf(" %d ", data[i]);
	printf("\n");
	system("pause");
	return 0;
}
