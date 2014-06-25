Compute the largest eigenvalue and corresponding eigenvector of a large amount of 3x3 symmetric matrices being directly from a CSV file.
A producer creates a queue of matrices to process, while consumer(s) calculate eigenvalue and eigenvector of the available matrices.

Few benchmarks: run on Intel(R) Xeon(R) CPU E5-2665 0 @ 2.40GHz, compiled with g++ (see Makefile)


| # matrices | Serial (s) | Queue, 100 elems (s) | Queue, 1024 elems (s)  | OMP 2 th. (s) | OMP 4 th. (s) | OMP 8 th. (s) | 
|:----------:|:----------:|:--------------------:|:----------------------:|:-------------:|:-------------:|:-------------:|
| 10 	     |   1.72e-4  |  3.14e-4             |  4.52e-4               |    1.7e-4     |   N/A         |    N/A        | 	
| 100 	     |   3.31e-4  |  4.18e-4             |  5.44e-4               |    3.32e-4    |  3.33e-4      |   N/A         |
| 1,000      |   1.91e-3  |  1.66e-3             |  1.72e-3               |    1.87e-3    |   1.85e-3     |  1.89e-3      |
| 10,000     |   1.77e-2  |  1.31e-2             |  1.33e-2               |   1.95e-2     |   1.73e-2     |  1.74e-2      | 
| 100,000    |   1.71e-1  |  1.28e-1             |  1.27e-1               |    1.75e-1    |   1.68e-1     |  1.67e-1      | 
| 1,000,000  |   1.67     |  0                   |  1.25                  |    1.65       |   1.66        |  1.65         |


Most of time is spent reading the matrix file (in s and %age of serial run):


| # matrices | while() read (s)| Boost spirit + mmap (s) | 
|:----------:|:---------------:|:-----------------------:|
| 10         | 1.38e-4  |       1.46e-4    |
| 100        | 2.40e-4  |       2.31e-4    |
| 1,000      | 1.32e-3  |       1.22e-3    |
| 10,000     | 1.21e-2  |       1.08e-2    |
| 100,000    | 1.13e-1  |       9.86e-1    |
| 1,000,000  | 1.13    |       1.05    |

