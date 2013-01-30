#include "evap.h"
double *evap_rate_gen()
{
	double *evap_rate = (double *)malloc(sizeof(double) * 100);
	int i = 0;
	for(i=0; i<100; i++)
	{
		evap_rate[i] = 0;
	}
	i=0;

	double temp = pow(1/m_insolar[i],1.0/3.0)-2;
	while(temp>=0 && i<10)  //strong limit;
//	while(temp>=0 && i<7)
	{
//		evap_rate[i] = Timestep/(10*yr) * (1e-4)*1.1*temp;
		evap_rate[i] = Timestep * Evap_rate *1.1*temp;
		i++;
		temp = pow(1/m_insolar[i],1.0/3.0)-2;
	}
	if(i==20)
		printf("evaporation exceeds 0.1Msun\n");
	//now don't allow evaporation above 0.1Msun!!!!!!!!!!!!!!!!
	else
		Evap_lim = i;

/*******
// now to calculate the other limit with small evapration:
	double temp=exp(-i/4.0);
	while(temp>=0 && i<=20)
	{
		evap_rate[i] = 0.4*Timestep/(10*yr)*(1e-3)*temp;
		i++;
		temp = exp(-i/4.0);
	}
	Evap_lim = 20;

*******/

//// 2012.01.07: 0108-03,i/4; 0108-04,*0.4; 0108-05,i/6;0108-06,(i+3)/6; 0108-08,real number!! EvapLim=40;
/*	double temp = exp(-(i+3.0)/6.0);
	while(temp>=0 && i<=40)
	{
		evap_rate[i] = 0.4*Timestep/(10*yr)*(1e-3)*temp;
		i++;
		temp = exp(-(i+3.0)/6.0);
	}
	Evap_lim = 40;
*/
/// 2012.01.08:
/*	double temp = 0;
	while(i<20)
	{
		temp = m[10]/(m[10]+m[i]);
		temp = pow(temp,co_evap);
		evap_rate[i] = Timestep/(10*yr)*8.0*(1e-3)*temp;
		i++;		
	}
*/
/// 2012.01.08 after -09:
/*	double temp = 0;
	while(i<100)
	{
		temp = 1/(1+pow(m[10]/m[i],co_evap));
//		temp = pow(temp,co_evap);
		evap_rate[i] = Timestep*Evap_rate*temp;
//		evap_rate[i] = Timestep/(10*yr)*(1e-3)*temp*1;
		i++;		
	}
	Evap_lim = 100;
*/	return evap_rate;
}

int evaporation()
{
	double temp;
	double evap_temp;
	int i;
	for(i = 0; i < Evap_lim; i++)
	{
		temp = n[i] * evap_rate[i] * evap_mod;
		delta_n[i] -= temp;
		delta_Ek[i] -= 0.5*temp*m[i]*pow(v_d[i],2);
//		total_mass_core[0] -= temp*m[i];
		back_mass += temp*m[i];
	}

//to smooth the transition:
/*
	evap_temp = evap_rate[Evap_lim-1];
	for(i=Evap_lim; i<100; i++)
	{
		temp = n[i] * evap_temp;
		temp *= 1/(1+pow(m[i]/m[Evap_lim],co_evap));
		delta_n[i] -= temp;
		delta_Ek[i] -= 0.5*temp*m[i]*pow(v_d[i],2);
		back_mass += temp*m[i];
	}
*/
	return 1;
}


