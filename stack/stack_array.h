#ifndef _STACK_ARRAY_H_

struct StackRecord;
typedef struct StackRecord *Stack;

Stack CreateStack(int MaxStackSize);
int IsEmpty(Stack S);
int IsFull(Stack S);
void MakeEmpty(Stack S);
void Push(int value, Stack S);
void Pop(Stack S);
int Top(Stack S);
void ReleaseStack(Stack S);

#endif /*_STACK_ARRAY_H_*/
 
#define EmptyMark (-1)
#define MinStackSize (5)

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	int *Array;
};

Stack CreateStack(int MaxStackSize)
{
	Stack S;
	if (MaxStackSize < MinStackSize)
	{
		printf("Please set a bigger Stack Size!\n"); 
		return NULL;
	}
	S = malloc(sizeof(struct StackRecord));
	if (S == NULL){ printf("out of space!\n"); return NULL; }
	S->Capacity = MaxStackSize;
	S->Array = malloc(MaxStackSize*(sizeof(int)));
	if (S->Array == NULL){ printf("out of space!\n"); return NULL; }
	MakeEmpty(S);
}
int IsEmpty(Stack S)
{
	return S->TopOfStack == EmptyMark;
}
int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity-1;
}
void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyMark;
}
void Push(int value, Stack S)
{
	if (IsFull(S))
	{
		printf("Full stack!\n"); return;
	}
	else S->Array[++S->TopOfStack] = value;
}
void Pop(Stack S)
{
	if (IsEmpty(S))
	{
		printf("Empty stack!\n"); return;
	}
	else S->TopOfStack--;
}
/*Empty stack return -1*/
int Top(Stack S)
{
	if (!IsEmpty(S))
	{
		return S->Array[S->TopOfStack];
	}
	printf("Empty stack!\n");
	return -1;
}
void ReleaseStack(Stack S)
{
	if (S != NULL)
	{
		free(S->Array);
		free(S);
	}
}
