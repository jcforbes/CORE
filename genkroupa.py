#!/usr/bin/python 
import numpy as np
import scipy as sp
import matplotlib
from matplotlib import pyplot as plt
from scipy import stats
def Observed():
    infile = 'data/R09.ls'
    data=np.loadtxt(infile)
    masses = np.log10(data[:,1])
    #print masses
    #linmass = np.logspace(-1,1,100)
    linmass = np.linspace(-1,2,100)
    kde = stats.gaussian_kde(masses)
    kde.covariance_factor=kde.silverman_factor
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_subplot(111)
    dist = kde(linmass)
    ax.loglog(10.**(linmass),dist)
    plt.show()
    outfile = 'data/R09_kde.txt'
    fout = open(outfile,mode='w')
    for i in xrange(len(dist)):
        fout.write('%f %f\n' % (10.**linmass[i],10*dist[i]))
    fout.close()
    return

def Kroupa(m):
    dist = np.zeros(len(m))
    dist[m<=0.5] = m[m<=0.5]**-0.3
    dist[m<0.08] = m[m<0.08]**0.7
    dist[m>0.5] = m[m>0.5]**-1.3
    return dist
def main():
    m = np.logspace(-1,2,100)
    dist = Kroupa(m)
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_subplot(111)
    ax.loglog(m,dist)
    plt.show()
 
    return

if __name__=='__main__':
    #Observed()
    main()
