# Instructions on How to Run the Code

### Setup AWS Cluster

We followed a similar setup as in [Lab7_2](https://harvard-iacs.github.io/2021-CS205/labs/I7_2/) to set up a cluster with two t2.2xlarge instances, each with 8 vCPUs. One change we did make was to increase the EBS volume size to 48GB because of the data size. An example of how this is done can be seen in [Lab_5](https://harvard-iacs.github.io/2021-CS205/labs/I5/I5.pdf). 

### Get the data

The data that has been processed into sentence representations via python is stored in a Google Drive. We created a shell script to download the data from the Google drive onto the AWS instance. The shell script is in our git repo and is called download_gdrive_data.sh. 

First copy shell script onto AWS instance. One way of doing this is to first clone git repo on local computer using:

	git clone https://github.com/boleary134h/CS205-final-project.git

Then copy shell script using scp:

```bash
scp -i [AWS_KEY] download_gdrive_data.sh mpiuser@master:/home/mpiuser/cloud
```

In the AWS instance:

```bash
chmod +x download_gdrive_data.sh
./download_gdrive_data.sh
sudo install zip
unzip data_zip
mv cnndm_result1 data
```

Create folders within mpiuser@master:/home/mpiuser/cloud to store the results:

```bash
mkdir result_mpi
mkdir result_hybrid
```

### Get the code

While not the only way, one way to get the code onto the AWS instance is to first clone the code locally and then copy it to the instance. Assuming the repo was not already cloned:

	git clone https://github.com/boleary134h/CS205-final-project.git

Then the necessary code can be copied over to the AWS instance. For example:

```bash
scp -i [AWS_KEY] -r MPI mpiuser@master:/home/mpiuser/MPI
scp -i [AWS_KEY] -r Hybrid mpiuser@master:/home/mpiuser/Hybrid
```

### MPI

We use makefiles to execute the MPI and Hybrid code. To be able to use makefiles, install make:

```bash
sudo apt install make
```

Make sure that the instances are able to communicate with each other through the port range 10000-10100: 

```bash
export MPICH_PORT_RANGE=10000:10100
export MPIR_CVAR_CH3_PORT_RANGE=10000:10100
```

So that we are using the same configuration and compiler, we use the MPI code to find the serial time used in speedup comparisons:

```bash
cd MPI
make
cp textrank ~/cloud
cd ~/cloud
mpirun -np 1 ./textrank
```

Note, we also confirmed that this time is similar if we were to run the a version of the serial code using g++.

To execute using 1 AWS instance, specify the number of total processes to use. For example, to use 4 processes:

```bash
cd MPI
make
cp textrank ~/cloud
cd ~/cloud
mpirun -np 4 ./textrank
```

To execute using 2 AWS instances, specify the number of total processes to use on the master and node1. For to use a total of 4 processes: 

```bash
cd MPI
make
cp textrank ~/cloud
cd ~/cloud
mpirun -np 4 -hosts master,node1 ./textrank
```

### Hybrid

Unlike in the MPI case, the makefile for the hybrid configuration includes the -fopenmp comiler flag.

To indicate the number of OpenMP threads, use the command below (command shown is using 2 threads):

```bash
export OMP_NUM_THREADS=2
```

To execute using 1 AWS instance, specify the number of total processes to use. For example, to use 4 processes (not including the OMP threads):

```bash
cd Hybrid
make
cp textrank ~/cloud
cd ~/cloud
mpirun -np 4 ./textrank
```

To execute using 2 AWS instances, specify the number of total processes to use on the master and node1. For example, to use a total of 4 processes (not including the OMP threads): 

```bash
cd Hybrid
make
cp textrank ~/cloud
cd ~/cloud
mpirun -np 4 -hosts master,node1 ./textrank
```

