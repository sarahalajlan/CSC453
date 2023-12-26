#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, numprocs;
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    int size; // Total number of elements
    if (rank == 0) {
        printf("Enter the size of the array: ");
        scanf("%d", &size);
    }

    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int numArray[size];
    int maxValue = 0;
    double start_time, end_time;

    if (rank == 0) {
        srand(time(NULL)); // Seed the random number generator
        for (int i = 0; i < size; i++) {
            numArray[i] = (rand() % size) + 1;
        }
    }

    MPI_Bcast(numArray, size, MPI_INT, 0, MPI_COMM_WORLD);

    start_time = MPI_Wtime();
    int elements_per_proc = size / numprocs;
    int extra_elements = size % numprocs;
    int start = rank * elements_per_proc + (rank < extra_elements ? rank : extra_elements);
    int end = start + elements_per_proc + (rank < extra_elements ? 1 : 0);

    // Find local max value
    int localMax = 0;
    for (int i = start; i < end; i++) {
        if (numArray[i] > localMax) {
            localMax = numArray[i];
        }
    }

    // Find global max using MPI_Reduce with MPI_MAX operation
    MPI_Reduce(&localMax, &maxValue, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // Broadcast global max value to all processes
    MPI_Bcast(&maxValue, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Initialize count array
    int numCountArray[maxValue + 1]; // +1 because we're using 1-based indexing for values

    for (int i = 0; i <= maxValue; i++) {
        numCountArray[i] = 0;
    }

    // Count occurrences
    for (int i = start; i < end; i++) {
        numCountArray[numArray[i] - 1]++;
    }

    int globalNumCounts[maxValue * numprocs];
    for (int i = 0; i < maxValue * numprocs; i++) {
        globalNumCounts[i] = 0;
    }

    MPI_Gather(numCountArray, maxValue, MPI_INT, globalNumCounts, maxValue, MPI_INT, 0, MPI_COMM_WORLD);

    // Master process prints the bar chart
    if (rank == 0) {
        // Print the final bar chart from process 0
        for (int i = 0; i < maxValue; i++) {
            printf("Data Point %d: ", i + 1);
            for (int j = 0; j < numprocs; j++) {
                for (int k = 0; k < globalNumCounts[j * maxValue + i]; k++) {
                    printf("*");
                }
            }
            printf("\n");
        }
    }

    // Stop the timer
    end_time = MPI_Wtime();

    // Print the execution time
    if (rank == 0) {
        printf("Execution time: %f seconds\n", end_time - start_time);
    }

    // Finalize MPI
    MPI_Finalize();
    return EXIT_SUCCESS;
}
