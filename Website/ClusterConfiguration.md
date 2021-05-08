# Cluster Configuration

We follow a similar setup as in [Lab7_2](https://harvard-iacs.github.io/2021-CS205/labs/I7_2/) using two t2.2xlarge instances, each with 8 vCPUs. 

### Info on t2.2xlarge:
* 8 vCPUs
* 8 CPUs
* 1 thread per core
* CPU MHz of 2299.849
* CPU is Intel(R) Xeon(R) CPU E5-2686 v4 @ 2.30GHz
* Memory of 32GB
* We extended EBS storage to 48GB
* L1d cache of 32KB
* L1i cache of 32KB
* L2 cache of 256KB
* L3 cache of 46080KB

### Info on Cluster:
* 2 AWS instances of t2.2xlarge
* Number of OMP threads controlled by export OMP_NUM_THREADS=X
* Set MPI port range as 10000:10100 
* Latency: 0.461 using ping 
* Bandwith: 1.02GB/s using iperf

### Info on Operating System:
* Ubuntu 18.04.5 LTS
* Linux 5.4.0-1047-aws

### Info on Compiler:
* mpic++ - mpiexec version 3.3a2  
* g++ 7.5.0
* Compiler flags used: -fopenmp, std=c++11

### C++ Libraries Used:
* iostream
* string
* vector
* fstream
* typeinfo
* mpi.h
* iterator
* algorithm
* stdexcept
* math.h
* omp.h

