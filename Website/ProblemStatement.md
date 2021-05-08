# Problem Statement

Text summarization is the task of generating text summaries while preserving important information and overall meaning. With the promise of condensing long articles, papers, or documents down to their key points, it captivates enterprises and individuals alike, and remains one of the hottest topics of research in data science. There are two main approaches to summarization:

- **Extractive summarization**: Select existing sentences in the document to generate the summary
- **Abstractive summarization**: Generate new text to summarize the document

In this project, we aim to parallelize TextRank, an algorithm for extractive summarization, and reduce the time taken to generate summaries for a large corpus of documents.

## Need for Big Data

The power of text summarization is in saving manhours from poring over a large number of long texts. This naturally leads to the challenge of processing large databases. These typically contains hundreds of thousands of documents, each with close to 1000 words. Table below shows the statistics for some of the popular databases in the Natural Language Processing (NLP) literature.

| Dataset | Number of documents | Average words per document |
| ------ | ------ | ------ | 
| XSUM | 226K | ~400 |
| CNN-DailyMail | 300K | ~800 |
| ARXIV | 215K | ~7000 |

Besides the volume of data, the velocity of data generation is also a concern for applications that require summarizations on the fly as new documents come in. For instance, media monitoring could require timely summarization of news articles, newsletters, blogs, and social media posts as they are published throughout the day. In such cases, it is not enough to summarize an existing database of documents; the algorithm should execute quickly on new data as it is generated.

## Need for Big Compute
TextRank is a graph-based algorithm inspired by Pagerank. Each document is represented as a complete graph, in which every sentence is a vertex and every pair of vertices is connected by an edge. Edge weights are typically assigned to indicate degree of ''similarity'' between the sentences. 

It has three key steps, each of which can be computationally intensive especially on a large, dense graph.

1. Compute pairwise sentence similarity to assign edge weights
2. Apply PageRank algorithm to compute "centrality score" of each sentence (vertex)
3. Rank sentences by centrality score and select top X to generate the summary

We provide detailed explanation for each of these steps in our [Sequential Model](https://github.com/boleary134h/CS205-final-project/blob/main/Website/SequentialModel.md) section.
