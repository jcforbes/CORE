CORE
====

1d starformation code
------------------------
Original version by Huang, X. C.; current working version by 
Zhou, T. T. ;  
References:   
\bibitem[Huang et al.(2013)]{2013ApJ...769...23H} Huang, X., Zhou, T.,
\& Lin, D.~N.~C.\ 2013, \apj, 769, 23   
Zhou,T., Huang, X. C. , Lin, D.~N.~C.,  et al. (2013) submitted to apjl  

Usage
-----------------------
runcore.py observable_example.txt to generate the default observable.h  
edit the observable.h to set up initial parameters  
read observable_example.txt for the definition of things  
make  
./core filenameyouwant  


Function Devision
-----------------------
coag: the contribution to the mass distributino from coagulation;

conden: the contribution to the mass distribution from condensation;

evap: the contribution to the mass distribution from evapration;

frag: the contribution to the mass distribution from the fragmenation due 
to KH instability;

sf: the contribution to the mass distribution from star formation.
