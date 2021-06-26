#ifndef _BINARY_SEARCH_H_

struct DataRecord;
typedef int Element;
typedef struct DataRecord *Data;
Data InitData(int keynum);
int Find(Element key, Element *Data);

#endif /*_BINARY_SEARCH_H_*/

struct DataRecord
{
	Element KeyNum;
	Element *Key;
};

Data InitData(int keynum)
{
	Data D = malloc(sizeof(struct DataRecord));
	if (D == NULL){ printf("out of space!\n"); return NULL; }
	D->KeyNum = keynum;
	D->Key = malloc(keynum*(sizeof(Element))); 
	if (D->Key == NULL){ printf("out of space!\n"); return NULL; }
	return D;
}
int Find(Element key, Data D)
{
	int start = 0, end = D->KeyNum - 1, mid;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (D->Key[mid] == key)
			return mid;
		else if (D->Key[mid] > key)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}
