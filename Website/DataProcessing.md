# Data Preprocess
The aim of data preprocess is to generate vector representation for each sentences in a document belonging to CNNDM dataset. For simplicity, we use python to implement this part.

## Text preprocess
We utilize a preprocessed dataset released by [BertSum](https://github.com/nlpyang/PreSumm). The training set contains 287083 documents and are split into 139 chunks. Each chunk contains around 2000 documents represented by a dictionary. We iterate over all the chunks to generate sentence embedding for all the documents. The documents have already been split documents into sentences by the authors. We use split() in python to split each sentence into words. Then, we use [GloVE](https://github.com/stanfordnlp/GloVe) to get the pretrained word's embedding and generate the sentence embedding by averaging all the words' embedding belonging to the sentence. To be specific, We use 100-D embedding pretrained on Wikipedia 2014 + Gigaword 5 including 400K vocabulary. We only retain the first three digits after the decimal so as to reduce the storage space.

        for j in media:
            media_matrix=np.zeros((len(j['src_txt']),vectors['the'].shape[0]))
            for k in range(len(j['src_txt'])):
                tokens=j['src_txt'][k].split()
                count=0
                for token in tokens:
                    if token in vectors.keys():
                        media_matrix[k]+=vectors[token]
                        count+=1
                if count>1:
                    media_matrix[k]=media_matrix[k]/count
            result.append(media_matrix)

## Output
For each chunk, we output a txt file containing corresponding sentence embedding. At the first line of the text file, the number indicates the amount of documents. At the second line, there 2 two numbers indicates the amount of sentence in the first document and the dimension of the sentence embedding. In the following lines, each line contain the 100-D representation of each sentence in the first document. Following documents follow the same format. The output file looks like this:

![OutputPlot](https://github.com/boleary134h/CS205-final-project/blob/main/Website/PlotResults/txt.PNG)

## Parallization
