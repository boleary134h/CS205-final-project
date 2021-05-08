#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <math.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#include "textrank.hpp"
using namespace std;

void getFilesFromDir(const char *path, vector<string> &fileVec)
{
    fileVec.clear();
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
    	string str=entry->d_name;
    	if(str.length()>0 && str[0]!='.')
    		fileVec.push_back(str);
    }
    std::sort(fileVec.begin(), fileVec.end());
    closedir(dir);

}

double cosineSimilarity(vector<double> &a, vector<double> &b)
{

	if (a.size() != b.size())
	{
		throw logic_error("Vector A and Vector B are not the same size.");
	}

	if (a.size() < 1)
	{
		throw logic_error("Vector A and Vector B are empty.");
	}

	float mul = 0.0;
	float d_a = 0.0;
	float d_b = 0.0;

	vector<double>::iterator a_iter = a.begin();
	vector<double>::iterator b_iter = b.begin();
	for ( ; a_iter != a.end(); a_iter++, b_iter++)
	{
		mul += *a_iter * *b_iter;
		d_a += *a_iter * *a_iter;
		d_b += *b_iter * *b_iter;
	}

	if (d_a == 0.0f || d_b == 0.0f)
	{
		return 0;
		//throw logic_error("Cosine similarity undefined when input vector is zero-vector.");
	}

	return mul / (sqrt(d_a * d_b));
}

bool compare(const centralityScore& a, const centralityScore& b) {
    return (a.score > b.score);
}

void TextRanker::computeSentenceSimilarity(vector<vector<double>> &sentenceInput)
{
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
				similarityMatrix[i][j] = similarityMatrix[j][i];
			}
		}
	}
}

void TextRanker::pageRank()
{
	// make sure that the transition matrix has zeros for i=j
	double transition[n_dim][n_dim];
	for (int i = 0; i < n_dim ; i++) { //row
		for (int j = 0; j < n_dim; j++) {
			if (i != j) {
				transition[i][j] = similarityMatrix[i][j];
			}
			else {
				transition[i][j] = 0.0;
			}
		}
	}

	// make sure the each row in transition matrix sums to 1
	double rowsum = 0.0;
	for (int i = 0; i < n_dim ; i++) {
		rowsum = 0.0;
		for (int j = 0; j < n_dim; j++) {
			rowsum += transition[i][j];
		}
		if (rowsum > 0) {
			for (int j = 0; j < n_dim; j++) {
				transition[i][j] = transition[i][j]/rowsum;
			}
		}
		// fix for the dangling node problem
		else {
			for (int j = 0; j < n_dim; j++) {
				transition[i][j] = 1.0/n_dim;
			}

		}
	}

	// dampen transition matrix
	for (int i = 0; i < n_dim; i++) {
		for (int j = 0; j < n_dim; j++) {
			transition[i][j] = damping*transition[i][j]+(1.0-damping)/n_dim;
		}
	}

	// used for debugging
	/*
	for (int i = 0; i < N ; i++) { //row
		printf("\n");
		for (int j = 0; j < N; j++) {
			printf("%f ",transition[i][j]);
		}
	}
	*/

	// initialize centrality matrix
	for (int i = 0; i < n_dim; i++) {
		cs[i].score = 1.0/n_dim;
	}

	// iterate up to max iterations
	int iteration = 0;
	while (iteration < max_iterations) {

		// initialize temp centrality
		double temp_centrality[n_dim];
		for (int i = 0; i < n_dim; i++) {
			temp_centrality[i] = 0.0;
		}

		// do update
		for (int i = 0; i < n_dim; i++) {
			for (int j = 0; j < n_dim; j++) {
				temp_centrality[i] += cs[j].score*transition[j][i];
			}
		}

		// compute the error for convergence
		double error = 0.0;
		for (int i = 0; i < n_dim; i++) {
			error += fabs(temp_centrality[i] - cs[i].score);
		}
		/*if (iteration % 5 == 0) {
			printf("error: %f \n",error);
		}*/

		// transfer centrality
		for (int i = 0; i < n_dim; i++) {
			cs[i].score = temp_centrality[i];
		}

		// break while loop if reach convergence
		iteration++;
		if (error < 0.001) {
			//printf("Reached convergence after %d iterations \n" , iteration);
			break;
		}
	}
	if (iteration == max_iterations) {
		printf("Reached max number of iterations \n");
	}
}



void TextRanker::sortCentrality()
{
	for(int i=0; i<n_dim; i++) {
	  cs[i].idx = i;
	}

	stable_sort(cs.begin(), cs.end(), compare);
}

void TextRanker::writeOutput(int x, string filename)
{
	int n_sentences;
	n_sentences = min(x, n_dim);
	ofstream out(filename, ios_base::app);
	for (int i=0; i < n_sentences; i++) {
		out << cs[i].idx << " ";
	}
	out << "\n";
}

void TextRanker::printSimilarity()
{
	for (int i=0; i<n_dim; i++)
	{
		for (int j=0; j<n_dim; j++) {
			cout << similarityMatrix[i][j] << " ";
		}
		cout << endl;
	}
	    cout << endl;
}

void TextRanker::printCentrality()
{
	for(int i=0; i<n_dim; i++) {
		cout << cs[i].score << " " << cs[i].idx << endl;
	}
	cout << endl;
}
