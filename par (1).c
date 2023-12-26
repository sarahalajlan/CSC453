#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int size = 2000;
    int numArray[size];
    int numThreads;
    double timet;
    double total_p = 0;
    double time_spent_each[10];

    printf("Enter the dataset values (the values are entered randomly from 1 to 2000):\n");
    printf("Enter number of threads: ");
    scanf("%d" , &numThreads);

    // Initialize the array with random values
    for(int i =0 ;i<10;i++){
    for (int i = 0; i < size; i++) {
        numArray[i] = rand() % 2000 + 1;
    }

   
        int maxValue = 1;
        double begin = omp_get_wtime();

        #pragma omp parallel for reduction(max : maxValue) num_threads(numThreads)
        for (int i = 0; i < size; i++) {
            if (numArray[i] > maxValue) {
                maxValue = numArray[i];
            }
        }

        int numCountArray[maxValue + 1];

        #pragma omp parallel for num_threads(numThreads)
        for (int i = 1; i <= maxValue; i++) {
            int numCount = 0;

            #pragma omp parallel for reduction(+:numCount) num_threads(numThreads)
            for (int j = 0; j < size; j++) {
                if (i == numArray[j]) {
                    numCount++;
                }
            }

            numCountArray[i] = numCount;
        }

       
        printf("--- Bar chart ---\n");

        
        for (int i = 1; i <= maxValue; i++) {
            printf("\nData Point %d: ", i);
           #pragma omp parallel for num_threads(numThreads) 
            for (int j = 0; j < numCountArray[i]; j++) {
                printf("*");
            }
        }
        double end = omp_get_wtime();
        double time_spent = (double)(end - begin);
        time_spent_each[i]= time_spent;
        total_p += time_spent;

        
    
}

for(int i =0 ;i<10;i++)
 printf("\nTime for run %i parallel OpenMP %f seconds \n",(i+1) ,(time_spent_each[i]));
 
    printf("\nNumber of thread %d Took %f seconds to execute parallel OpenMP \n",numThreads, (total_p/10));
  

    return 0;
}
