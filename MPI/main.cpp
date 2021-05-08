#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <mpi.h>

#include "textrank.hpp"
using namespace std;

int main(int argc, char **argv)
{   
	// path names
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

    /* Print a diagnostic message */
    if (rank == 0)
        printf("Processes: %d\n", size);

    /* Split files into chunks */
    int ioffset, nper;
    nper    = (n_files+size-1)/size;
    ioffset = rank*nper;
    // nloc    = (rank == size-1) ? (n-ioffset) : nper+1;
    int n_files_partition;
    if (rank == size-1) {
        n_files_partition = n_files - ioffset;
    }
    else {
    	n_files_partition = nper;
    }

    tstart = MPI_Wtime();
    vector<string> inputFileNames;
    vector<string> outputFileNames;
    inputFileNames.resize(n_files_partition);
    outputFileNames.resize(n_files_partition);
    for (int f = 0; f < n_files_partition; f++) {
    	inputFileNames[f] = data_path + to_string(f+ioffset) + file_type;
    	outputFileNames[f] = output_path + output_file_prefix + to_string(f+ioffset) + file_type;

    }
    // inputFileNames[0] = "/data/0.txt"
    // inputFileNames[1] = "/data/1.txt"
    
    
    // inputFileNames[0] = "/data/0.txt"
    // inputFileNames[1] = "/data/1.txt"

    // iterate over every document
    for (int f = 0; f < n_files_partition; f++) { 
    	// cout << inputFileNames[f];
		int size[2] = { 0 };
		int n_doc = 0;
		// string out_filename = "output_0.txt";

		ifstream infile;
		// infile.open("0.txt");
		infile.open(inputFileNames[f]);
		infile >> n_doc;

		// We loop over all documents in current file
		// Documents are processed one at a time
		// Output is the indices of the top 10 sentences
		for (int doc = 0; doc < n_doc; doc++) {

			for (int i = 0; i <= 1; i++) {
				infile >> size[i];
			}
			// cout << size[0] << " "<< size[1] << endl;

			// Read vectors representations of sentences in current document
			vector<vector<double>> sentenceInput;
			sentenceInput.resize(size[0]);
			for(int i=0; i<size[0]; i++) {
				sentenceInput[i].resize(size[1]);
			}

			for (int i = 0; i < size[0]; i++)
			{
				for (int j = 0; j < size[1]; j++)
				{
					infile >> sentenceInput[i][j];
				}
			}
			// cout << sentenceInput[0][0] << ',' << sentenceInput[0][1] << endl;
			// cout << sentenceInput[1][0] << ',' << sentenceInput[1][1] << endl;

			// Instantiate textranker for current document
			// Compute similarity matrix and apply pagerank
			TextRanker textRanker(size[0], size[1]);
			textRanker.computeSentenceSimilarity(sentenceInput);
			textRanker.pageRank();

			// Sort centrality scores and write index of top 10 sentences to output
			// Each line of output file correspond to one document
			textRanker.sortCentrality();
			textRanker.writeOutput(10, outputFileNames[f]);

			for (int m = 0; m < size[0]; m++) {
				sentenceInput[m].clear();
			}

			// cout << endl;
		}
		infile.close();
    }
    MPI_Barrier(MPI_COMM_WORLD);
    tend = MPI_Wtime();
    if (rank == 0) {
	    cout << "Total wall time is: " << tend-tstart << endl;
    }

    MPI_Finalize();
	return 0;
}
