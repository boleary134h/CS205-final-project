# Results

## Sequential 

The [sequential model](https://github.com/boleary134h/CS205-final-project/blob/main/Website/SequentialModel.md) was run on an AWS t2.micro instance with the following specifications:

- Intel Xeon CPU ES-2676 @ 2.40GHz
- L1 cache, L2 cache, L3 cache: 64K, 256K, 30G
- EBS volume: 48G
- g++ 7.5.0

There are **287083** documents in the CNN-DailyMail database, and the document matrices are saved in 144 txt files. Total size of all files is 6G. Total execution over all files takes **1361 seconds** (~23 minutes). The figure below plots the average runtime for each section of the code: (1) read input matrices, (2) compute similarity matrix, (3) PageRank, (4) sort sentences, and (5) write output.

![img](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/sequential_runtime.png)

Computing similarity matrix takes the most time (3.43 ms) out of all steps. Interestingly, it took more time to read the matrices from the text files (1.19 ms) than to compute PageRank (0.059 ms). Sorting the sentences (0.008 ms) takes negligible time as expected, and writing the indices of the top 3 sentences to output (0.016 ms) is not a bottleneck either. 

Overall, the algorithm doesn't take long to run for each document (4.74 ms on average), but the total time for all 280K documents still takes some time. This suggests that our problem is likely to be more data intensive than compute intensive.

## Parallelization

See details on the parallel model setup at this [link](https://github.com/boleary134h/CS205-final-project/blob/main/Website/ParallelModel.md).

Also, see details on the cluster configuration [here](https://github.com/boleary134h/CS205-final-project/blob/main/Website/ClusterConfiguration.md) and details on how to run the code [here](https://github.com/boleary134h/CS205-final-project/blob/main/Website/HowToRunCode.md).

### MPI

As mentioned previously, there are over 280K documents in the CNN-DailyMail dataset and there are 144 txt files that store the data. We utilize MPI to parallelize across the files. In other words, each MPI node gets a batch of files to compute TextRank on each of the documents within the files. These computations are relatively independent so there is little communication/synchronization that needs to occur within the cluster. The only coordination that exists is keeping track of the input and output files across all of the MPI nodes. As a result, there is near linear speedup as we alter the number of cores per instance. Using only one AWS instance, the speedup is roughly the same as the number of cores per instance (2 and 4 for 2 and 4 cores per instance, respectively). For the same number of total processes, the execution times are a bit slower using 2 AWS instances versus using 1 AWS instance. We attribute this to the overhead and communication between instances. 


| AWS Instances | Cores per Instance | Total Processes | Exec. Time (sec) | Speedup |
| ------------- | ------------------ | --------------- | ---------------- | ------- |
| 1         | 1                  | 1               | 2305.430           |  1.000    |
| 1         | 2                  | 2               | 1164.980           | 1.979    |
| 1         | 4                  | 4               | 576.182            | 4.001    |
| 2         | 1                  | 2               | 1609.11           | 1.433    |
| 2         | 2                  | 4               | 802.049            | 2.874    |
| 2         | 4                  | 8               | 403.478            | 5.714    |

![MPISpeedupPlot](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/mpi_speedup_plot.png)

In addition to analyzing the MPI model using strong scaling (above), we also analyze the model using weak scaling. To do this, we increase the problem size (# files) as well as the number of processors. We use 10, 20, and 40 files for 1, 2, and 4 processes, respectively. To alter the number of files, we changed the hardcoded number of files in main.cpp.

```cpp
int n_files = 20; // original # is 144
```

The weak scaling speedup is constant at roughly 1.0.

| AWS Instances | Cores per Instance | Total Processes | # Files | Exec. Time (sec) | Speedup |
| ------------- | ------------------ | --------------- | ------- | ---------------- | ------- |
| 1         | 1                  | 1             | 10  | 158.039           |  1.000    | 
| 1         | 2                  | 2             | 20  | 160.105           | 0.987    |
| 1         | 4                  | 4             | 40  | 163.084            | 0.969    |

![MPISpeedupPlot](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/mpi_speedup_plot_ws.png)

### Hybrid: MPI and OpenMP

For the hybrid model, MPI is used in a similar way as mentioned in the MPI section. OpenMP is used to further parallelize each TextRank computation. For each of the configurations listed below, we set the number of OMP threads to be equal to 2. The hybrid results look similar to those of the MPI results. In other words, for a given number of AWS instances and cores per instance, the execution time and speedup appear to be similar whether or not OpenMP is used. In some occasions, the use of OpenMP seems to be slower. The additional benefits from parallelizing each TextRank computation appear to be small and they are offset by the additional overhead in a shared memory setup. We believe the hybrid model exhibits little benefit because each CNN-DailyMail article is relatively small (20-30 senteces per article) and each individual TextRank computation is already relatively fast. The hybrid model is likely to produce more computational benefits if each article is much longer.

| AWS Instances | Cores per Instance | OMP Threads | Total Processes | Exec. Time (sec) | Speedup |
| ------------- | ------------------ | ----------- | --------------- | ---------------- | ------- |
| 1         | 1               | 1    | 1               | 2305.430           |  1.000    |
| 1         | 1               | 2    | 2               | 2323.35           |  0.992    |
| 1         | 2               | 2    | 4               | 1164.16           | 1.980    |
| 1         | 4               | 2    | 8               | 582.572            | 3.957    |
| 2         | 1               | 2    | 4               | 1636.17           |  1.409    |
| 2         | 2               | 2    | 8               | 819.445           |  2.813    |
| 2         | 4               | 2    | 16               | 401.661           | 5.740    |



![HybridSpeedupPlot](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/hybrid_speedup_plot.png)

The approach to analyze weak scaling is similar as described in the MPI section, however 2 OMP threads are used. Since the OpenMP parallelization does not appear to improve execution time but it is being counted as a processor, the speedup drops to about 50%.

| AWS Instances | Cores per Instance | OMP Threads | Total Processes | # Files | Exec. Time (sec) | Speedup |
| ------------- | ------------------ | ----------- | --------------- | ------- | ---------------- | ------- |
| 1         | 1               | 1    | 1              | 10 | 158.039           |  1.000    |
| 1         | 1               | 2    | 2              | 20 | 318.669           |  0.496    |
| 1         | 2               | 2    | 4              | 40 | 323.245           | 0.489    |
| 1         | 4               | 2    | 8              | 80 | 323.847            | 0.488    |


![HybridSpeedupPlot](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/hybrid_speedup_plot_ws.png)

## Summarization Evaluation

We use [Rouge](https://www.aclweb.org/anthology/W04-1013/) to evaluate the performance of our summarization method. However, it is complicated to install the original implementation, so we instead use a [python implementation](https://github.com/pltrdy/rouge). We calculated the rouge score on a subset. The score is as follows:

| Rouge-1 | Rouge-2 | Rouge-L | 
| ------------- | ------------------ | ------------------ | 
|27.34          |7.72                | 22.24              |

The score is not very ideal. However, since our model is relative simple and it is an unsupervised method, the performance is as expected.
