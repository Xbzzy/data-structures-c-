#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define null_value -1024;
int table_len = 0;
typedef struct 
{
	int *data;
	int count;
}table;
int create_hashtable(table *one)
{
	printf("input table_len£º\n");
	scanf("%d", &table_len);
	one->data = (int*)malloc(table_len*(sizeof(int)));
	for (int i = 0; i < table_len; i++)
		one->data[i] = null_value;
	return 1;
}
int hash(int key)
{
	return key%table_len;
}
void insert_key(table *one, int key)
{
	int site = hash(key);
	while (one->data[site] != -1024)
		site = (site + 1) % table_len;
	one->data[site] = key;
}
int search_key(table *one, int key)
{
	int site = hash(key);
	while (one->data[site] != key)
	{
		site = (site + 1) % table_len;
		if (one->data[site] == -1024 || site == hash(key));
		return -1;
	}
	return 1;
}
void output_hashtable(table *one)
{
	for (int i = 0; i < table_len; i++)
		printf("%d  ", one->data[i]);
	printf("\n");
}
void main()
{
	table* hashtable = (table*)malloc(sizeof(table));
	int test[10] = { 1, 3, 7, 23, 43, 52, 62, 14, 32, 25 };
	create_hashtable(hashtable);
	output_hashtable(hashtable);
	for (int i = 0; i < 10; i++)
		insert_key(hashtable, test[i]);
	output_hashtable(hashtable);
	printf("table have 8?\n");
	int result = search_key(hashtable, 8);
	if (result == 1)printf("got it\n");
	else printf("no\n");
	system("pause");
	return;
}