#ifndef _QUEUE_ARRAY_H_

struct QueueRecord;
typedef	struct	QueueRecord *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxSize);
void ReleaseQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(int value, Queue Q);
void Dequeue(Queue Q);

#endif /*_QUEUE_ARRAY_H_*/

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int *Array;
};

int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}
int IsFull(Queue Q)
{
	return Q->Size == Q->Capacity;
}
Queue CreateQueue(int MaxSize)
{
	Queue Q = malloc(sizeof(struct QueueRecord));
	if (Q == NULL){ printf("out of space!\n"); return NULL; }
	Q->Capacity = MaxSize;
	MakeEmpty(Q);
	Q->Array = malloc(MaxSize*(sizeof(int)));
	if (Q->Array == NULL){ printf("out of space!\n"); return NULL; }
	return Q;
}
void ReleaseQueue(Queue Q)
{
	if (Q != NULL)
	{
		free(Q->Array);
		free(Q);
	}
}
void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}
void Enqueue(int value, Queue Q)
{
	if (IsFull(Q))
	{
		printf("Full queue!\n"); return;
	}
	else
	{
		Q->Size++;
		Q->Rear = (Q->Rear++) % (Q->Capacity);
		Q->Array[Q->Rear] = value;
	}
}
void Dequeue(Queue Q)
{
	if (IsEmpty(Q))
	{
		printf("Empty queue!\n"); return;
	}
	else
	{
		Q->Size--;
		Q->Front = (Q->Front++) % (Q->Capacity);
	}
}
