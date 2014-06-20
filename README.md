Compute the largest eigenvalue and corresponding eigenvector of a large amount of 3x3 symmetric matrices being directly from a CSV file.
A producer creates a queue of matrices to process, while consumer(s) calculate eigenvalue and eigenvector of the available matrices.

Few benchmarks

| # matrices | Serial (s) | Queue, 100 elems (s) | Queue, 1024 elems (s) |
|:----------:|:----------:|:--------------:|:---------------:|
| 10 	     |   1.72e-4  |  3.14e-4       |  4.52e-4              |
| 100 	     |   3.31e-4  |  4.18e-4       |  5.44e-4              |
| 1,000      |   1.91e-3  |  1.66e-3       |  1.72e-3              |
| 10,000     |   1.77e-2  |  1.31e-2       |  1.33e-2              |
| 100,000    |   1.71e-1  |  1.28e-1       |  1.27e-1              |
| 1,000,000  |   1.67     |  1             |  1.25              |

