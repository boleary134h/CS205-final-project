# -*- coding: utf-8 -*-
"""
Created on Fri May  7 16:07:03 2021

@author: lhy
"""

from rouge import Rouge 
import os
import torch
rouge = Rouge()
for file in os.listdir("output"):
    index=int(file.split('_')[1].split('.')[0])
    pt_file="cnndm1/cnndm.train."+str(index)+".bert.pt"
    pt_file=torch.load(pt_file)
    count=0
    hyps=[]
    refs=[]
    with open(os.path.join("output",file),'r') as file:
        for line in file:
            extract=line.split()
            extract=[int(i) for i in extract]
            hypothesis=[pt_file[count]['src_txt'][i] for i in extract]
            hypothesis=" ".join(hypothesis)
            reference=pt_file[count]['tgt_txt']
            count+=1
            reference=reference.replace("<q>",' . ')
            scores = rouge.get_scores(hypothesis, reference)
            hyps.append(hypothesis)
            refs.append(reference)
    print(rouge.get_scores(hyps,refs,avg=True))