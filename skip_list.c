#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_level 5
typedef struct node
{
	int key;
	int value;
	struct node *next[1];
}Node;
typedef struct list
{
	int level;
	Node *head;
}skip_list;
Node* create_node(int level, int key, int value)
{
	Node *temp = (Node*)malloc(sizeof(Node)*level);
	temp->key = key;
	temp->value = value;
	return temp;
}
skip_list* create_list()
{
	skip_list* list = (skip_list*)malloc(sizeof(skip_list));
	list->level = 0;
	Node* one = create_node(max_level, 0, 0);
	list->head = one;
	for (int i = 0; i < max_level; i++)
		one->next[i] = NULL;
}
int rand_level()
{
	int level = 1;
	while (rand() % 2)
		level++;
	level = (max_level>level) ? level : max_level;
	return level;
}
int insert_node(skip_list* list, int key, int value)
{
	Node* way_data[max_level];
	Node* pre = list->head, *last = NULL;
	for (int i = list->level - 1; i >= 0; i--)
	{
		while ((last = pre->next[i]) && last->key < key)
			pre = last;
		way_data[i] = pre;
	}
	if (last&&last->key == key)
	{
		last->value = value;
		return 1;
	}
	int level = rand_level();
	if (level > list->level)
	{
		for (int i = list->level; i < level; i++)
		{
			way_data[i] = list->head;
		}
		list->level = level;
	}
	last = create_node(level, key, value);
	for (int i = level-1; i >= 0; i--)
	{
		last->next[i] = way_data[i]->next[i];
		way_data[i]->next[i] = last;
	}
	return 1;
}
int del_node(skip_list *list, int key)
{
	Node *way_data[max_level];
	Node* pre = list->head, *last = NULL;
	for (int i = list->level - 1; i >= 0; i--)
	{
		while ((last = pre->next[i]) && last->key < key)
			pre = last;
		way_data[i] = pre;
	}
	if (!last || (last&&last->key != key))
	{
		printf("sry,fail to search\n");
		return -1;
	}
	for (int i = list->level - 1; i >= 0; i--)
	{
		if (way_data[i]->next[i] = last)
		{
			way_data[i]->next[i] = last->next[i];
			if (list->head->next[i] == NULL)
				list->level--;
		}
	}
	printf("delete success\n");
	free(last);
	last = NULL;
	return 1;
}
int search_key(skip_list* list, int key)
{
	Node* pre = list->head, *last = NULL;
	for (int i = list->level - 1; i >= 0; i--)
	{
		while ((last = pre->next[i]) && last->key < key)
			pre = last;
		if (last&&last->key == key)
			return last->value;
	}
	return -1;
}
void main()
{
	srand(time(0));
	int key_nums[5] = { 13, 26, 9, 41, 33 };
	skip_list* list = create_list();
	for (int i = 0; i < 5; i++)
		insert_node(list, key_nums[i], 0);
	int i=search_key(list, 13);
	if (i != -1)printf("search success\n");
	else printf("fail to search\n");
	del_node(list, 13);
	int i = search_key(list, 13);
	if (i != -1)printf("search success\n");
	else printf("fail to search\n");
}

