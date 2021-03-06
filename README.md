# CS205 Final Project: Textrank

## Team 18:
* You Wu
* Haoyuan Li
* Brendan O'Leary

## Introduction

Our focus on this work is to parallelize the TextRank algorithm for text summarization. TextRank is a graph-based algorithm inspired by PageRank for extractive summarization, where the most important sentences in a document are selected to generate the summary. Key steps in this algorithm are:

1. Represent document as a complete graph where **each sentence is a vertex** and **edge weights represent sentence similarity**
2. Compute sentence importance score using PageRank
3. Sort sentences by importance and select top X sentences for the summary

For this project, we used the publicly available [CNN-DailyMail dataset](https://github.com/abisee/cnn-dailymail) which consists of ~280K news articles, each approximately 20-30 sentences long. We select the top 3 sentences to generate the summary and evaluate our prediction by the [Rouge](https://www.aclweb.org/anthology/W04-1013/) score.

The types of parallelism explored in this project are:
- Multiprocessing in Python for data processing
- Loop parallelism with OpenMP
- Task parallelism with MPI

## Table of Contents
1. [Problem Statement](Website/ProblemStatement.md) 
2. [Data Processing](Website/DataProcessing.md)
3. [Sequential Model](Website/SequentialModel.md)
4. [Parallel Model](Website/ParallelModel.md)
5. [Results](Website/Results.md)
6. [Discussion](Website/Discussion.md)
7. [How To Run Code](Website/HowToRunCode.md)
8. [Cluster Configuration](Website/ClusterConfiguration.md)

## References

Brin, S. and Page, L., 1998. The anatomy of a large-scale hypertextual web search engine. *Computer networks and ISDN systems, 30*(1-7), pp.107-117.

Liu, Y. and Lapata, M., 2019. Text summarization with pretrained encoders. *arXiv preprint arXiv:1908.08345*.

Mihalcea, R. and Tarau, P., 2004, July. Textrank: Bringing order into text. In *Proceedings of the 2004 conference on empirical methods in natural language processing* (pp. 404-411).

Pennington, J., Socher, R. and Manning, C.D., 2014, October. Glove: Global vectors for word representation. In *Proceedings of the 2014 conference on empirical methods in natural language processing (EMNLP)* (pp. 1532-1543).

Lin, C.Y., 2004, July. Rouge: A package for automatic evaluation of summaries. In Text summarization branches out (pp. 74-81).
