#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

#include "textrank.hpp"
using namespace std;

int main()
{

	int size[2] = { 0 };
	int n_doc = 0;
	string out_filename = "output_0.txt";

	ifstream infile;
	infile.open("0.txt");
	infile >> n_doc;

	// We loop over all documents in current file
	// Documents are processed one at a time
	// Output is the indices of the top 10 sentences
	for (int doc = 0; doc < n_doc; doc++) {

		for (int i = 0; i <= 1; i++) {
			infile >> size[i];
		}
		cout << size[0] << " "<< size[1] << endl;

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
		cout << sentenceInput[0][0] << ',' << sentenceInput[0][1] << endl;
		cout << sentenceInput[1][0] << ',' << sentenceInput[1][1] << endl;

		// Instantiate textranker for current document
		// Compute similarity matrix and apply pagerank
		TextRanker textRanker(size[0], size[1]);
		textRanker.computeSentenceSimilarity(sentenceInput);
		textRanker.pageRank();

		// Sort centrality scores and write index of top 10 sentences to output
		// Each line of output file correspond to one document
		textRanker.sortCentrality();
		textRanker.writeOutput(10, out_filename);

		for (int m = 0; m < size[0]; m++) {
			sentenceInput[m].clear();
		}

		cout << endl;
	}
	infile.close();

	return 0;
}
