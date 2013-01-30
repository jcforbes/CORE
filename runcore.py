#!/usr/bin/env python
import os
import datetime as dt
def gen_observable(infile):
    fin = open(infile,mode='r')
    key = []
    value = []
    for line in fin.readlines():
        if (not line.startswith('#')):
            tempkey,tempvalue=line.rstrip().split('=')
            key.append(tempkey)
            value.append(tempvalue)    
    fin.close()
    para_dic=dict(zip(key,value))
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
    now = str(dt.datetime.utcnow())
    infile = 'observable_example.txt'
    timestamp = now.split()[0]+'-'+'-'.join(now.split()[1].split(":")[0:2])
    gen_observable(infile)
    #print './core %s' % timestamp
    os.system('Make clean')
    os.system('Make')
    #os.system('./core %s' % timestamp)
if __name__=='__main__':
    main()
