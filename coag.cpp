#include "coag.h"
int coagulation(int i, int j, double ni, double nj, double ri, double rj)
/*Input: i, j the mass bin index of the two cores coagulate; 
 *       ni, nj the number of cores in each bins; 
 *       ri, rj the radius coresponding to the mass for cores in each bins;
 *
 *Output: In later version, we shall change all the output so that they 
 *        can be told from read the function call;
 *        List as below: the global valuables 
 *        delta_n
 *        delta_Ek
 *        ghost_mass 
 *        are updated during the function call.
 * */
{
	double z, temp, tempEk, tempenergy;
	double coe1, coe2, coe;
  /*assign sticking coefficients for each core*/
  if(m[i] > mBE)
	{
		coe1 = pow((double)m[i]/mBE, beta);
	} else {
		coe1 = 1;
  }
	if(m[j] > mBE)
	{
		coe2 = pow((double)m[j]/mBE, beta);
	}
	else {
		coe2 = 1;
  }

	coe = 1.0/(1 + coe1) + 1.0/(1 + coe2);
	  
  z = 3 * ni * nj * (v_d[i] + v_d[j]) * pow((ri + rj),2) * ((double)Timestep / (4 * pow(Rb,3)))/2 ;
	//below use gravitational focusing from Binney & Germaine:
	
  coe = pow(v0,2.0)/2.0/Drho/pow(vc,2.0)*(pow(m[i],2.0/3.0)+pow(m[j],2.0/3.0))/pow(mBE,2.0/3.0);
	coe += 1;
	z *= coe;
  /*record the reduce of core numbers and energy in bin i and j due to this 
   * coagulation*/
	if(i == j){
    /*If coag with the same bin, need special care of the energy change*/
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

	temp = m[i] + m[j]; /*the result mass assuming no mass loss during the 
                       coagulation*/
  /*if it ends up in our ghost zone*/
	if(temp >= m[100])
	{
		ghost_mass += z * (m[i] + m[j]);
	}
	else
	{
    /*otherwise, it ends up in bin k*/
		int k;
    k = (i >= j)?i:j;
		while(temp > m[k] && k < 99) /*search for bin k given the mass*/
		{
			k++;
		}
    /*Record the mass change in bin k due to this coagulation*/
		delta_n[k] += z * temp/m[k];
		delta_Ek[k] += tempEk;
	}
	return 1;
};


