#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define null_value -1024
typedef struct list_node
{
	int value;//结点值
	struct list_node *pre;//前驱结点指针
	struct list_node *next;//后继结点指针
}data_node;
typedef struct
{
	int max;//缓存中页面上限
	int acount;//当前缓存中页面个数
	data_node *head;//头结点指针
	data_node *tail;//尾结点指针
}data_list;
typedef struct hashnode
{
	int key;
	int value;
	data_node *data;//链表中值对应的页面
	struct hashnode *next;//下一个hash结点指针

}hash_node;
typedef struct
{
	int len;
	hash_node *map;//hashmap数组指针
}hash_map;

data_list* create_list();//初始化缓存表
hash_map* create_map();//初始化hashmap
void add_data(data_list *list, hash_map *hashmap, int value1);//向缓存表中插入新页面并映射到hashmap中
void del_data(data_list *list, hash_map *hashmap);//删除最近最久未使用页面并消除其在hashmap中的映射
data_node* search_data(hash_map *hashmap, data_list *list, int value2);//在hashmap中查找指定页号
void refresh_data(data_list *list, data_node *newest);//访问页面后刷新缓存表
void output_hashmap(hash_map *hashmap);//输出hashmap数组情况
void output_list(data_list *list);//输出缓存表情况
void visit(data_list *list, hash_map *hashmap, int page);//访问页面
void output(data_list *list, hash_map *hashmap);//输出LRU情况

data_list* create_list()
{
	data_list *list = (data_list*)malloc(sizeof(data_list));
	if (list == NULL)exit(1);
	printf("输入页面上限数：\n");
	scanf("%d", &list->max);
	list->acount = 0;
	data_node *head_node = (data_node*)malloc(sizeof(data_node));
	list->head = head_node;
	if (head_node == NULL)exit(1);
	data_node *tail_node = (data_node*)malloc(sizeof(data_node));
	list->tail = tail_node;
	if (tail_node == NULL)exit(1);
	head_node->value = 0;
	head_node->pre = NULL;
	head_node->next = tail_node;
	tail_node->value = 0;
	tail_node->pre = head_node;
	tail_node->next = NULL;
	return list;
}
hash_map* create_map()
{
	int i;
	hash_map* hashmap = (hash_map*)malloc(sizeof(hash_map));
	printf("输入hash数组结点数:\n");
	scanf("%d", &hashmap->len);
	hashmap->map = (hash_node*)malloc(hashmap->len*sizeof(hash_node));
	for (i = 0; i<hashmap->len; i++)
	{
		hashmap->map[i].key = i;
		hashmap->map[i].value = null_value;
		hashmap->map[i].data = NULL;
		hashmap->map[i].next = NULL;
	}
	return hashmap;
}
void add_data(data_list *list, hash_map *hashmap, int value1)
{
	int site;
	data_node *node = (data_node*)malloc(sizeof(data_node));
	if (node == NULL)exit(1);
	node->value = value1;
	node->pre = list->head;
	node->next = list->head->next;
	list->head->next = node;
	site = abs(value1%hashmap->len);
	if (hashmap->map[site].value == -1024)
	{
		hashmap->map[site].key = site;
		hashmap->map[site].value = value1;
		hashmap->map[site].data = node;
		return;
	}
	else
	{
		hash_node *newnode = (hash_node*)malloc(sizeof(hash_node));
		newnode->key = site;
		newnode->value = value1;
		newnode->data = node;
		newnode->next = NULL;
		hash_node *temp = &(hashmap->map[site]);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
		return;
	}
}
void del_data(data_list *list, hash_map *hashmap)
{
	int site, del_value;
	data_node *tail_node = list->tail;
	del_value = tail_node->value;
	data_node *del = tail_node->pre;
	data_node *del_pre = del->pre;
	del_pre->next = tail_node;
	tail_node->pre = del_pre;
	free(del);
	site = abs(del_value%hashmap->len);
	if (hashmap->map[site].value == del_value)
	{
		hashmap->map[site].value = null_value;
		hashmap->map[site].data = NULL;
		return;
	}
	hash_node *temp = &(hashmap->map[site]);
	while (temp->next->value != del_value)
		temp = temp->next;
	free(temp->next);
	temp->next = NULL;
}
data_node* search_data(hash_map *hashmap, data_list *list, int value2)
{
	int key2;
	key2 = abs(value2%hashmap->len);
	hash_node *temp = &(hashmap->map[key2]);
	while (1)
	{
		if (temp->value == value2)
			return temp->data;
		temp = temp->next;
		if (temp == NULL)
			return NULL;
	}
}
void refresh_data(data_list *list, data_node *newest)
{
	data_node *head_node = list->head;
	data_node *head_next = head_node->next;
	head_next->pre = newest;
	head_node->next = newest;
	newest->pre->next = newest->next;
	newest->next->pre = newest->pre;
	newest->pre = head_node;
	newest->next = head_node->next;
}
void output_hashmap(hash_map *hashmap)
{
	int i;
	for (i = 0; i<hashmap->len; i++)
	{
		hash_node *temp = &(hashmap->map[i]);
		while (temp != NULL)
		{
			if (temp->value != null_value)
			{
				printf("%d -> ", temp->value);
			}
			else
			{
				printf("NULL");
			}
			temp = temp->next;
		}
		printf("\n");
	}
}
void output_list(data_list *list)
{
	int i;
	data_node *temp = list->head;
	printf("head -> ");
	for (i = 0; i<list->acount; i++)
	{
		temp = temp->next;
		printf("%d -> ", temp->value);
	}
	printf("tail\n");
}
void visit(data_list *list, hash_map *hashmap, int page_num)
{
	data_node *page_table = search_data(hashmap, list, page_num);
	if (page_table == NULL)
	{
		printf("缓存表中不存在,即将插入该页面。\n");
		if (list->acount == list->max)
		{
			del_data(list, hashmap);
			add_data(list, hashmap, page_num);
		}
		else
		{
			add_data(list, hashmap, page_num);
			list->acount++;
		}
	}
	else
	{
		printf("缓存表中已存在,即将更新缓存表。\n");
		refresh_data(list, page_table);
	}
}
void output(data_list *list, hash_map *hashmap)
{
	printf("hashmap:\n");
	output_hashmap(hashmap);
	printf("cachetable:\n");
	output_list(list);
}
void main()
{
	data_list *list = create_list();
	hash_map *hashmap = create_map();
	printf("初始化完成！\n");
	visit(list, hashmap, 7);
	output(list, hashmap);
	visit(list, hashmap, 4);
	output(list, hashmap);
	visit(list, hashmap, 1);
	output(list, hashmap);
	visit(list, hashmap, 3);
	output(list, hashmap);
	visit(list, hashmap, 7);
	output(list, hashmap);
	system("pause");
}