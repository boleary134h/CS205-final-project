# Sequential Model

After pre-processing, each document is represented as an *n* x *d* matrix. *n* is the number of sentences in the document and *d* is the size of the sentence vector representation. For this project, we use the Glove100 word embeddings to compute sentence representations, and let *d* = 100. The document matrices are then passed to the TextRank algorithm:

    for each matrix:
        computeSimilarityMatrix(); //pairwise sentence "similarity" scores
        computePageRank(); //find sentence "centrality" score
        sortSentences(); //sort by centrality score and pick top X sentences

We detail each step below, and present the sequential runtime on the CNN-DailyMail dataset. Top 3 sentences are chosen to create the summary.

## Compute similarity matrix

The document is represented as a complete graph in which every pair of sentences (vertices) is connected by an edge. Edge weights equal the cosine similarity between the sentence vector representations. For two vectors **a** and **b**, their cosine similarity is given by:

![img](http://latex.codecogs.com/svg.latex?%5Cfrac%7B%5Csum_%7Bi%3D1%7D%5Ena_ib_i%7D%7B%5Csqrt%7B%5Csum_%7Bi%3D1%7D%5Ena_i%5E2%7D%5Csqrt%7B%5Csum_%7Bi%3D1%7D%5Enb_i%5E2%7D%7D)

Since

![img](http://latex.codecogs.com/svg.latex?%5Csqrt%7B%5Csum_%7Bi%3D1%7D%5Ena_i%5E2%7D%5Csqrt%7B%5Csum_%7Bi%3D1%7D%5Enb_i%5E2%7D%3D%5Csqrt%7B%5Cleft%28%5Csum_%7Bi%3D1%7D%5Ena_i%5E2%5Cright%29%5Cleft%28%5Csum_%7Bi%3D1%7D%5Enb_i%5E2%5Cright%29%7D)

we can compute the three sums in the same loop as shown below.

**Cosine similarity between 2 vectors**
 ```cpp
double cosineSimilarity(vector<double> &a, vector<double> &b) {
double mul = 0.0, d_a = 0.0, d_b = 0.0;
vector<double>::iterator a_iter = a.begin();
vector<double>::iterator b_iter = b.begin();
for ( ; a_iter != a.end(); a_iter++, b_iter++) {
	mul += *a_iter * *b_iter;
	d_a += *a_iter * *a_iter;
	d_b += *b_iter * *b_iter;
}
return mul / (sqrt(d_a * d_b));
}
  ```

It takes *O(d)* to compute the cosine similarity of two *d*-dimensional vectors. We want to find the pairwise cosine similarity for all *n* sentences in the document, which is in the order of *O(n^2)*. Hence, the computational complexity of this steps is in the order *O(d n ^2)*. This step becomes computationally intensive very quickly. A document with 50 sentences will need the cosine similarity for 1225 pairs of sentences. We will attempt to parallelize this step in the [Parallel Model](https://github.com/boleary134h/CS205-final-project/blob/main/Website/ParallelModel.md) section.

## Compute PageRank

In the original PageRank algorithm, each vertex on the graph represents a webpage. The algorithm returns a score for each vertex that represents its "importance" - in web-surfing terms, that is the number and quality of links to a page. In our context, where each vertex is a sentence in the document, the PageRank algorithm returns the "centrality" of a sentence in the document. This is measured by the "strength" of connections between sentences, which is their edge weight (cosine similarity). The centrality score for a vertex *u* is given as:

![img](http://latex.codecogs.com/svg.latex?CS%28u%29%3D%281-d%29%2Bd%5Ctimes%5Csum_%7Bv%5Cin%20In%28u%29%7D%5Cfrac%7Bw_%7Bv%2Cu%7D%7D%7B%5Csum_%7Bx%5Cin%20Out%28v%29%7Dw_%7Bv%2Cx%7D%7DCS%28v%29)

where *d* is the damping factor and we let *d*=0.85. 

In our implementation, we take the similarity matrix **A** from the previous step, and initialize a transition matrix **T** to each cell of **A** divided by its row sum. This gives the fraction term in the equation above. Then, we multiply **T** by *d* and perform *m* iterations of updates to the vector of centrality scores **c**. We initialize **c** to *1/n* for every element.

```cpp
//update centrality scores
for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
		temp_c[i] += c[j]*T[j][i];
	}
}

// compute the error for convergence
double error = 0.0;
for (int i = 0; i < n; i++) {
	error += fabs(temp_c[i] - c[i]);
}
```
	
At every iteration, we check the error for convergence and terminate when error is less than 0.001 or when *max_iter*=50 is reached, whichever is earlier. For our project, convergence was reached within 2-3 iterations for all documents.

Since we are performing matrix-vector multiplication at each iteration, this takes order of *O(n^2)*.  Hence, the total complexity is *O(m n^2)*. We will attempt to parallelize the multiplication steps in our [Parallel Model](https://github.com/boleary134h/CS205-final-project/blob/main/Website/ParallelModel.md)

## Sort sentences

We sort the sentences by their centrality scores and select the top 3 sentences for our summary. This is achieve using the *stable_sort* function in C++, which runs in *O(n* log *n)* given sufficient memory. We do not expect this to be the computational bottleneck of our algorithm.

Sequential runtime and comparisons against the parallelized model can be found in our [Results](https://github.com/boleary134h/CS205-final-project/blob/main/Website/Results.md) section.
