/* Program Binary Search can..  
    1. Random a difference data into 1 dimension Array and Sort it 
    2. Search by key 
    3. Count a time of searching 
    4. Show each step result 
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
    int i,j,temp;  
    srand(time(NULL)); //for difference random number in rand() 
    for (i=1;i<=N;i++) 
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
    for(i=1;i<=N;i++) 
        printf("(%2d)",i); //Show Subscript i
    printf("\n");  
    for(i=1;i<=N;i++) 
        printf(" %2d ",Data[i]); //Show Data[] 
    printf("\n");  
}  
     
void BubbleSort(int N) //Ascending Sort 
{  
    int i,j,temp;  
    for(i=1;i<=N-1;i++) //loop forward 
    {  
        if(Data[i]>Data[i+1]) //if not true position 
        {  
        j=i+1; //loop backward 
            while(Data[j]<Data[j-1]) //while if remain bubble 
            {  
                temp=Data[j-1]; //swap data 
                Data[j-1]=Data[j];  
                Data[j]=temp;  
                j--; //count down j 
            } //end while 
        } //end if 
    } //end for 
} //end Fn. 
 
bool BinarySearch(int Key1) 
{  
    int L,R,Mid;  
    L=1;  
    R=N;  
    Times=0; //Initial Time for search 
    while(L<=R) 
    {  
        Mid=(L+R)/2; //Calculate Middle 
        Times++; //Count Searching Time 
        printf("L : %2d ",L);  
        printf("R : %2d ",R);  
        printf("Mid : %2d ",Mid);  
        printf("Searching Time : %d\n",Times);  
        if(Key1==Data[Mid]) 
            return(true); //if found 
        else 
        { 
            if(Key1<Data[Mid]) 
                R=Mid-1; //Move R 
            else 
                L=Mid+1; //Move L 
        } 
    } //End while 
    return(false); //If not found 
} //End Fn. 
 
int main() 
{  
    printf("BINARY SEARCH\n");  
    printf("===================================================\n");  
    N=32;  
    PrepareRawKey(N);  
    printf("Raw key :\n");  
    DispKey(N); //Raw key 
    BubbleSort(N);  
    printf("----------------------------------------------------------------\n");  
    while(key!=-999) 
    {  
        printf("Sorted Key :\n");  
        DispKey(N); //Sorted Key  
        printf("\nEnter Key for Search(-999 for EXIT) = ");  
        scanf("%d",&key); //Read key from KBD 
        if(key!=-999) 
        {  
            result=BinarySearch(key); //Call Binary Search 
            if(result) 
                printf("Result...FOUND\n"); //if found 
            else 
            {  
                Beep(600,600);  
                printf("Result...NOT FOUND!!\n"); //if NOT found  
            }  
            //printf("Searching Time : %d\n",Times); 
            printf("---------------------------------------------------Searching Finished\n");  
        } //End if 
    } //End While 
    return(0);  
} //End Main
