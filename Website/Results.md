# Results

## Parallelization

### MPI


| AWS Instances | Cores per Instance | Total Processes | Exec. Time (sec) | Speedup |
| ------------- | ------------------ | --------------- | ---------------- | ------- |
| 1         | 1                  | 1               | 2305.430           |  1.000    |
| 1         | 2                  | 2               | 1164.980           | 1.979    |
| 1         | 4                  | 4               | 576.182            | 4.001    |
| 2         | 1                  | 2               | 1609.11           | 1.433    |
| 2         | 2                  | 4               | 802.049            | 2.874    |
| 2         | 4                  | 8               | 403.478            | 5.714    |

![MPISpeedupPlot](mpi_speedup_plot.png)

### Hybrid: MPI and OpenMP

| AWS Instances | Cores per Instance | OMP Threads | Total Processes | Exec. Time (sec) | Speedup |
| ------------- | ------------------ | ----------- | --------------- | ---------------- | ------- |
| 1         | 1               | 1 |   | 1               | 2305.430           |  1.000    |
| 1         | 1               | 2 |   | 2               | 2323.35           |  0.992    |
| 1         | 2               | 2 |   | 4               | 1164.16           | 1.980    |
| 1         | 4               | 2 |   | 8               | 582.572            | 3.957    |
| 2         | 1               | 2 |   | 4               | 1636.17           | 1.409    |
| 2         | 2               | 2 |   | 8               | 819.445            | 2.813    |
| 2         | 4               | 2 |   | 16              | 401.661            | 5.740    |

![HybridSpeedupPlot](hybrid_speedup_plot.png)

