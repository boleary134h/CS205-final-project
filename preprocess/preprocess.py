# -*- coding: utf-8 -*-
"""
Created on Thu Apr 15 19:24:17 2021

@author: lhy
"""

import torch
import os
for i in os.listdir("cnndm"):
    if i.startswith("cnndm"):
        media=torch.load("cnndm/"+i)
        result=[]
        for j in media:
            result.append({'src_txt':j['src_txt'],'src_sent_labels':j['src_sent_labels']})
        torch.save(result,'cnndm1/'+i)
        print(i)