#ifndef _QUEUE_LIST_H_

struct Node;
struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;

int IsEmpty(Queue Q);
Queue CreateQueue(int MaxSize);
void ReleaseQueue(Queue Q);
void Enqueue(int value, Queue Q);
void Dequeue(Queue Q);

#endif /*_QUEUE_LIST_H_*/

struct Node
{
	int val;
	Position Next;
};
struct QueueRecord
{
	Position Front;
	Position Rear;
	int Size;
};

int IsEmpty(Queue Q)
{
	return Q-> Size == 0;
}
Queue CreateQueue()
{
	Queue Q = malloc(sizeof(struct QueueRecord));
	if (Q == NULL){ printf("out of space!\n"); return NULL; }
	Q->Size = 0;
	Q->Front = NULL;
	Q->Rear = NULL;
	return Q;
}
void ReleaseQueue(Queue Q)
{
	Position P, Tmp;
	P = Q->Front;
	Q->Front = NULL;
	while (P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}
void Enqueue(int value, Queue Q)
{
	Position TmpNode = malloc(sizeof(struct Node));
	if (TmpNode == NULL){ printf("out of space!\n"); return; }
	TmpNode->val = value;
	TmpNode->Next = NULL;
	if (Q->Rear == NULL)
	{
		Q->Front = TmpNode;
		Q->Rear = TmpNode;
		Q->Size++;
	}
	else
	{
		Q->Rear->Next = TmpNode;
		Q->Rear = TmpNode;
		Q->Size++;
	}
}
void Dequeue(Queue Q)
{
	if (IsEmpty(Q))
	{
		printf("Empty queue!\n");
		return;
	}
	Position Tmp;
	Tmp = Q->Front->Next;
	free(Q->Front);
	Q->Front =Tmp;
	Q->Size--;
}