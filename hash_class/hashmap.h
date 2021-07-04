#ifndef _HASHMAP_H_
#define default_val -1024

struct HashNode;
typedef struct HashNode *Position;
struct Map;
typedef struct Map *HashMap;

HashMap InitMap(int maxsize);
Position CreateNode(int value);
void Insert(HashMap hashmap, int value);
Position Find(HashMap hashmap, int value);

#endif /*_HASHMAO_H_*/

struct HashNode
{
	int val;
	struct HashNode *next;
};
struct Map
{
	int len;
	struct HashNode *map;
};
HashMap InitMap(int maxsize)
{
	int i = 0;
	HashMap hashmap = malloc(sizeof(struct Map));
	if (hashmap == NULL){
		printf("out of space!\n");
		return NULL;
	}
	hashmap->len = maxsize;
	hashmap->map = malloc((sizeof(struct HashNode))*maxsize);
	if (hashmap->map == NULL){
		printf("out of space!\n");
		return NULL;
	}
	for (int i = 0; i < maxsize; i++){
		hashmap->map[i].val = default_val;
		hashmap->map[i].next = NULL;
	}
	return hashmap;
}
Position CreateNode(int site,int value)
{
	HashNode *node = malloc(sizeof(struct HashNode));
	if (node == NULL){
		printf("out of space!\n");
		return NULL;
	}
	node->val = value;
	node->next = NULL;
}
void Insert(HashMap hashmap, int value)
{
	int site;
	site = abs(value%hashmap->len);
	if (hashmap->map[site].val == default_val){
		hashmap->map[site].val = value;
	}
	else
	{
		HashNode *tmp = &(hashmap->map[site]);
		while (tmp->next != NULL){
			tmp = tmp->next;
		}
		Positon next_node = CreateNode(site, value);
		tmp->next = next_node;
	}
}
Position Find(HashMap hashmap, int value)
{
	int site = abs(value % hashmap->len);
	Position tmp = &(hashmap->map[site]);
	while (tmp != NULL)
	{
		if (tmp->val == value)
			return tmp;
		else tmp = tmp->next;
	}
	return NULL;
}

