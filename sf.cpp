#include "sf.h"
int star_formation_hierarchy(int i)
{
	return 1;
}

int star_formation(int i)
{
	double temp = sf_rate[i] * n[i] * Timestep;
	double temp_star_mass, tempn_star;
	delta_n[i] -= temp;
//	if(i <= 50)
	star_mass += temp * alpha * m[i];
	temp_star_mass = m[i] * alpha;
	int j, k;
	j=0;
	k=j;
	while(m[j]<temp_star_mass)
	{
		k=j;
		j++;
	}
	tempn_star = temp * alpha * m[i]/m[k];
	n_star[k] += tempn_star;
  back_mass += temp * (1 - alpha) * m[i];          /*alpha is star formation efficiency*/
	return 1;
};

int star_formation_binary(int i)
{
	int j, flag;
	double q, q1, Qb=q_beta+1, tt1, tt2, tt, tmpstar;  //tmpstar for debug;
	double mtmp[2], ntmp;
	tmpstar = 0;
	for(q=0; q<=0.5-dq; q+= dq)  //pow(0,-0.5) will have some problem??
	{
		mtmp[0] = m[i]*q;
		mtmp[1] = m[i]*(1-q);
		ntmp = n[i] * sf_rate[i] * Timestep;
		q1 = q+dq;
		tt1 = pow(q1,Qb);
		if(q==0)
			tt2 = 0;
		else
			tt2 = pow(q,Qb);
		tt = (tt1-tt2);
		if(tt<0)
			tt=-tt;
		ntmp *= A_q*tt/Qb;
		for(flag=0; flag<2; flag++)
		{
			j=0;
			while(m[j]<mtmp[flag])
				j++;
			j--;
			if(j>=0)
			{
				n_star[j] += mtmp[flag]/m[j]*ntmp;
				star_mass += mtmp[flag]*ntmp;
			}
			else
				back_mass += mtmp[flag]*ntmp;
		}
 		delta_n[i] -= ntmp;
		tmpstar += ntmp;
	}
	tmpstar -= n[i] * sf_rate[i] * Timestep;
	tmpstar /= (n[i] * sf_rate[i] * Timestep);
	return 1;
}

void sf_rate_gen(double *sf_rate, double *m)
{
	int i;
	for(i = 0; i < 50; i++)                                        /** change the turning point here if change MBE**/
	{
	//	sf_rate[i] = SF_rate * exp( - (double)pow((i - 40),2)/(2 * pow(Gauss1,2)));
		sf_rate[i] = 0;
	}
	for(i = 50; i < 100; i++)
	{
		//sf_rate[i] = SF_rate/1.e6;
		sf_rate[i] = SF_rate;
		//sf_rate[i] = SF_rate * 1.5/ (1.0 + 0.5/(pow(m[i]/mBE, gamma)));
//		sf_rate[i] = SF_rate * 1.5/ (1.0 + 0.5/(pow(m[i]/mBE, gamma))) * 100; change SF_rate instead of change here after 0714;
	}		
//	A_q = (q_beta+1)*pow(2, q_beta+1.0);
}


