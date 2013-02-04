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
    ax.loglog(10.**(linmass),10*kde(linmass))
    plt.show()
    return
def main():
    return

if __name__=='__main__':
    Observed()
    #main()
