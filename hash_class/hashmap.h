#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define null_value -1024
typedef struct node
{
	int key;
	int value;
	struct node *next;
}Node;
typedef struct
{
	int map_len;
	Node *map;
}hashmap;
hashmap* create_map(int size)
{
	int i = 0, j = 0;
	hashmap *hash_map = (hashmap*)malloc(sizeof(hashmap));
	hash_map->map_len = size;
	hash_map->map = (Node*)malloc(sizeof(Node)*hash_map->map_len);
	for (int i = 0; i < hash_map->map_len; i++)
	{
		hash_map->map[i].value = null_value;
		hash_map->map[i].next = NULL;
	}
	return hash_map;
}
void insert_data(hashmap* hash_map, int value)
{
	int site = abs(value%hash_map->map_len);
	if (hash_map->map[site].value == null_value)
	{
		hash_map->map[site].key = site;
		hash_map->map[site].value = value;
	}
	else
	{
		Node *next_node = (Node*)malloc(sizeof(Node));
		next_node->key = site;
		next_node->value = value;
		next_node->next = NULL;
		Node *temp = &(hash_map->map[site]);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = next_node;
	}
}
int search_data(hashmap* hash_map, int value)
{
	int site = abs(value % hash_map->map_len);
	Node *temp = &(hash_map->map[site]);
	while (temp != NULL)
	{
		if (temp->value == value)
			return temp->key;
		else temp = temp->next;
	}
	return -1;
}
void output_map(hashmap* hash_map)
{
	for (int i = 0; i < hash_map->map_len; i++)
	{
		Node* temp = &(hash_map->map[i]);
		while (temp != NULL)
		{
			if (temp->value != null_value)
				printf("%d ->", temp->value);
			else printf("null");
			temp = temp->next;
		}
		printf("\n");
	}
}
void main()
{
	hashmap* hash_map=create_map(5);
	output_map(hash_map);
	printf("\n");
	int datas[5] = { 12, 45, 23, 66, 18 };
	for (int i = 0; i < 5; i++)
		insert_data(hash_map, datas[i]);
	output_map(hash_map);
	printf("\n");
	printf("map have 12?\n");
	if (search_data(hash_map, 12) != -1)
		printf("got it\n");
	else printf("no\n");
	system("pause");
	return;
}
