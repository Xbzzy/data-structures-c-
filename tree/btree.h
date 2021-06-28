#ifndef _BTREE_H_
#define MaxOrder 5
const int MaxKeyNum = MaxOrder -1;
const int MinKeyNum = (MaxOrder-1) / 2;
struct BTreeNode;
struct Result;
typedef BTreeNode *Position;
typedef BTreeNode *BTree;

BTree InitBTree(BTree B);
BTree Insert(int key, BTree B);
BTree Delete(int key, BTree B);
Result Find(int key, BTree B);
BTree CreateBTreeRoot(BTree B, int key, BTree Left, BTree Right);
BTreeNode *CreateBTreeNode();

#endif /*_BTREE_H_*/

struct BTreeNode
{
	int KeyNum;
	int Key[MaxOrder];
	struct BTreeNode *Parent;
	struct BTreeNode *Pointer[MaxOrder];
};
struct Result
{
	BTreeNode *Position;
	int Site;
};
BTree InitBTree(BTree B)
{
	B = NULL;
	return B;
}
BTree CreateBTreeRoot(BTree B,int key,BTree Left,BTree Right)
{
	B = malloc(sizeof(struct BTreeNode));
	B->KeyNum = 1;
	B->Key[1] = key;
	B->Parent = NULL;
	B->Pointer[0] = Left;
	B->Pointer[1] = Right;
	if (Left != NULL)
		Left->Parent = B;
	if (Right != NULL)
		Right->Parent = B;
	return B;
}
BTreeNode *CreateBTreeNode()
{
	BTree B = malloc(sizeof(struct BTreeNode));
	if (B == NULL){ printf("out of space!\n"); return NULL; }
	return B;
}

static int FindSite(int key, BTreeNode *B)
{
	int start=0, end=B->KeyNum-1, mid;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (B->Key[mid] == key)
			return mid;
		else if (B->Key[mid] > key)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}
static int FindInsertSite(int key, BTreeNode *B)
{
	int i = 0;
	while (key < Data[i+1] && i<B->KeyNum)
		i++;
	return i;
}
static BTreeNode *FindInsertNode(int key, BTree B)
{
	int site = FindInsertSite(key, B);
	if (B->Pointer[site-1] != NULL)
		B= FindInsertNode(key, B->Pointer[site-1]);
	else return B;
}
static void InsertNode(BTreeNode *B,int site, int key, BTreeNode *Tmp)
{
	int i;
	for (i = B->KeyNum; i > site; i--)
	{
		B->Key[i + 1] = B->Key[i];
		B->Pointer[i + 1] = B->Pointer[i];
	}
	B->Key[site] = key;
	B->Pointer[site] = Tmp;
	B->KeyNum++;
}
static void SplitNode(BTreeNode *B,BTreeNode *Tmp)
{
	int i;
	int split = (MaxOrder + 1) / 2;
	Tmp = malloc(sizeof(struct BTreeNode));
	if (Tmp == NULL){ printf("out of space!\n"); return; }
	Tmp->Pointer[0] = B->Pointer[split];
	for (i = split + 1; i <= MaxOrder; i++)
	{
		Tmp->Key[i - split] = B->Key[i];
		Tmp->Pointer[i - split] = B->Pointer[i];
	}
	Tmp->KeyNum = B->KeyNum - split;
	Tmp->Parent = B->Parent;
	for (i = 0; i < B->KeyNum - split; i++)
	{
		if (Tmp->Pointer[i] != NULL)
			Tmp->Pointer[i]->Parent = Tmp;
	}
	B->KeyNum = split - 1;
}

BTree Insert(int key, BTree B)
{
	int i,site;
	BTreeNode *Tmp = NULL;
	if (B == NULL)
		B = CreateBTreeRoot(B, key, NULL, NULL);
	else
	{
		BTree Insertnode = FindInsertNode(key, B);
		while (1)
		{
			site = FindInsertSite(key, Insertnode);
			InsertNode(Insertnode,site, key, Tmp);
			if (Insertnode->KeyNum <= MaxOrder)
			{
				return B;
			}
			else
			{
				SplitNode(Insertnode, Tmp);
				if (Insertnode->Parent == NULL)
				{
					BTree NewRoot;
					NewRoot = CreateBTreeRoot(NewRoot, Insertnode->Key[(MaxOrder + 1) / 2], Insertnode, Tmp);
					return NewRoot;
				}
				else
				{
					Insertnode = Insertnode->Parent;
				}
			}
		}
	}
}
static void MoveToLeft(BTreeNode *B,int site)
{
	int i;
	BTreeNode *left = B->Pointer[site - 1];
	BTreeNode *move = B->Pointer[site];
	left->KeyNum++;
	left->Key[left->KeyNum] = B->Key[site];
	B->Key[site] = move->Key[site];
	move->KeyNum--;
	for (i = 1; i <= move->KeyNum; i++)
		move->Key[i] = move->Key[i + 1];
}
static void MoveToRight(BTreeNode *B, int site)
{
	int i;
	BTreeNode *right = B->Pointer[site + 1];
	BTreeNode *move = B->Pointer[site];
	for (i = right->KeyNum; i > 0; i--)
		right->Key[i + 1] = right->Key[i];
	right->Key[1] = B->Key[site];
	right->KeyNum++;
	B->Key[site] = move->Key[move->KeyNum];
	move->KeyNum--;
}
static void Combine(BTreeNode *B, int site)
{
	int i;
	BTreeNode *master = B->Pointer[site - 1];
	BTreeNode *slave = B->Pointer[site];
	for (i = 0; i <= slave->KeyNum; i++)
	{
		master->KeyNum++;
		master->Key[master->KeyNum] = slave->Key[i];
	}
	for (i = site; i < B->KeyNum; i++)
		B->Key[i] = B->Key[i + 1];
	B->KeyNum--;
	free(slave);
}
static void Remove(BTreeNode *B, int site)
{
	int i;
	for (i = site + 1; i <= B->KeyNum; i++)
		B->Key[i - 1] = B->Key[i];
	B->KeyNum--;
}
void AdjustBTree(BTreeNode *B, int site)
{
	if (site == 0)
	{
		if (B->Pointer[1]->KeyNum > MinKeyNum + 1)
			MoveToLeft(B,1);
		else
			Combine(B,1);
	}
	else if (site == B->KeyNum)
	{
		if (B->Pointer[site - 1]->KeyNum > MinKeyNum + 1)
			MoveToRight(B,site-1);
		else
			Combine(B,site);
	}
	else if (B->Pointer[site - 1]->KeyNum > MinKeyNum + 1)
		MoveToRight(B,site);
	else if (B->Pointer[site + 1]->KeyNum > MinKeyNum + 1)
		MoveToLeft(B,site+1);
	else
		Combine(B,site);
}
BTree Delete(int key, BTree B)
{
	int sign,site;
	BTreeNode *Tmp;
	Tmp = FindInsertNode(key, B);
	site = FindInsertSite(key, Tmp->Parent);
	sign = FindSite(key, Tmp);
	if (sign == -1)return NULL;
	else
	{
		Remove(Tmp, sign);
		if (Tmp->KeyNum < MinKeyNum+1)
			AdjustBTree(Tmp->Parent, site);
	}
	return B;
}
Result Find(int key, BTree B)
{
	Result R;
	if (B == NULL)
	{
		printf("Null tree!\n");
		return NULL;
	}
	BTreeNode *Tmp = FindInsertNode(key, B);
	int site = FindSite(key, Tmp);
	R.Site = site;
	R.Position = Tmp;
	return R;
}
