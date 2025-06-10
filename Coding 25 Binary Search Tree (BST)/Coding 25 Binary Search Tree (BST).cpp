/* Program Binary Search Tree(BST) can..  
  	1. Random a difference data into 1 dimension Array  
  	2. Create Binary Search Tree. 
  	3. Search by key 
  	4. Count a time of searching 
*/ 
#include <stdio.h> //use printf 
#include <conio.h> //use getch 
#include <stdlib.h> //use random 
#include <time.h> //use time 
#include <windows.h> //use Sound 
#define MaxData 100 // Define Max Data 
int Data[MaxData];  
int N,key,Times;  
bool result;  
struct Node //Declare structure of node of Tree 
{  
  	int info;  
  	struct Node *lson,*rson;  
};  
struct Node *Start[MaxData],*Root,*p; // Declare pointer node 
Node *Allocate() //Allocate 1 node from storage pool 
{  
  	struct Node *temp;  
  	temp=(Node*)malloc(sizeof(Node)); //Allocate node by size declare 
  	return(temp);  
}  
bool Duplicate(int i,int Data1) //Check Duplication Data 
{  
  	int j;  
  	for(j=1;j<=i;j++) 
    	if(Data1==Data[j]) 
    		return(true);  
  	return(false);  
}  
void PrepareRawKey(int N) 
{  
  	int i,temp;  
  	srand(time(NULL)); //for difference random number in rand() 
  	for (i=0;i<N;i++) 
  	{  
    	temp=(rand() % 89)+10; //random difference number 10..99 
    	while(Duplicate(i-1,temp)) //Loop if Still Duplicate 
      		temp=(rand() % 89)+10; //random again 
    	Data[i]=temp; //Keep new Number 
  	} //End for 
} //End Fn. 
void DispKey(int N) 
{  
  	int i;  
  	for(i=0;i<N;i++) 
    	printf("(%2d)",i); //Show Subscript i 
  	printf("\n");  
  	for(i=0;i<N;i++) 
    	printf(" %2d ",Data[i]); //Show Data[] 
  	printf("\n");  
}  
void CreateBST(int N) 
{  
  	int i;  
  	bool Finish;  
  	struct Node *T1,*p;  
  	p=Allocate(); //Set Root Node 
  	p->info=Data[0];  
  	p->lson=NULL;  
  	p->rson=NULL;  
  	Root=p; //Set Root Node Pointer 
  	for (i=1;i<N;i++) //Count by Number of Data 
  	{  
    	T1=Root; //Let T1 point at Root Node  
    	p=Allocate();  
    	p->info=Data[i];  
    	p->lson=NULL;  
    	p->rson=NULL;  
    	Finish=false;  
    	while(!Finish) 
	    {  
	    	if(Data[i]<T1->info) 
	        	if(T1->lson==NULL) 
	        	{  
	          		//Add left Node 
	          		T1->lson=p; //Let LSON Last Node point to New Node 
	          		Finish=true; //Done  
	        	} 
	        	else 
	          		T1=T1->lson; //Skip to Left Son  
      		else 
        		if(T1->rson==NULL) 
        		{ 
		          	//Add right Node 
		          	T1->rson=p; //Let RSON Last Node point to New Node 
		          	Finish=true; //Done 
        		}  
        		else 
          			T1=T1->rson; //Skip to Right Son 
    	} //End while 
  	} //End for 
} //End Fn. 
void InOrder(struct Node *i) 
{  
  	if (i != NULL) //if i NOT NULL 
  	{  
    	InOrder(i->lson); //Call left Son by InOrder  
    	printf(" %2d",i->info); //Display INFO 
    	InOrder(i->rson); //Call Right Son by InOrder 
  	}  
}  
bool SearchBST(int key) 
{  
  	struct Node *T1;  
  	Times=0;  
  	T1=Root;  
  	while(T1!=NULL) 
  	{  
    	Times++; //Count the search time 
    	if(key==T1->info) 
      		return(true); //Found 
    	else 
      		if(key<T1->info) 
        		T1=T1->lson; //Skip T1 to Left 
      		else 
        		T1=T1->rson; //Skip T1 to Right 
  	} //End While 
  	return(false); //NOT Found 
} //End Fn. 
int main() 
{  
	printf("BINARY SEARCH TREE\n");  
  	printf("===================================================\n");  
  	N=16;  
  	PrepareRawKey(N);  
  	CreateBST(N);  
  	while(key!=-999) 
  	{  
    	printf("Raw key :\n");  
    	DispKey(N); //Raw key 
    	printf("----------------------------------------------------------------\n");  
    	printf("In Order :\n");  
    	InOrder(Root);  
    	printf("\n----------------------------------------------------------------\n");  
    	printf("\nEnter Key for Search(-999 for EXIT) : ");  
    	scanf("%d",&key); //Read key from KBD 
    	if(key!=-999) 
    	{  
      		result=SearchBST(key);  
      		printf("Searching Time : %d\n",Times);  
      		printf("Result...");  
      		if(result) 
        		printf("FOUND\n"); //if found  
      		else 
      		{  
        		Beep(600,600);  
        		printf("NOT FOUND!!\n"); //if NOT found 
      		}  
      	printf("---------------------------------------------------Searching Finished\n");  
    	} //End if 
  	} //End While 
  	return(0);  
} //End Main
