#include "frag.h"
void taoKH_gen(double *taoKH, double *r)
{
	double temp1;
	int i;
	for (i = 0; i < 100; i++)
	{
		temp1 = Rb * r[i];
//		taoKH[i] = pow(temp1, 0.5) / Vcircular0;
		if(v_d[i] != 0)
			taoKH[i] = pow(temp1, 0.5) / v_d[i];
		else
		{
			printf("v_d[%d] = 0!!\n", i);
			taoKH[i] = pow(temp1, 0.5) / Vcircular0;
		}
	}
}

double *frag_rate_gen(double *m)
{
	double *frag_rate;
	frag_rate = (double*)malloc(sizeof(double)*100);
	int i;
	double temp;
/*	for (i = 0; i<50; i++)                      // change the turning point here if change MBE!!59~4Msolar
	{
		temp = exp((i - 50.0)/Gauss2);
		frag_rate[i] = Frag_rate * (1 - temp);
	}
	for(i = 50; i<100; i++)
	{
		frag_rate[i] = 0;
	}
*/
/// 2012.01:
	for (i=0; i<100; i++)
	{
		temp = m[50]/(m[50]+m[i]);
		temp = pow(temp,co_frag);
		frag_rate[i] = Frag_rate * temp;
	}
	return frag_rate;
}

int fragmentation(int i)
{
	int j;
	double temp = 0;
	j = i + 1;
/*	while(m[j] < mBE)
	{
//		the old way for fragmentation:			
		temp = Timestep * (m[i+1] - m[i]) * n[j]/(taoKH[j] * m[i]) * frag_rate[j];
//		2nd way for fragmentation:
//		temp = Timestep * n[j] * frag_rate[j] / (taoKH[j]) * (m[j] - m[0])/sum[j];
		delta_n[i] += temp;
		delta_Ek[i] += 0.5*temp*m[i]*pow(v_d[j],2);// the same for different fragmentation ways;
		j++;
	}
*/
////2012.01:
	while(j<100)
	{
		temp = Timestep * n[j] * frag_rate[j] / (taoKH[j]) * (m[j] - m[0]);
		temp = temp/sum[j];
		delta_n[i] += temp;
		delta_Ek[i] += 0.5*temp*m[i]*pow(v_d[j],2);// the same for different fragmentation ways;
		j++;
	}

	temp = Timestep * (m[i] - m[0]) * n[i] / (m[i] * taoKH[i]) * frag_rate[i];

///try different powerlaw index for fragment spectra:
// below sth is wrong;
/*	while(j<100)
	{
		temp = Timestep * n[j] * frag_rate[j]/(taoKH[j]);
		temp *= m[j]/m[i]*(1-beta_frag)*pow(m[i],-beta_frag)/(pow(m[j],1-beta_frag)-pow(m[0],1-beta_frag));
		delta_n[i] += temp;
		delta_Ek[i] += 0.5*temp*m[i]*pow(v_d[j],2);
		j++;
	}
	temp = Timestep * (m[i]-m[0]) * n[i] / (m[i] * taoKH[i]) * frag_rate[i];
*/
	delta_n[i] -= temp;
	delta_Ek[i] -= 0.5*temp*m[i]*pow(v_d[i],2); 

	return 1;
}
