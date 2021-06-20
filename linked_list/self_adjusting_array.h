#ifndef _SELF_ADJUSTING_ARRAY_H_

struct ArrayRecord;
typedef struct ArrayRecord *SelfAdj;

SelfAdj CreateSelfAdj(int MaxSize);
void AddInHeader(int value, SelfAdj S);
int Find(int value, SelfAdj S);
int Visit(int value, SelfAdj S);
int Delete(int value, SelfAdj S);
void MoveExcept(SelfAdj S);

#endif /*_SELF_ADJUSTING_ARRAY_H_*/

struct ArrayRecord
{
	int Capacity;
	int Size;
	int *Array;
};

SelfAdj CreateSelfAdj(int MaxSize)
{
	SelfAdj S = malloc(sizeof(struct ArrayRecord));
	if (S == NULL){ printf("out of space!\n"); return; }
	S->Capacity = MaxSize;
	S->Array = malloc((MaxSize)*sizeof(int));
	if (S->Array == NULL){ printf("out of space!\n"); return; }
	S->Size = 0;
}
void AddInHeader(int value, SelfAdj S)
{
	int i;
	if (S->Size == S->Capacity){ printf("Array full!\n"); return; }
	if (S->Size == 0)
	{
		S->Array[0] = value;
		S->Size++;
	}
	else
	{
		for (i = S->Size; i >= 0; i--)
		{
			S->Array[i + 1] = S->Array[i];
		}
		S->Array[0] = value;
		S->Size++;
	}
}
/*Find the first one/Find sccess return the site,Not find return -1*/
int Find(int value, SelfAdj S)
{
	int i;
	for (i = 0; i < S->Capacity; i++)
	{
		if (S->Array[i] == value)
		{
			return i;
		}
	}
	return -1;
}
/*True return 1,Flase return 0*/
int Visit(int value, SelfAdj S)
{
	int Tmp=Find(value, S);
	if (Tmp != -1)
	{
		MoveExcept(Tmp, S);
		return 1;
	}
	return 0;
}
/*Delete the first one/True return 1,Flase return 0*/
int Delete(int value, SelfAdj S)
{
	int i=0;
	int Tmp = Find(value, S);
	for (i = Tmp; i < S->Size; i++)
	{
		S->Array[i] = S->Array[i + 1];
	}
	S->Size--;
}
void MoveExcept(int Site, SelfAdj S)
{
	int i;
	int Tmp = S->Array[Site];
	for (i = Site; i > 0; i--)
	{
		S->Array[i] = S->Array[i - 1];
	}
	S->Array[0] = Tmp;
}