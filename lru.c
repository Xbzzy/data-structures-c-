#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define null_value -1024
typedef struct list_node
{
	int value;//���ֵ
	struct list_node *pre;//ǰ�����ָ��
	struct list_node *next;//��̽��ָ��
}data_node;
typedef struct
{
	int max;//������ҳ������
	int acount;//��ǰ������ҳ�����
	data_node *head;//ͷ���ָ��
	data_node *tail;//β���ָ��
}data_list;
typedef struct hashnode
{
	int key;
	int value;
	data_node *data;//������ֵ��Ӧ��ҳ��
	struct hashnode *next;//��һ��hash���ָ��

}hash_node;
typedef struct
{
	int len;
	hash_node *map;//hashmap����ָ��
}hash_map;

data_list* create_list();//��ʼ�������
hash_map* create_map();//��ʼ��hashmap
void add_data(data_list *list, hash_map *hashmap, int value1);//�򻺴���в�����ҳ�沢ӳ�䵽hashmap��
void del_data(data_list *list, hash_map *hashmap);//ɾ��������δʹ��ҳ�沢��������hashmap�е�ӳ��
data_node* search_data(hash_map *hashmap, data_list *list, int value2);//��hashmap�в���ָ��ҳ��
void refresh_data(data_list *list, data_node *newest);//����ҳ���ˢ�»����
void output_hashmap(hash_map *hashmap);//���hashmap�������
void output_list(data_list *list);//�����������
void visit(data_list *list, hash_map *hashmap, int page);//����ҳ��
void output(data_list *list, hash_map *hashmap);//���LRU���

data_list* create_list()
{
	data_list *list = (data_list*)malloc(sizeof(data_list));
	if (list == NULL)exit(1);
	printf("����ҳ����������\n");
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
	printf("����hash��������:\n");
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
		printf("������в�����,���������ҳ�档\n");
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
		printf("��������Ѵ���,�������»����\n");
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
	printf("��ʼ����ɣ�\n");
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