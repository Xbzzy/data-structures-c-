#ifndef _QUICK_SORT_H_

int *InitArray(int maxsize);
void QuickSort(int *data, int left, int right);

#endif /*_QUICK_SORT_H_*/
int *InitArray(int maxsize)
{
	int i;
	int *data = (int *)malloc(sizeof(int)*maxsize);
	if (data == NULL){
		printf("out of space!\n");
		return NULL;
	}
	for (i = 0; i < maxsize; i++){
		data[i] = rand() % (maxsize * 5);
	}
	return data;
}
static int Settle(int data[], int left, int right)
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
void QuickSort(int data[], int left, int right)
{
	if (left<right)
	{
		int i = Settle(data, left, right);
		QuickSort(data, left, i - 1);
		QuickSort(data, i + 1, right);
	}
}

