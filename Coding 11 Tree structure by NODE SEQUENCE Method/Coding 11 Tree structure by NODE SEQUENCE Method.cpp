/* Program create Tree structure by "NODE SEQUENCE Method".  
Can shows the result when traversaled by Pongpan Laowaphong
 1. Pre Order 
 2. In Order 
 3. Post Order 
 4. Can use for 5 Level maximum of tree (N=31) 
*/ 
#include <stdio.h> //use printf 
#include <conio.h> //use getch 
#include <stdlib.h> //use random 
#include <math.h> //use pow 
#define MaxNode 100 // Define Max Node of Tree  
int N,data[MaxNode]; // Declare Array for keep data of Tree 
char ch;  
 
void CreateTreeNS(int n) 
{  
    int i,temp;  
    for (i=1;i<=n;i++) 
    {  
        temp=1+rand() % 99; //random difference number 1..99 
        data[i]=temp;  
    }  
}  
  
void ShowArray() 
{  
    int i=1;  
    while (data[i] != NULL) 
    {  
        printf("[%i]%d ",i,data[i]); i++;  
    }  
    printf("\n==============================================================================\n");  
}  
  
void ShowTree() 
{  
    int j,level,start,ends;  
    j=1;  
    level=1; //Start al Level 1 
    printf("\n");  
    while (data[j] != NULL) 
    {  
        start=pow(2,level)/2; //Calculate START Node of this level 
        ends=pow(2,level)-1; //Calculate END Node of this level 
        for (j=start;j<=ends;j++) 
        { 
 
            if(data[j] != NULL) 
            {  
                switch (level) 
                {  
                    case 1 : printf("%40d",data[j]);  
                                break;  
                    case 2 : if (j==2)  
                                printf("%20d",data[j]);  
                             else 
                                printf("%40d",data[j]);   
                             break;   
                    case 3 : if(j==4)  
                                printf("%10d",data[j]);   
                             else  
                                printf("%20d",data[j]); 
                             break;   
                    case 4 : if(j==8)  
                                printf("%5d",data[j]);   
                             else 
                                printf("%10d",data[j]);  
                             break;   
                    case 5 : if(j==16) 
                                printf("%d",data[j]);  
                             else 
                                printf("%5d",data[j]); 
                             break;  
                }  
            }  
        } 
        printf("\n\n"); //Line feed 
        level++;  
    }  
}  
  
void PreOrder(int i)
{ 
    int info,lson,rson;  
    info=data[i]; // Root info 
    if (info != NULL) //if INFO NOT NULL 
    {  
        printf(" %d",data[i]); //Display INFO 
        lson=2*i; //Calculate LSON 
        rson=2*i+1; //Calculate RSON 
        PreOrder(lson); //Call left Son by PreOrder 
        PreOrder(rson); //Call Right Son by PreOrder 
    }  
}  
  
void InOrder(int i) 
{  
    int info,lson,rson;  
    info=data[i]; // Root info 
    if (info != NULL) //if INFO NOT NULL 
    {  
        lson=2*i; //Calculate LSON 
        rson=2*i+1; //Calculate RSON 
        InOrder(lson); //Call left Son by InOrder 
        printf(" %d",data[i]); //Display INFO 
        InOrder(rson); //Call Right Son by InOrder 
    }  
}  
  
void PostOrder(int i) 
{  
    int info,lson,rson;  
    info=data[i]; // Root info 
    if (info != NULL) //if INFO NOT NULL 
    {  
        lson=2*i; //Calculate LSON 
        rson=2*i+1; //Calculate RSON 
        PostOrder(lson); //Call left Son by PostOrder 
        PostOrder(rson); //Call Right Son by PostOrder 
        printf(" %d",data[i]); //Display INFO 
    }  
}  
  
int main() 
{  
    N=31;  
    CreateTreeNS(N); //Create N Node 
    while (ch != 'E') 
    {  
        printf("\nTREE (NODE SEQUENCE)\n");  
        printf("==================================\n");  
        ShowArray();  
        ShowTree();  
        printf("\nMENU => P:PreOrder I:InOrder O:PostOrder E:Exit");  
        printf("\n-------------------------------------------------------------------------\n");  
        ch=getch(); 
        switch (ch) 
        {  
            case 'P' :  ShowTree();  
                        printf("PRE ORDER TRAVERSAL : ");  
                        PreOrder(1);  
                        printf("\n"); //Line feed 
                        break;  
            case 'I' :  ShowTree();  
                        printf("IN ORDER TRAVERSAL : ");  
                        InOrder(1);  
                        printf("\n"); //Line feed 
                        break;  
            case 'O' :  ShowTree();  
                        printf("POST ORDER TRAVERSAL : ");  
                        PostOrder(1);  
                        printf("\n"); //Line feed 
                        break;  
        } //End Switch...case 
    } //End While 
    return(0);  
}//End MAIN
