# Parallel Model

As discussed in the [Problem Statement](https://github.com/boleary134h/CS205-final-project/blob/main/Website/ProblemStatement.md), our initial thinking was that extractive text summarization is both a big data and a big compute problem. It is a big data problem because datasets like CNN-DailyMail contain hundreds of thousands of text documents. It is a big compute problem because parts of the TextRank algorithm are compute intensive, such as the computation of similarity scores between sentences. This part of TextRank is quadratic in the number of sentences.

While it is possible to use Spark for a problem like this, we chose to explore a hybrid model with MPI and OpenMP to address the big data and big compute aspects of TextRank. We use MPI to partition the documents across all of the compute nodes, where each compute node executes the TextRank algorithm on a set of documents. We use OpenMP to parallelize aspects of the TextRank algorithm, such as the sentence similarity computation.

## MPI

As mentioned previously, we use MPI to partition the documents across the compute nodes within the AWS cluster. Each of these partitions is relatively independent, so we should expect close to linear speedup. We attempt to make the workload as even as possible by giving each compute node the same number of input files. For example, if there were four compute nodes and 100 files, then each of the four compute nodes would handle 25 of the files.

See below for a portion of the code in main.cpp that partitions the input files and uses MPI:

```cpp
// hardcode path names
string data_path = "./data/";
string output_path = "./result_mpi/";
string file_type = ".txt";
string output_file_prefix = "output_";

// hardcode number of files
int n_files = 144;

// initial MPI and get rank and size
int rank, size;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

// for timing
double tstart, tend;

// Split files into roughly equal chunks
int ioffset, nper;
nper    = (n_files+size-1)/size;
ioffset = rank*nper;
int n_files_partition;
if (rank == size-1) {
    n_files_partition = n_files - ioffset;
}
else {
	n_files_partition = nper;
}

// figure out which input/output files belong to that compute node
tstart = MPI_Wtime();
vector<string> inputFileNames;
vector<string> outputFileNames;
inputFileNames.resize(n_files_partition);
outputFileNames.resize(n_files_partition);
for (int f = 0; f < n_files_partition; f++) {
	inputFileNames[f] = data_path + to_string(f+ioffset) + file_type;
	outputFileNames[f] = output_path + output_file_prefix + to_string(f+ioffset) + file_type;

}

// iterate over every document in set
for (int f = 0; f < n_files_partition; f++) { 
	/*

	Code that executes textrank algorithm for each document within file

	*/
}
// Use MPI_Barrier to make sure all nodes have finished
MPI_Barrier(MPI_COMM_WORLD);
tend = MPI_Wtime();
if (rank == 0) {
    cout << "Total wall time is: " << tend-tstart << endl;
}

MPI_Finalize();
```  

## OpenMP

The shared memory aspect of our setup uses OpenMP to parallelize computations within the TextRank algorithm. As mentioned in the [Sequential](https://github.com/boleary134h/CS205-final-project/blob/main/Website/SequentialModel.md) section, the TextRank algorithm is a sequence of three key steps: computing the similarity matrix between sentences, using PageRank to find the sentence centrality scores, and sorting the sentences by their centrality scores. 

    for each matrix:
        computeSimilarityMatrix(); //pairwise sentence "similarity" scores
        computePageRank(); //find sentence "centrality" score
        sortSentences(); //sort by centrality score and pick top X sentences

We use OpenMP to parallelize the first two steps, computing the similarity matrix and the centrality scores. Both of these steps can be seen in textrankOperations.cpp. 

#### Sentence Similarity

As noted in the [analysis](https://github.com/boleary134h/CS205-final-project/blob/main/Website/Results.md) of the sequential runtime, the sentence similarity computation is the most time consuming step of the TextRank algorithm for this dataset. We use OpenMP to parallelize this computation.

```cpp
#pragma omp parallel for shared(similarityMatrix,n_dim) private (i,j) 
for (int i=0; i<n_dim; i++)
{
	for (int j=0; j<n_dim; j++)
	{
		if (i==j) {
			// fill diagonals with 0s
			similarityMatrix[i][j] = 0;
		} else if (i < j) {
			similarityMatrix[i][j] = cosineSimilarity(sentenceInput[i], sentenceInput[j]);
		} else {
			similarityMatrix[i][j] = cosineSimilarity(sentenceInput[j], sentenceInput[i]);
		}
	}
}
```

Note, the sequential time analysis uses a simplification of the above else statement to reduce the number of cosine similarity computations:

```cpp
else {
	similarityMatrix[i][j] = similarityMatrix[j][i];
}
```

However, we explicity execute all of these cosine similarity computations for the MPI model, the hybrid model, and in finding the serial time for the speedup analysis. When using OpenMP, we do not want to access a part of the similarityMatrix in one thread that has not been computed in another thread. We use this logic for the MPI model and finding the serial time to stay consistent.   

#### PageRank Centrality

The iteration component of the PageRank algorithm cannot be parallelized, however there are several for loops within each iteration that can be parallelized using OpenMP. One example of this is the double for loop that updates each centrality score based on the centrality scores of the neighbors within the graph.

```cpp
#pragma omp parallel for shared(temp_centrality,cs,transition,n_dim) private(i,j)
for (int i = 0; i < n_dim; i++) {
	for (int j = 0; j < n_dim; j++) {
		temp_centrality[i] += cs[j].score*transition[j][i];
	}
}
```

## Hybrid


The hybrid model uses both MPI and OpenMP as described above.




