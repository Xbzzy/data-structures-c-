#ifndef _STACK_LIST_

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack(void);
void MakeEmpty(Stack S);
void Push(int value, Stack S);
void Pop(Stack S);
int Top(Stack S);

#endif /*_STACK_LIST_*/

struct Node
{
	int val;
	PtrToNode Next;
};

int IsEmpty(Stack S)
{
	return S->Next == NULL;
}
Stack CreateStack()
{
	Stack S = malloc(sizeof(struct Node));
	if (S == NULL) printf("out of space!\n");
	S->Next = NULL;
	return S;
}
void MakeEmpty(Stack S)
{
	if (S == NULL)printf("Please use CreateStack first!\n");
	else
	{
		while (!IsEmpty(S))
			Pop(S);
	}
}
void Push(int value, Stack S)
{
	PtrToNode TmpNode;
	TmpNode = malloc(sizeof(struct Node));
	if (TmpNode == NULL)printf("out of space!\n");
	else
	{
		TmpNode->val = value;
		TmpNode->Next = S->Next;
		S->Next = TmpNode;
	}
}
void Pop(Stack S)
{
	PtrToNode FirstNode;
	if (IsEmpty(S))printf("Empty Stack!\n");
	else
	{
		FirstNode = S->Next;
		S->Next = S->Next->Next;
		free(FirstNode);
	}
}
/* Empty Stack Top==-1 */
int Top(Stack S)
{
	if (!IsEmpty(S))return S->Next->val;
	else
	{
		printf("Empty Stack!\n");
		return -1;
	}
}
