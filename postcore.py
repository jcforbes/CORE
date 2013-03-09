#!/usr/bin/env python
import numpy as np
import scipy as sp
import math
"""
Take fragmentaion files and distr_r files 
and do post analysis.
"""

def main():
    distrf = 'data/standard-distr_r.txt'
    fragf = 'data/standard-coag.txt'
    data1 = np.loadtxt(distrf)
    print data1.shape
    data2 = np.loadtxt(fragf)
    dndlogt = np.zeros([100,10])
    for j in range(2,12):
        for i in range(100):
            if(not data1[i][j]==0):
                dndlogt[i][j-2] = data2[i][j]*1.e5/data1[i][j]
            else:
                dndlogt[i][j-2] = 0
    outfile = 'data/standard-coag-post.txt'
    fout=open(outfile,mode='w')
    for i in range(100):
        fout.write('%15.7f' % data1[i][0])
        for j in range(10):
            fout.write('%15.7f' % dndlogt[i][j])
        fout.write('\n')
    fout.close()
if __name__=='__main__':
    main()
