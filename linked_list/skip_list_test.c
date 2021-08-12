#include"skip_list.h"
void InsertTest(SkipList list){
	int i,count;
	for(i=0;i<10;i++){
		count+=Insert(list,i,1);
	}
	assert(count==10);
	return;
}
void DeleteTest(SkipList list){
	int i,count;
	for(i=0;i<5;i++){
		count+=Delete(list,i);
	}
	assert(count==5);
	return;
}
void SearchTest(SkipList list){
	int i,count;
	for(i=5;i<10;i++){
		count+=Search(list,i);
	}
	assert(count==5);
	return;
}
void TimeTest(SkipList list){
	int i,random;
	double cost_time;
	clock_t start,end;
	start=clock();
	for(i=0;i<10000;i++){
		Insert(list,i,i);
	}
	for(i=0;i<10000;i++){
		Delete(list,i);
	}
	end=clock();
	cost_time=(double)(end-start)/CLOCKS_PER_SEC;
	printf("10000 times operation cost: %f",cost_time);
}
void main(){
	srand((unsigned)time(NULL));
	SkipList list = CreateList();
	InsertTest(list);
	DeleteTest(list);
	SearchTest(list);
	TimeTest(list);
	system("pause");
	return;
}

