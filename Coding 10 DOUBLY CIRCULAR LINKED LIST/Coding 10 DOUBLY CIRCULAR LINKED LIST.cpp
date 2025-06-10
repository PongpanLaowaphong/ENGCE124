/* Program create DOUBLY CIRCULAR LINKED LIST by Pongpan Laowaphong 
 1. Create Node N Nodes 
 2. Insert node before/after data as defined 
 3. Delete node before/itself/after data as defined 
 4. Show address of Node 
Note.- Not allow to delete the HEAD Node  
*/ 
#include <stdio.h> //use printf 
#include <conio.h> //use getch 
#include <stdlib.h> //usemolloc 
#define HeadInfo -999 // Define data of Head Node 
 
struct Node { //Declare structure of node 
    int info;  
    struct Node *llink;  
    struct Node *rlink;  
};  
struct Node *H, *H1, *p, *q; // Declare pointer node 
int i,j,k,n,data;  
char ch;  
 
Node *Allocate() {//Allocate 1 node from storage pool 
    struct Node *temp;  
    temp=(Node*)malloc(sizeof(Node)); //Allocate node by size declare 
    return(temp);  
}  

void CreateNNode(int n) {//Create N Node put data and link its 
    int i,temp;  
    H1=H; //Start H1 at here 
    for (i=1;i<=n;i++) {//Count N Node 
        p=Allocate(); //Allocate New Node 
        temp=1+rand() % 99; //random difference number 1..99  
        p->info=temp; //Put random data in to node 
        H1->rlink=p; //Link first node to second node 
        p->llink=H1; //LLink point back to predecessor node 
        H1=p; //Let H1 point to last node 
        H1->rlink=H; //Set rlink of H1 point to HEAD NODE 
        H->llink=H1; //Set LLink of H point to H1  
    }  
}

void ShowAllNode() 
{ 
    printf("H = %x\n",H); //Display address of pointer H 
    p=H; //Set start point of p pointer 
    i=1; //set start value of counter 
    if (p->rlink != H ) //if have more node 
    {  
        p=p->rlink; //Skip pointer to first node 
        while (p != H) //While if P <> H 
            {  
            printf("%d) : %x\t",i,p); //Show COUNTER and POINTER 
            printf("LLINK : %x\t",p->llink); //Show lLINK 
            printf("INFO : %d\t",p->info); //Show INFO 
            printf("RLINK : %x\n",p->rlink); //Show RLINK 
            p=p->rlink; //Skip to next node 
            i++; //Skip Counter 
        } //End While 
    } //End if 
} //Enf Fn. 

void InsertAfter(int data1) 
{ 
    int temp; //Temporary variable 
    if (H->rlink == H)  
        printf("Linked List have no node!!..\n");  
    else 
    {  
        H1=H->rlink; //Let H1 point at 1st node 
        while (H1->info != HeadInfo) // Search for the data while H1 loop back to HAED Node 
        {  
            if (H1->info == data1) //if Found 
            {  
                p=Allocate(); //Allocat one node from storage pool 
                printf("\nInsert data : " ); //Input data for insert 
                scanf("%d",&temp); //Read from KBD 
                p->info=temp; // Entry temporary data into INFO of node 
                if (H1->rlink == H) //IF H1 is Last Node 
                {  
                    p->rlink=H; //Let p Point to HEAD Node 
                    H->llink=p; //Let H Point to Last Node  
                }  
                else 
                {  
                    p->rlink=H1->rlink; //Change pointer 1st for insert node (FAR to NEAR) 
                    H1->rlink->llink=p; //LLINK(RLINK(H1))=p  
                } 
                p->llink=H1; //LLINK(P)=H1 
                H1->rlink=p; //RLINK(H1)=p
            } //End if 
            H1=H1->rlink; //Skip H1 to next node  
        } //End while 
    } //End IF 
} //End Fn. 
  
void InsertBefore(int data1) 
{ 
    int temp; //Temporary variable 
    if (H->rlink==H)  
        printf("Linked List have no node!!..\n");  
    else 
    {  
        H1=H->rlink; //Let H1 point at 1st node 
        while (H1->info != HeadInfo) // Search for the data while H1 loop back to HAED Node 
        {  
            if (H1->info == data1) //if Found 
            {  
                p=Allocate(); //Allocate one node from storage pool 
                printf("\nInsert data : " ); //Input data for insert 
                scanf("%d",&temp); //Read from KBD 
                p->info=temp; // Entry temporary data into INFO of node 
                if (H1->llink == H) //First Node 
                {  
                    p->llink=H; //LLINK(p) Point to HEAD Node 
                    H->rlink=p; //RLINK(H) Point to p 
                }  
                else 
                {  
                    H1->llink->rlink=p; //RLINK(LLINK(H1))=p 
                    p->llink=H1->llink; //LLINK(p)=LLINK(H1) 
                }  
                H1->llink=p;//LLINK(H1)=p 
                p->rlink=H1;//RLINK(P)=H1 
            } //End if 
            H1=H1->rlink; //Skip H1 to next node  
        } //End while 
    } //End IF 
} //End Fn 
  
void DeleteBefore(int data1) 
{ 
    int temp; //Temporary variable 
    if (H->rlink==H)  
        printf("Linked List have NO NODE!!..\n");
    else 
    {  
        H1=H->rlink; //Let H1 point at 1st node 
        while (H1->info != HeadInfo) // Search for the data while H1 loop back to HAED Node 
        {  
            if (H1->info == data1) //if Found 
            {  
                if (H1->llink==H) //If no more node 
                    printf ("No more node before here,Can't delete it!!!\n");  
                else 
                {  
                    p=H1->llink; //Mark at node for Delete 
                    H1->llink=p->llink; //If not set link of H1 point same address of p  
                    p->llink->rlink=H1; //RLINK(LLINK(P)) 
                    free(p); //Free node to storage pool 
                } //End if2 
            } //End if1 
            H1=H1->rlink; //Skip H1 to next node  
        } //End while 
    } //End IF 
} //End Fn.  
  
void DeleteSelf(int data1) 
{ 
    int temp; //Temporary variable 
    if (H->rlink==H)  
        printf("Linked List have NO NODE!!..\n");  
    else 
    {  
        H1=H->rlink; //Let H1 point at 1st node 
        while (H1->info != HeadInfo) // Search for the data while H1 loop back to HAED Node 
        {  
            if (H1->info == data1) //if Found 
            {  
                p=H1; //Mark at node for Delete 
                if(p->llink==H && p->rlink==H) //If only one node 
                {  
                    H->llink=H; //Set HEAD Pointer point it self 
                    H->rlink=H;  
                }  
                else 
                {  
                    p->llink->rlink=p->rlink; //RLINK(LLINK(H1))=RLINK(P) 
                    p->rlink->llink=p->llink; //LLINK(RLINK(H1))=LLINK(P)
                }  
                free(p); //Free node to storage pool 
            } //End if1 
            H1=H1->rlink; //Skip H1 to next node  
        } //End while 
    } //End IF 
 } //End Fn.  
  
void DeleteAfter(int data1) 
{ 
    int temp; //Temporary variable 
    if (H->rlink==H)  
        printf("Linked List have NO NODE!!..\n");  
    else 
    {  
        H1=H->rlink; //Let H1 point at 1st node 
        while (H1->info != HeadInfo) // Search for the data while H1 loop back to HAED Node 
        {  
            if (H1->info == data1) //if Found 
            {  
                if (H1->rlink==H) //If no more node 
                    printf ("No more node from here,Can't delete it!!!\n");  
                else 
                {  
                    p=H1->rlink; //Mark at node for Delete 
                    H1->rlink=p->rlink; //If not set link of H1 point same address of p  
                    p->rlink->llink=H1;  
                    free(p); //Free node to storage pool 
                } //End if2 
            } //End if1 
            H1=H1->rlink; //Skip H1 to next node  
        } //End while 
    } //End IF 
} //End Fn 
  
int main() //MAIN Fn. 
{  
    p=Allocate();// Create HEAD NODE 
    p->info=HeadInfo; //Special data for Head node 
    p->llink=p; p->rlink=p; //Let both Link point to itself 
    H=p; //Let H Point to Head node 
    n=10; //Set amount of node 
    CreateNNode(n); //Call Fn. Create N nodes
    printf("PROGRAM DOUBLY CIRCULAR LINKED LIST \n");  
    printf("================================== \n");  
    printf("All Data in Linked List \n");  
    ShowAllNode(); //Call Fn. Show all node 
    ch=' ';  
    while (ch != 'E') 
    { 
        printf("MENU>> [B:InsertBefore  A:InsertAfter\n");  
        printf(" O:DeleteBefore X:Deleteitself D:DeleteAfter E:Exit]\n");  
        //printf(" D:DeleteAfter E:Exit]");  
        ch=getch();  
        switch (ch) 
        { 
        case 'B' :  printf("\nInsert Before data : " ); //Input data for insert after 
            scanf("%d",&data);  
            InsertBefore(data); //Call Fn. Insert after data 
            printf("\nAll Data in Linked List AFTER INSERTED\n");  
            ShowAllNode(); //Call Fn. Show all node  
            break;  
        case 'A' :  printf("\nInsert After data : " ); //Input data for insert after 
            scanf("%d",&data);  
            InsertAfter(data); //Call Fn. Insert after data 
            printf("\nAll Data in Linked List AFTER INSERTED\n");  
            ShowAllNode(); //Call Fn. Show all node  
            break;  
        case 'O' :  printf("\nDelete Before data : " ); //Input data for Delete after 
            scanf("%d",&data);  
            DeleteBefore(data); //Call Fn. Delete after data 
            printf("\nAll Data in Linked List AFTER DELETED\n");  
            ShowAllNode(); //Call Fn. Show all node  
            break;  
        case 'X' :  printf("\nDelete ItSelf data : " ); //Input data for Delete after 
            scanf("%d",&data);  
            DeleteSelf(data); //Call Fn. Delete after data 
            printf("\nAll Data in Linked List ITSELF DELETED\n");  
            ShowAllNode(); //Call Fn. Show all node  
            break;  
        case 'D' :  printf("\nDelete After data : " ); //Input data for Delete after 
            scanf("%d",&data);  
            DeleteAfter(data); //Call Fn. Delete after data 
            printf("\nAll Data in Linked List AFTER DELETED\n"); 
            ShowAllNode(); //Call Fn. Show all node  
            break;  
        } // End Switch...case 
    } //End While */ 
    return(0);  
} //End MAIN
