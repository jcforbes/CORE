#include "coag.h"
int coagulation(int i, int j, double ni, double nj, double ri, double rj)
{
	double z, temp, tempEk, tempenergy;
	double coe1, coe2, coe;
    if(m[i] > mBE)
	{
		coe1 = pow((double)m[i]/mBE, beta);
	}
	else
		coe1 = 1;
	if(m[j] > mBE)
	{
		coe2 = pow((double)m[j]/mBE, beta);
	}
	else
		coe2 = 1;
	coe = 1.0/(1 + coe1) + 1.0/(1 + coe2);
//	coe *= 20;                                                                         //7.17_4 cancel
//	z = 3 * ni * nj * vc * pow((ri + rj),2) * ((double)Timestep / (4 * pow(Rb,3))) ;    /*collision number*/
	z = 3 * ni * nj * (v_d[i] + v_d[j]) * pow((ri + rj),2) * ((double)Timestep / (4 * pow(Rb,3)))/2 ;
	//below use gravitational focusing from Binney & Germaine:
//	z *= coe;
	coe = pow(v0,2.0)/2.0/Drho/pow(vc,2.0)*(pow(m[i],2.0/3.0)+pow(m[j],2.0/3.0))/pow(mBE,2.0/3.0);
	coe += 1;
	z *= coe;

	if(i == j)
	{
		z = (double)z/2;
		delta_n[i] -= z * 2;
		tempenergy = z*m[i]*pow(v_d[i],2);
		delta_Ek[i] -= tempenergy;
		tempEk = tempenergy;
	}
	else
	{
		delta_n[j] -= z;
		tempenergy = 0.5*z*m[j]*pow(v_d[j],2);
		delta_Ek[j] -= tempenergy;
		tempEk = tempenergy;
		delta_n[i] -= z;
		tempenergy= 0.5*z*m[i]*pow(v_d[i],2);
		delta_Ek[i] -= tempenergy;
		tempEk += tempenergy;
	}

	temp = m[i] + m[j];
	if(temp >= m[100])
	{
		ghost_mass += z * (m[i] + m[j]);
	}
	else
	{
		int k;
        k = (i >= j)?i:j;
		while(temp > m[k] && k < 99)
		{
			k++;
		}
		delta_n[k] += z * temp/m[k];
		delta_Ek[k] += tempEk;
//		delta_n[k] += (temp - m[k-1])/(m[k] - m[k-1]) * z * temp/m[k];
//		k--;
//		delta_n[k] += (temp - m[k])/(m[k+1] - m[k]) * z * temp/m[k];
	}
	return 1;
};


