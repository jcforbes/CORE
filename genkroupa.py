#!/usr/bin/python 
import numpy as np
import scipy as sp
import math
import matplotlib
from matplotlib import pyplot as plt
from scipy import stats
def Observed():
    infile = 'data/R09.ls'
    data=np.loadtxt(infile)
    masses = np.log10(data[:,1])
    #print masses
    #linmass = np.logspace(-1,1,100)
    linmass = np.linspace(-1,math.log10(40),100)
    kde = stats.gaussian_kde(masses)
    kde.covariance_factor=kde.silverman_factor
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_subplot(111)
    dist = kde(linmass)
    ax.loglog(10.**(linmass),dist)
    ratio = 230./sum(dist)
    plt.show()
    outfile = 'data/R09_kde.txt'
    fout = open(outfile,mode='w')    
    for i in xrange(len(dist)):
        if(i==0 or i == len(dist)-1):
            bin = 10**linmass[i]
        else:
            bin = (10**linmass[i+1]-10**linmass[i-1])/2
        fout.write('%f %f %f\n' % (10.**linmass[i],ratio*dist[i],bin))
    fout.close()
    masses = data[:,1]
    logmass = np.logspace(-1,math.log10(20),10)
    digitized = np.digitize(masses,logmass)
    binmass = np.array([len(masses[digitized==i]) for i in range(len(logmass))])
    print binmass
    for i in range(1,len(logmass)):
        print logmass[i], binmass[i],binmass[i]/(logmass[i]-logmass[i-1])
    return

def Chabrier(m):
    dist = np.zeros(len(m))
    #dis[m<1] = 0.158*(1./m[m<1])*np.exp(-(np.log(m<1)-np.log(0.08))**2./(2*0.69**2.))
    dist[m<1] = 0.158*np.exp(-(np.log(m[m<1])-np.log(0.079))**2./(2*0.69**2.))
    m0 = 1.
    cont= 0.158*(1./m0)*np.exp(-(np.log(m0)-np.log(0.08))**2./(2*0.69**2.))

    dist[m>=1] = cont*m[m>=1]**(-1.3) 
    return dist
def Kroupa(m):
    dist = np.zeros(len(m))
    dist[m<=0.5] = m[m<=0.5]**-0.3*10/0.5**-0.3
    m0 = 0.08**-0.3*10/0.5**-0.3
    dist[m<0.08] = m[m<0.08]**0.7*m0/0.08**0.7
    dist[m>0.5] = m[m>0.5]**-1.3*10/0.5**-1.3
    return dist
def main():
    m = np.logspace(-2,math.log10(40),100)
    dist1 = Kroupa(m)
    dist2 = Chabrier(m)
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_subplot(111)
    ax.loglog(m,dist1)
    ax.loglog(m,dist2)
    plt.show()
    #outfile = 'data/Kroupa.txt'
    #fout = open(outfile,mode='w')
    #for i in range(100):
    #    fout.write("%f %f\n" % (3*m[i],dist[i]))
    #fout.close()
    return

if __name__=='__main__':
    #Observed()
    main()
