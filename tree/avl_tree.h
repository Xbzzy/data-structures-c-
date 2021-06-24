#ifndef _AVL_TREE_H_

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree CreateTree(void);
AvlTree Insert(int value, AvlTree T);
AvlTree Delete(int value, AvlTree T);
Position Find(int value, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
#endif /*_AVL_TREE_H_*/

struct AvlNode
{
	int val;
	AvlTree Left;
	AvlTree Right;
	int Height;
};
/*Avoid node is NULL*/
static int Height(Position P)
{
	if (P == NULL)
		return -1;
	else return P->Height;
}
/*P2 has a left child,Perform a rorate bewteen P2 and its left child,return new root*/
static Position SingleRotateWithLeft(Position P2)
{
	Position P1;
	P1 = P2->Left;
	P2->Left = P1->Right;
	P1->Right = P2;
	P2->Height = max(Height(P2->Left), Height(P2->Right)) + 1;
	P1->Height = max(Height(P1->Left), P2->Height) + 1;
	return P1;
}
/*P4 has a right child,Perform a rorate bewteen P3 and its right child,return new root*/
static Position SingleRotateWithRight(Position P3)
{
	Position P4;
	P4 = P3->Right;
	P3->Right = P4->Left;
	P4->Left = P3;
	P3->Height = max(Height(P3->Left), Height(P3->Right)) + 1;
	P4->Height = max(P3->Height,Height(P4->Right)) + 1;
	return P4;
}
/*P3 has a left,P3's left child has a right child,(left-right ratation)*/
static Position DoubleRotateWithLeft(Position P5)
{
	P5->Left = SingleRotateWithRight(P5->Left);
	return SingleRotateWithLeft(P5);
}
/*P3 has a right,P3's right child has a left child,(right-left ratation)*/
static Position DoubleRotateWithRight(Position P6)
{
	P6->Right = SingleRotateWithLeft(P6->Right);
	return SingleRotateWithRight(P6);
}
AvlTree CreateTree()
{
	AvlTree T = malloc(sizeof(struct AvlNode));
	if (T == NULL){ printf("out of space!\n"); return NULL; }
	return T;
}
AvlTree Insert(int value, AvlTree T)
{
	if (T == NULL)
	{
		T = malloc(sizeof(struct AvlNode));
		if (T == NULL){ printf("out of space!\n"); return NULL; }
		else
		{
			T->val = value;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (value<T->val)
	{
		T->Left = Insert(value, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
			if (value < T->Left->val)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	else if (value > T->val)
	{
		T->Right = Insert(value, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
			if (value > T->Right->val)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}
	T->Height = max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}
AvlTree Delete(int value, AvlTree T)
{
	Position TmpNode=Find(value,T);
	if (T == NULL||TmpNode==NULL)return NULL;
	else if (value < T->val)
	{
		T->Left = Delete(value, T->Left);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (Height(T->Right->Left) - Height(T->Right->Right) == -1)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}
	else if (value > T->val)
	{
		T->Right = Delete(value, T->Right);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (Height(T->Left->Left) - Height(T->Left->Right) == 1)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else
	{
		if (T->Left&&T->Right)
		{
			TmpNode = FindMin(T->Right);
			T->val = TmpNode->val;
			T->Right = Delete(T->val, T->Right);
		}
		else 
		{
			TmpNode = T;
			if (T->Left == NULL)T = T->Right;
			else if (T->Right == NULL)T = T->Left;
			free(TmpNode);
		}
	}
	if (T!=NULL) T->Height = max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}
Position Find(int value, AvlTree T)
{
	if (T == NULL)return NULL;
	else if (value<T->val)return Find(value, T->Left);
	else if (value>T->val)return Find(value, T->Right);
	else return T;
}
Position FindMin(AvlTree T)
{
	if (T->Left == NULL)return T;
	return FindMin(T->Left);
}
Position FindMax(AvlTree T)
{
	if (T->Right == NULL)return T;
	return FindMax(T->Right);
}
