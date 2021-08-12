#ifndef _SKIP_LIST_H_
#define max_level 5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>

struct Node;
struct List;
typedef struct Node *Ptr_Node;
typedef struct List *SkipList;
 
SkipList CreateList();
int Insert(SkipList list, int key, int value);
int Delete(SkipList list, int key);
int Search(SkipList list, int key);

#endif /*_SKIP_LIST_H*/


struct Node
{
	int key;
	int value;
	struct Node* next[1];
};
struct List
{
	int level;
	Node *head;
};

static Node* CreateNode(int level, int key, int value)
{
	Node *tmp = (Node*)malloc(sizeof(struct Node)*level);
	tmp->key = key;
	tmp->value = value;
	return tmp;
}
SkipList CreateList()
{
	SkipList list = (SkipList)malloc(sizeof(List));
	list->level = 0;
	Node* one = CreateNode(max_level, 0, 0);
	list->head = one;
	for (int i = 0; i < max_level; i++)
		one->next[i] = NULL;
}
int RandLevel()
{
	int level = 1;
	while (rand() % 2)
		level++;
	level = (max_level>level) ? level : max_level;
	return level;
}
int Insert(SkipList list, int key, int value)
{
	Node *way_data[max_level];
	Node *pre = list->head,*last = NULL;
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
	int level = RandLevel();
	if (level > list->level)
	{
		for (int i = list->level; i < level; i++)
		{
			way_data[i] = list->head;
		}
		list->level = level;
	}
	last = CreateNode(level, key, value);
	for (int i = level-1; i >= 0; i--)
	{
		last->next[i] = way_data[i]->next[i];
		way_data[i]->next[i] = last;
	}
	return 1;
}
int Delete(SkipList list, int key)
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
	free(last);
	last = NULL;
	return 1;
}
int Search(SkipList list, int key)
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