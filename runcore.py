#!/usr/bin/env python
import os
import datetime as dt
import numpy as np
import scipy as sp
def gen_observable(infile,newpara):
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
        if(key in para_dic):
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
    #alphaarray = np.linspace(0,1.5,10)
    perturb = ['vc']
    #perturb = ['alpha_init']
    #vcarray = np.array([1.5e3])
    for vc in vcarray: 
    #for alpha in alphaarray: 
      now = str(dt.datetime.utcnow())
      timestamp = now.split()[0]+'-'+'-'.join(now.split()[1].split(":")[0:2])
      newpara = dict(zip(perturb,[vc]))
      #newpara = dict(zip(perturb,[alpha]))
      gen_observable(infile,newpara)
    #print './core %s' % timestamp
      os.system('make clean')
      os.system('make')
      os.system('./core %s' % timestamp)
if __name__=='__main__':
    main()
