Compute the largest eigenvalue and corresponding eigenvector of a large amount of 3x3 symmetric matrices being streamed to a fifo or standard input.
A producer creates a queue of matrices to process, while consumer(s) calculate eigenvalue and eigenvector of the available matrices.

Few benchmarks

| # matrices | Serial (s) | Queue, 100 (s) | Queue, 1024 (s) |
|:----------:|:----------:|:--------------:|:---------------:|
| 10 	     |   1        |  1             |  1              |
| 100 	     |    1       |  1             |  1              |
| 1,000      |     1      |  1             |  1              |
| 10,000     |      1     |  1             |  1              |
| 100,000    |       1    |  1             |  1              |
| 1,000,000  |        1   |  1             |  1              |

