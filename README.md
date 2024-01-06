# Parallel Bar Chart Generation Project

## Overview
This project aims to develop a program for generating bar charts based on user-provided datasets. The initial implementation is sequential, allowing users to input an array of values and visualize the corresponding bar chart. Subsequently, parallel programming techniques, specifically OpenMP and MPI, are employed to enhance the efficiency of the bar chart generation process.

## Project Tasks

### 1. Sequential Bar Chart Generation
- Users input the dataset size and values.
- The program generates and displays a sequential bar chart using asterisks ('*').
- A short array is initially used for testing, serving as a baseline for performance comparison.

### 2. Parallel Bar Chart Generation with OpenMP
- OpenMP is employed to parallelize the bar chart generation process.
- Users can specify the number of threads for parallelization.
- Testing is performed on both short and long array sizes to evaluate the impact of OpenMP parallelism on performance.

### 3. Parallel Bar Chart Generation with MPI
- MPI is utilized for parallelization, allowing users to specify the number of processes.
- Similar to the OpenMP version, testing is conducted on short and long array sizes to explore parallelism using MPI.

### 4. Performance Comparison
- A comprehensive analysis is conducted to compare the performance of sequential, OpenMP, and MPI implementations.
- Key considerations include task distribution, code complexity, scalability with large datasets, and communication overhead.
- Insights gained from the performance comparison help understand the benefits and trade-offs of parallel programming techniques for efficient data visualization.
