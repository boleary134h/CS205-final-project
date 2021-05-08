#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

#include "textrank.hpp"
using namespace std;

int main()
{
	// To read file names from directory
	const char *pathPtr = "/home/ubuntu/cnndm_result1";
	vector<string> fileVec;
	getFilesFromDir(pathPtr, fileVec);
	vector<string>::iterator f_iter = fileVec.begin();

	// Loop over input files
	// Output saved to current directory
	string pathname = "/home/ubuntu/cnndm_result1/";
	for ( ; f_iter != fileVec.end(); f_iter++)
	{
		cout << "Processing " << *f_iter << "..." << endl;
		int size[2] = { 0 };
		int n_doc = 0;
		string in_filename = pathname + *f_iter;
		string out_filename = "output_" + *f_iter;

		ifstream infile;
		infile.open(in_filename);
		infile >> n_doc;

		// Loop over all documents in current file
		// Documents are processed one at a time
		// Output is the indices of the top 3 sentences
		for (int doc = 0; doc < n_doc; doc++) {

			for (int i = 0; i <= 1; i++) {
				infile >> size[i];
			}

			// Read sentence vectors representations
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

			// Instantiate textranker for current document
			TextRanker textRanker(size[0], size[1]);
			
			// Compute similarity matrix
			textRanker.computeSentenceSimilarity(sentenceInput);

			// Apply Pagerank to get sentence centrality scores
			textRanker.pageRank();

			// Sort centrality scores
			textRanker.sortCentrality();
			
			// Write indices of top 3 sentences to output
			// Each line of output file correspond to one document
			// Output saved to current directory
			textRanker.writeOutput(3, out_filename);

			for (int m = 0; m < size[0]; m++) {
				sentenceInput[m].clear();
			}
		}
		infile.close();

	}

	return 0;
}
