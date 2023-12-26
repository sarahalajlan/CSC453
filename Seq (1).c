#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int size = 2000;
    int numArray[size];
    double times;
    double total_s = 0;
    double time_spent_each[10];

    printf("Enter the dataset values (the values are entered randomly from 1 to 2000):\n");

    // Initialize the array with random values
    for(int i =0 ;i<10;i++){
    for (int i = 0; i < size; i++) {
        numArray[i] = rand() % 2000+ 1;
    }

    
        int maxValueS = 1;
        clock_t beginS = clock();

        for (int i = 0; i < size; i++) {
            if (numArray[i] > maxValueS) {
                maxValueS = numArray[i];
            }
        }

        int numCountArrayS[maxValueS + 1];

        for (int i = 1; i <= maxValueS; i++) {
            int numCountS = 0;

            for (int j = 0; j < size; j++) {
                if (i == numArray[j]) {
                    numCountS++;
                }
            }

            numCountArrayS[i] = numCountS;
        }

        printf("--- Bar chart ---\n");

        for (int i = 1; i <= maxValueS; i++) {
            printf("\nData Point %d: ", i);
            for (int j = 0; j < numCountArrayS[i]; j++) {
                printf("*");
            }
        }

        clock_t endS = clock();
        double time_spentS = (double)(endS - beginS) / CLOCKS_PER_SEC;
        time_spent_each[i]= time_spentS;
        total_s += time_spentS;

 }  
 for(int i =0 ;i<10;i++)
 printf("\nTime for run %i Sequential %f seconds \n",(i+1) ,(time_spent_each[i]));
    
   printf("\nTook %f seconds to execute Sequential\n", (total_s/10));


    return 0;
}
