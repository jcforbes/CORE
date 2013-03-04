#!/usr/bin/env python
import os
import datetime as dt
import sys
import numpy as np
import scipy as sp
import math
def gen_observable(infile,newpara={}):
    fin = open(infile,mode='r')
    key = []
    value = []
    for line in fin.readlines():
        if (not line.startswith('#')):
            tempkey,tempvalue=line.rstrip().split('=')
            key.append(tempkey.strip())
            value.append(tempvalue.strip())    
    fin.close()
    para_dic=dict(zip(key,value))
    for key,value in newpara.items():
        print key,value
        if(key in para_dic):
            print key,value
            para_dic[key]=value
    outfile = 'observable.h'
    fout = open(outfile,mode='w')
    fout.write('#ifndef OBSERBABLE_H\n')
    fout.write('#define OBSERBABLE_H\n')
    for name,value in para_dic.items():
        line='#define %s %s\n' % (name,value)
        fout.write(line)
    fout.write('#endif\n')
    fout.close()
    return 

def main():
    infile = 'observable_example.txt'
    vcarray = 1000*np.linspace(0.5,2,10)
#    alphaarray = np.linspace(0,1.5,10)
#    evaparray = np.logspace(-1,math.log10(5),10)
#    perturb = ['alpha_init']
#    perturb = ['evap_mod']
    perturb = ['vc']
    #vcarray = np.array([1.5e3])
#    for alpha in alphaarray:
#    for evap in evaparray:
    for vc in vcarray: 
      now = str(dt.datetime.utcnow())
      timestamp = now.split()[0]+'-'+'-'.join(now.split()[1].split(":")[0:2])
      newpara = dict(zip(perturb,[vc]))
#      newpara = dict(zip(perturb,[alpha]))
#      newpara = dict(zip(perturb,[evap]))
      gen_observable(infile,newpara)
      print 'v%s' % timestamp
      os.system('make clean')
      os.system('make')
      os.system('./core v%s' % timestamp)
if __name__=='__main__':
    if len(sys.argv)==1: 
        main()
    else:
        gen_observable(sys.argv[1])
