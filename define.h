#ifndef DEFINE_H
#define DEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "const.h"
#include "observable.h"
//initial values:
//#define Backmassinsolar (4*Pi*rhoc*pow(Rb,3)/(3*Msolar*Drho))
#define Totalmass_core0 (Tmass_core0solar*Msolar)
#define Rhob           (rhoc/Drho)
#define Back_mass       (Backmassinsolar*Msolar)
#define Rb              (pow(Back_mass*3/(4*Pi*Rhob),1.0/3.0))
#define fifa            (Totalmass_core0/Backmassinsolar)
//#define Totalmass_core0 (Back_mass*fifa*Drho)

//derived constants:
#define Vcircular0      (pow(Grav*Back_mass/Rb, 0.5)) /*****circular speed******/

//runtime parameters:

#define unit           (50000)	//timestep interval of output record; 
#define Timestep       (10*yr)
#define totaltime      (5.0*myr)
#define bin             40          //parameter for initial mass distribution: truncation bin number;
#define Frag_rate       1.0			//in frag_rate_gen();
#define Evap_rate       ((7e-3)/kyr)     //calculated according to energy conservation; try /kyr and /yr both;
//outdated !! #define cn_ratio        0.8              /****condensation to nucleation ratio***/
#define Gauss1          1.                /****sigma for sf_rate_gen()*****/
#define Gauss2          20.                /****sigma for frag_rate_gen()****/


/***************external variables*******************/
//main solution array:
#ifdef MAIN_C
double n[100], delta_n[100], rk[4][100], Ek[100], delta_Ek[100]; //rk[4][100] is for RK4 algorithm;
double n_star[100];

//constant array:
double m[101], m_insolar[100], sum[100]/*** auxiliary array for m[]***/, v_d[100]/*** core velocity ***/, sf_rate[100];
double *evap_rate, *dens, *frag_rate/**smoothing function for frag*/; /***initially used, then don't need to update***/
//int Evap_lim;
double A_q;

//need to update every timestep!!!!!!!!:
double *r, taoKH[100];  /**** auxiliary for calculation ****/
double delta_n_cond[100], delta_n_coag[100], delta_n_frag[100], delta_n_evap[100];
double rhob;   /*** rhob is variable with evolution ***/
double star_mass, back_mass, total_mass, total_mass_core, ghost_mass, totEk;
//runtime:
clock_t start, finish, start2, end2;
char *name;
#else
extern double n[100], delta_n[100], rk[4][100], Ek[100], delta_Ek[100]; //rk[4][100] is for RK4 algorithm;
extern double n_star[100];
extern double m[101], m_insolar[100], sum[100]/*** auxiliary array for m[]***/, v_d[100]/*** core velocity ***/, sf_rate[100];
extern double *evap_rate, *dens, *frag_rate/**smoothing function for frag*/; /***initially used, then don't need to update***/
//extern int Evap_lim;
extern double A_q;
extern double *r, taoKH[100];  /**** auxiliary for calculation ****/
extern double delta_n_cond[100], delta_n_coag[100], delta_n_frag[100], delta_n_evap[100];
extern double rhob;   /*** rhob is variable with evolution ***/
extern double star_mass, back_mass, total_mass, total_mass_core, ghost_mass, totEk;
extern clock_t start, finish, start2, end2;
extern char *name;
#endif
#endif






