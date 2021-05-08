# Results

## Sequential Runtime

The [sequential model](https://github.com/boleary134h/CS205-final-project/blob/main/Website/SequentialModel.md) was run on an AWS t2.micro instance with the following specifications:

- Intel Xeon CPU ES-2676 @ 2.40GHz
- L1 cache, L2 cache, L3 cache: 64Kb, 256Kb, 30Gb
- EBS volume: 128Gb
- GCC version 9.3.0

There are **287083** documents in the CNN-DailyMail database, and the document matrices are saved in 144 txt files. Total size of all files is 6Gb. Total execution over all files takes **1361 seconds**. The figure below plots the average runtime for each section of the code: (1) read input matrices, (2) compute similarity matrix, (3) PageRank, (4) sort sentences, and (5) write output.

![img](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/sequential_runtime.png)

Computing similarity matrix takes the most time (3.43 ms) out of all steps. Interestingly, it took more time to read the matrices from the text files (1.19 ms) than to compute PageRank (0.059 ms). Sorting the sentences (0.008 ms) takes negligible time as expected, and writing the indices of the top 3 sentences to output (0.016 ms) is not a bottleneck either. 

Overall, the algorithm doesn't take long to run for each document (4.74 ms on average), but the total time for 280K documents is still noticeable. This suggests that our problem is likely to be data intensive more than compute intensive.
