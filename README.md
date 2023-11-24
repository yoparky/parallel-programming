# parallel-programming
A collection of parallel programming projects using OpenMPI and Cuda from OSU's parallel programming class

# projects
## openmp_simple_experiment
- This C program, utilizing OpenMP for parallel computing, is designed to measure the performance of array multiplication across multiple threads. It initializes two large arrays, A and B, each of size SIZE (which can be defined by the user), and fills them with predetermined values
## opemp_monte_carlo
- This C program uses OpenMP for parallel processing to perform a Monte Carlo simulation, a method used for estimating the probability of complex phenomena. The simulation aims to determine the probability of a certain event occurring under randomized conditions, specifically involving the placement of pins and holes.
## openmp_functional_decomp
- This C program simulates a hypothetical ecological system over a span of years (2023-2028) using OpenMP for parallel processing. It models the interaction between rabbits, rye grass, and hunters in an environment where temperature and precipitation change monthly. Each are handled by a unique thread that is synchronized using barriers before advancing a year.
## mutex_stack
- This C program uses OpenMP to demonstrate a simple parallel stack operation where multiple threads push and pop values concurrently. It's designed to test the effectiveness of using a mutex lock for ensuring thread safety in a stack operation.
## vectorized_array_mult
- This C program demonstrates the use of SIMD (Single Instruction, Multiple Data) operations and compares their performance against non-SIMD operations for vector multiplication. It is designed to showcase the efficiency gains possible through parallel processing at the CPU level.
## cuda_monte_carlo
- This C program demonstrates a Monte Carlo simulation using CUDA, a parallel computing platform and application programming interface model created by Nvidia. The simulation estimates the probability of pins fitting into holes on a plate, a problem well-suited for parallel processing.
## opencl_matrix_mult
- This C program is a demonstration of matrix multiplication using OpenCL, a framework for writing programs that execute across heterogeneous platforms consisting of CPUs, GPUs, and other processors. The program multiplies two matrices and is designed to leverage the parallel computing capabilities of GPUs for efficient computation.
## mpi_fourier_analysis
- This C program is designed for parallel Fourier analysis using MPI (Message Passing Interface), a library for parallel processing. The program is structured to analyze a large signal dataset by distributing the computation across multiple processors, thus leveraging the power of parallel computing for efficient data processing.
