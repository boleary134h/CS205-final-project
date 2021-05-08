#include <string>
#include <vector>
using namespace std;

#ifndef TEXTRANK_HPP
#define TEXTRANK_HPP

class TextRanker
{
private:
	//n x d matrix
	int n_dim;
	int d_dim;
	vector<vector<double>> similarityMatrix;

	double damping = 0.85; // pagerank damping parameter
	int max_iterations = 50; // maximum number of iterations

	vector<struct centralityScore> cs; // sentence centrality score

public:

	//Constructor
	TextRanker(int n, int d)
	{
		n_dim = n;
		d_dim = d;

		similarityMatrix.resize(n_dim);
		for(int i=0; i<n_dim; i++){
			similarityMatrix[i].resize(n_dim);
		}

		cs.resize(n_dim);
	}

	//Destructor
	~TextRanker()
	{
		//centralityVec.clear();
		for(int i=0; i<n_dim; i++)
		{
			similarityMatrix[i].clear();
		}
	}

	void computeSentenceSimilarity(vector<vector<double>> &sentenceInput);
	vector<vector<double>>& getSimilarityMatrix() {return similarityMatrix;}
	void pageRank();
	void sortCentrality();
	void writeOutput(int x, string filename);

	void printSimilarity();
	void printCentrality();
};

struct centralityScore {
    int idx;
    double score;
};

extern double cosineSimilarity(vector<double> &a, vector<double> &b);
extern bool compare (const centralityScore& a, const centralityScore& b);

#endif
