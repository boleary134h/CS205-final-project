# -*- coding: utf-8 -*-
"""
Created on Wed Apr 14 20:41:51 2021

@author: lhy
"""

import torch
import os
import numpy as np
import multiprocessing
import math
import time
def process(vector_path,input_path,input_file,output_path):
    with open(vector_path, 'r',encoding='utf-8') as f:
            vectors = {}
            for line in f:
                vals = line.rstrip().split(' ')
                vectors[vals[0]] = np.array([float(x) for x in vals[1:]])
    for i in input_file:
        print(i)
        media=torch.load(input_path+i)
        result=[]
        index=i.split(".")[2]
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
        with open(output_path+"/"+index+".txt","w") as file:
            file.write(str(len(result))+'\n')
            for j in result:
                file.write(str(j.shape[0])+" "+str(j.shape[1])+"\n")
                for k in range(j.shape[0]):
                    media=list(j[k])
                    media=[str(round(l,3)) for l in media]
                    file.write(" ".join(media)+"\n")
if __name__ == '__main__':
    start=time.time()
    n_process=4
    file_list=[]
    for i in os.listdir("cnndm"):
        if i.startswith("cnndm.train"):
           file_list.append(i)
    """
    n_element=math.ceil(float(len(file_list))/float(n_process))
    index=0
    file_lists=[]
    while index+n_element<len(file_list):
        file_lists.append(file_list[index:index+n_element])
        index=index+n_element
    file_lists.append(file_list[index:len(file_list)])
    assert len(file_lists)==n_process
    #process("glove.6B.100d.txt", "cnndm/",file_lists[0],"cnndm_result1/" )
    p1 = multiprocessing.Process(target=process, args=("glove.6B.100d.txt", "cnndm/",file_lists[0],"cnndm_result1/" )) 
    p2 = multiprocessing.Process(target=process, args=("glove.6B.100d.txt", "cnndm/",file_lists[1],"cnndm_result1/" )) 
    p3 = multiprocessing.Process(target=process, args=("glove.6B.100d.txt", "cnndm/",file_lists[2],"cnndm_result1/" )) 
    p4 = multiprocessing.Process(target=process, args=("glove.6B.100d.txt", "cnndm/",file_lists[3],"cnndm_result1/" )) 
    p1.start() 
    p2.start() 
    p3.start() 
    p4.start() 
    p1.join() 
    p2.join()
    p3.join() 
    p4.join()
    print(time.time()-start)
    """