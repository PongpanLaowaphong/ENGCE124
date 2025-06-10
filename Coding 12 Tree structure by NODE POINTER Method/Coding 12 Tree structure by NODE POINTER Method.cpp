/* Program create Tree structure by "NODE POINTER Method".  
Can shows the result when traversal by Pongpan Laowaphong
1. Pre Order 
2. In Order 
3. Post Order 
Note.- Use for 5 Level maximum of tree (N=31) 
*/ 
#include <stdio.h> //use printf 
#include <conio.h> //use getch 
#include <stdlib.h> //use random, malloc  
#include <math.h> //use pow 
#define MaxNode 40  

struct Node {//Declare structure of Tree node 
    int info;  
    struct Node *lson;  
    struct Node *rson;  
};  

struct Node *T, *address[MaxNode]; // Declare pointer T of Tree node 
int i,N,info[MaxNode];  
char ch; 

Node *Allocate() {//Allocate 1 node from storage pool and return pointer of node 
    struct Node *temp;  
    temp=(Node*)malloc(sizeof(Node)); //Allocate node by size declare 
    return(temp);  
}  

void CreateTreeNP(int n) { 
    int i,temp,Father; 
    struct Node *p, *FatherPT;  
    T=NULL; //Set start of T Pointer 
    for (i=1;i<=n;i++){ 
        p=Allocate(); // Allocate NODE p 
        temp=1+rand() % 99; //random difference number 1..99 
        info[i]=temp; //Keep data for Check Correcting of Sequence 
        address[i]=p; //Keep Address of Node Sequence 
        p->info=temp; //Keep data to INFO 
        p->lson=NULL; //Set default LSON=NULL 
        p->rson=NULL; //Set default RSON=NULL 
        if (T==NULL) { //Check for T=NULL? 
            T=p; //Set T point to first node for begining of Treer 
        }  
        else
        { 
            Father=(i/2); //Calculate FATHER 
            FatherPT=address[Father]; //Get pointer of Father Node 
            if(FatherPT->lson == NULL) 
                FatherPT->lson=p; //Link LSON to new node 
            else 
                FatherPT->rson=p; //link RSON to new node 
        }  
    }  
}  
  
void ShowTree(){ 
    int j,level,start,ends;  
    j=1;  
    level=1; //Start al Level 1 
    printf("\n");  
    while (info[j] != NULL) { 
    start=pow(2,level)/2; //Calculate START Node of this level 
    ends=pow(2,level)-1; //Calculate END Node of this level 
    for (j=start;j<=ends;j++) 
        if(info[j] != NULL) { 
            switch (level) { 
                case 1 : printf("%40d",info[j]);  
                        break;  
                case 2 : if (j==2) 
                            printf("%20d",info[j]);  
                        else 
                            printf("%40d",info[j]);  
                        break;  
                case 3 : if(j==4) 
                            printf("%10d",info[j]);  
                        else 
                            printf("%20d",info[j]);
                             break;  
                case 4 : if(j==8) 
                            printf("%5d",info[j]);  
                        else 
                            printf("%10d",info[j]); 
                        break;  
                case 5 : if(j==16) 
                            printf("%d",info[j]);  
                        else 
                            printf("%5d",info[j]); 
                        break;  
            }  
        } 
        printf("\n"); //Line feed 
        level++;  
    }  
}  
  
void PreOrder(struct Node *i) 
{  
    if (i != NULL) {//if i NOT NULL 
        printf(" %d",i->info); //Display INFO 
        PreOrder(i->lson); //Call left Son by PreOrder 
        PreOrder(i->rson); //Call Right Son by PreOrder 
    }  
}  
  
void InOrder(struct Node *i) 
{  
    if (i != NULL) { //if i NOT NULL 
        InOrder(i->lson); //Call left Son by InOrder  
        printf(" %d",i->info); //Display INFO 
        InOrder(i->rson); //Call Right Son by InOrder 
    }  
}  
  
void PostOrder(struct Node *i) 
{  
    if (i != NULL) {//if i NOT NULL 
        PostOrder(i->lson); //Call left Son by PostOrder 
        PostOrder(i->rson); //Call Right Son by PostOrder 
        printf(" %d",i->info); //Display INFO 
    }  
}  

int main() 
{
    N=31;  
    CreateTreeNP(N);  
    while (ch != 'E') //Loop until 'E' Pressed 
    {  
        printf("\nPROGRAM TREE(Node Pointer) \n");  
        printf("================================== \n");  
        printf("N : %d\n",N);  
        printf("Sequence of data : ");  
        for (i=1;i<=N;i++) //Show Data Sequence 
            printf("%d ",info[i]);  
        ShowTree(); //Show tree structure 
        printf("\nMENU => P:PreOrder I:InOrder O:PostOrder E:Exit"); 
        printf("\n-------------------------------------------------------------------------\n");  
        ch=getch();  
        switch (ch) 
        {  
            case 'P' :  printf("PRE ORDER TRAVERSAL : ");  
                        PreOrder(T);  
                        printf("\n-------------------------------------------------------------------------\n");  
                        break;  
            case 'I' :  printf("IN ORDER TRAVERSAL : ");  
                        InOrder(T);  
                        printf("\n-------------------------------------------------------------------------\n");  
                        break;  
            case 'O' :  printf("POST ORDER TRAVERSAL : ");  
                        PostOrder(T);  
                        printf("\n-------------------------------------------------------------------------\n");  
                        break;  
        } //End Switch...case 
    } //End While 
    return(0);  
}//End MAIN 
