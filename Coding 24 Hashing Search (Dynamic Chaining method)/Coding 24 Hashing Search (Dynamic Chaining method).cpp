/* Program Hashing Search(Dynamic Chaining method) can..  
    1. Random a difference data into 1 dimension Array  
    2. Create Hash Table by.. 
        -Calculate Address=K mod M+Lo  
        -Let M=50% of N 
        -if collision solve new location by "Dynamic Chaining" method 
    3. Search by key 
    4. Count a time of searching 
    5. Show each step result 
*/ 
#include <stdio.h> //use printf 
#include <conio.h> //use getch 
#include <stdlib.h> //use random 
#include <time.h> //use time 
#include <windows.h> //use Sound 
#define MaxData 100 // Define Max Data 
#define Lo 1 //Define Lo=1 
int Data[MaxData];  
int N,M,key,Addr,Times;  
bool result;  
struct Node //Declare structure of node 
{  
    int info;  
    struct Node *link;  
};  
 
struct Node *Start[MaxData],*H1,*p; // Declare pointer node 
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
    { 
        if(Data1==Data[j]) 
        return(true);  
    } 
    return(false);  
} 

void PrepareRawKey(int N) 
{  
    int i,temp;  
    srand(time(NULL)); //for difference random number in rand() 
    for (i=0;i<N;i++) 
    {  
        temp=(rand() % 989)+10; //random difference number 10..999 
        while(Duplicate(i-1,temp)) //Loop if Still Duplicate 
        temp=(rand() % 989)+10; //random again 
        Data[i]=temp; //Keep new Number 
    } //End for 
} //End Fn. 

void DispKey(int N) 
{  
    int i;  
    for(i=0;i<N;i++) 
        printf(" %2d ",Data[i]); //Show Data[] 
    printf("\n");  
} 

void CreateHead(int Head) 
{  
    int i;  
    struct Node *p;  
    for (i=1;i<=Head;i++) //Count by Number of Head 
    {  
        p=Allocate();  
        p->info=NULL;  
        p->link=NULL; //Let NEXT = NULL 
        Start[i]=p; //Let Start of each node = Address of first Node 
    } //End for 
}

void CreateHashTable(int N)  
{  
    int i;  
    struct Node *H1, *p;  
    for(i=0;i<N;i++) 
    {  
        Addr=Data[i]%M+Lo; //Calculate Address of Key (Addr=K mod M+l0) 
        H1=Start[Addr];  
        if(H1->info==NULL) //if Head Node  
            H1->info=Data[i];  
        else 
        {  
            while(H1->link!=NULL) 
                H1=H1->link;  
            p=Allocate(); //Add new Node
            p->info=Data[i];  
            p->link=NULL;  
            H1->link=p;  
        } //End if 
    } //End for 
}

void DispHashTable() 
{  
    int i;  
    struct Node *H1;  
    for(i=1;i<=M;i++) 
    {  
        H1=Start[i];  
        printf("\nAddress %2d : ",i);  
        while(H1!=NULL) 
        {  
            printf("%3d ",H1->info);  
            H1=H1->link; //Skip next Node  
        }  
    } //End for 
    printf("\n");  
}  

bool SearchHash(int key) 
{  
    struct Node *H1;  
    Addr=key%M+Lo; //Calculate Address of Key (Addr=K mod M+lo)  
    H1=Start[Addr];  
    Times=0;  
    while(H1!=NULL) 
    {  
        Times++; //Add Counter Times 
        if(H1->info==key) 
            return(true); //Found 
        else 
            H1=H1->link;  
    }  
    return(false); //NOT Found 
}

int main() 
{  
    printf("HASHING SEARCH(DYNAMIC CHAINING)\n");  
    printf("===================================================\n");  
    N=32;  
    M=N*0.50; //Let M=50% of N 
    PrepareRawKey(N);  
    printf("Raw key :\n");  
    DispKey(N); //Raw key 
    printf("----------------------------------------------------------------\n");  
    CreateHead(M); //Create Head Node 
    CreateHashTable(N);  
    while(key!=-999) 
    {  
        DispHashTable();  
        printf("----------------------------------------------------------------\n");  
        printf("\nEnter Key for Search(-999 for EXIT) = ");  
        scanf("%d",&key); //Read key from KBD 
        if(key!=-999) 
        {  
            result=SearchHash(key);  
            printf("Key Address : %d\n",Addr);  
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
