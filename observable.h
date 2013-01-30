#ifndef OBSERVABLE_H
#define OBSERVABLE_H
//observables:
#define mBE            (2*Msolar)  //remember to change function frag_rate_gen and sf_rate_gen when change mBE!!!!
#define v_m			   (-0.2)        //initial core v~m^0.1
//#define Rb             (5*pc)   //for concentrated, 2.75pc; for realistic, 5pc; now use total mass instead.
#define Backmassinsolar  (1e3)
#define Tmass_core0solar (350.0)
#define Totalmass_core0 (Tmass_core0solar*Msolar)
#define vc             (1e3)  //(2.0e3)   //before 0209-05(3e3)            /****velocity dispersion of cores.m/s,*/
#define v0             (0.8e3)      //before 0209-05(4e3)         /****thermal velocity of molecules in background******/
#define rhoc           (3e-17)  //(3.187e-17)      /****kg/m^3****/
#define Drho            15 //7              /******density contrast, 100 or 1000****/
//#define fifa            0.0006             /***initial filling factor***/
/**for realistic, 0.01/Drho=0.0006; for concentrated, just keep the total core mass~150Msolar;**/
#define Rhob           (rhoc/Drho)

#define alpha_init      (0.7)       //in initialize(); dn/dlogm=A*m^(-alpha_init);
#define alpha           1//0.5        //in star_formation(); the efficiency of sf;
#define beta            (-2.5)		   //in coagulation(); the modified coefficient of cross section;
#define beta_frag       (5.0)      //in fragmentation(); fragment spectra powerlaw index;
#define kappa           0.8 //0.5        //in conden_nucle(); modified coefficient;         
#define gamma           0.5        //in sf_rate_gen(); modified coefficient;
#define co_frag         4.0        //in frag_rate_gen; modified coefficient;
#define co_evap			2.0  //2.0  //8.0		   //in evapration; powerlaw index;
#define evap_mod        3 //0.5       //in evapration; coefficient;
#define q_beta		    (-1.2) 
#define dq				0.05
#define idens 40				   // mean rhoc at m = 1.05Msun
#define X_fac				10			//coefficient for cooling function;
#define NUCLEAT		   (3.36e-2/kyr)   //coefficient for nucleation;
#define SF_rate         (0.03/myr)           //in sf_rate_gen();

#endif

