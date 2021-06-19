#ifndef _LINKED_LIST_H_

struct Node;
typedef struct Node *Ptr_Node;
typedef Ptr_Node List;
typedef Ptr_Node Position;

List CreateEmptyList(List L);
Position Find(int value, List L);
Position FindPre(int value, List L);
int Delete(int value, List L);
void Insert(int value, List L, Position P);
void DeleteList(List L);

#endif /*_LINKED_LIST_H_*/

struct Node
{
	int val;
	Position Next;
};

List CreateEmptyList()
{
	List L = malloc(sizeof(struct Node));
	if(L==NULL){printf("out of space!\n");return;}
	L->Next = NULL;
	return L;
}
Position Find(int value, List L)
{
	Position P = L;
	while (P->Next != NULL&&P->val != value)
		P = P->Next;
	return P;
}
Position FindPre(int value, List L)
{
	Position P = L;
	while (P->Next != NULL&&P->Next->val != value)
		P = P->Next;
	return P;
}
/*successfully delete return 1,not found return -1*/
int Delete(int value, List L)
{
	Position Tmp;
	Position P = FindPre(value, L);
	if (P->Next != NULL)
	{
		Tmp = P->Next;
		P->Next = Tmp->Next;
		free(Tmp);
		return 1;
	}
	else return -1;
}
/*insert after position p*/
void Insert(int value, List L, Position P)
{
	Position Tmp=malloc(sizeof(struct Node));
	if (Tmp == NULL) {printf("out of space!\n");return;}
	Tmp->val = value;
	Tmp->Next = P->Next;
	P->Next = Tmp;
}
void DeleteList(List L)
{
	Position P, Tmp;
	P = L->Next;
	L->Next = NULL;
	while (P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}
