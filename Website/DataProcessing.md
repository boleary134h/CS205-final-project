# Data Preprocess
The aim of data preprocess is to generate vector representation for each sentences in a document belonging to CNNDM dataset. For simplicity, we use python to implement this part.

## Text preprocess
We utilize a preprocessed dataset released by [BertSum](https://github.com/nlpyang/PreSumm). The training set contains 287083 documents and are split into 139 chunks. Each chunk contains around 2000 documents represented by a dictionary. The documents have already been split documents into sentences. I use split() in python to split each sentence into words. Then, I use [GloVE](https://github.com/stanfordnlp/GloVe) to generate the 
'''
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
'''