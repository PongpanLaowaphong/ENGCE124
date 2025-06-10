#include <stdio.h> // Use printf() 
#include <conio.h> // Use getch() 

int Base, Exponent, result; //declare base, exponent and result

// Recursive function to calculate M^N
int Power(int M, int N) {
    if (N == 0) {
        printf("...............Roll Back Point\n");
        return 1; // Base case: M^0 = 1
    } else {
        printf("%2d^%2d = %2d * %2d^%2d\n", M, N, M, M, N-1); // Display before recursion
        int partial_result = Power(M, N - 1); // Recursive call
        printf("%2d^%2d = %2d * %3d = %5d\n", M, N, M, partial_result, M * partial_result); // Display after recursion
        return M * partial_result; // Return a result from M * partial_result
    }
}

int main() {
    printf("RECURSIVE (POWER) PROGRAM\n");
    printf("==========================\n");
    while (1) {
        printf("Enter Base (-999 to END) : ");
        scanf("%d", &Base);
        if (Base == -999) break; // end program with -999

        printf("Enter Exponent (-999 to END) : ");
        scanf("%d", &Exponent);
        if (Exponent == -999) break; // end program with -999

        if (Exponent >= 0) {
            printf("M^N = M * M^(N-1)\n");
            printf("-------------\n");
            result = Power(Base, Exponent); // Recursive call
            printf("\nAnswer %d^%d = %d\n", Base, Exponent, result);
            printf("------------Finished\n");
            getch();
        }
    }
    return 0;
}
