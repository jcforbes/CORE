#ifndef MAIN_C
#define MAIN_C
#include"define.h"
#include "coag.h"
#include "io.h"
#include "conden.h"
#include "evap.h"
#include "frag.h"
#include "sf.h"
/*** with conduction, no artificial support ***/

static int update();    
static int initialize(double *time, double *TimeContinue, int *ff, int *ff2);
int main()
{
	start = clock();
	int    i = 0, j = 0, k = 0;
	double mytime = 0, TimeContinue = 0, time1;
	int ff = 0, ff2 = 0;
	int countcolumn = 0, countcolumncf = 0;
	double result[15][100], result_star[15][100], Ek_evo[15][100], frag[15][100], coag[15][100];  //result[0] stores the initial distribution; frag[] & coag[] store the separate contributions;

    /***************initialize*************/
    initialize(&mytime, &TimeContinue, &ff, &ff2);
	time1 = (double)mytime/myr;
	if(TimeContinue==0)
	{
		for(i = 0; i<100; i++)
		{
			result[countcolumn][i] = n[i];
			Ek_evo[countcolumn][i] = Ek[i];
			for(j = 0; j<15; j++)
			{
				frag[j][i] = 0;
				coag[j][i] = 0;
			}
		}
		countcolumn++;
	}
	/**********************************/

	/************open file****************/
	char f_txt[25],f_distr[25], f_mass[25], f_star[25], cp[25], f_Ek[25], filefrag[25], filecoag[25];
	FILE *fp, *fp1, *fpfrag, *fpcoag;
	filename_gen(f_txt, f_distr, f_mass, f_star, f_Ek, cp, filefrag, filecoag);
	fp = fopen(f_txt,"w");
	print_paras(fp, back_mass, TimeContinue, total_mass_core);
	fp1=fopen(f_mass, "w");
	fprintf(fp1, "time(myr)\tstar mass\tcore mass\tghost mass\tchange in rhob\ttotal mass\ttotal Ek(10^40)\n");
	fprintf(fp1, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n", time1, star_mass/Msolar, total_mass_core/Msolar, ghost_mass/Msolar, (rhob-Rhob)/Rhob, total_mass/Msolar, totEk/pow(10,40));
	/******************************/

	/**************iteration**************/
	do
	{
		ff2++;
		conden_nucle();
		for( i = 0; i < 100; i++)
		{
			for(j = i; j < 100; j++)
			{
				coagulation(i, j, n[i], n[j], r[i], r[j]);
			}
			star_formation(i);
			//star_formation_binary(i);
			//star_formation_hierarchy(i);
		}
		for(i = 0; i<100; i++)
		{
			coag[countcolumncf][i] += delta_n_coag[i];
		}
		for(i = 0; i<100; i++)
		{
//			if (m[i] < mBE)
				fragmentation(i);
		}
		for(i = 0; i<100; i++)
		{
			frag[countcolumncf][i] += delta_n_frag[i];
		}
		if(ff2 == unit)
		{
			ff2 = 0;
			countcolumncf++;
		}
		evaporation();
		update();
		mytime += Timestep;
		ff++;
        if(ff >= unit)
		{
			time1 = (double)mytime/myr;
			fprintf(fp1, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n",time1, star_mass/Msolar, total_mass_core/Msolar, ghost_mass/Msolar, (rhob-Rhob)/Rhob, total_mass/Msolar, totEk/pow(10,40));
			for(k = 0; k < 100; k++)
			{
				result[countcolumn][k] = n[k];
				result_star[countcolumn][k] = n_star[k];
				Ek_evo[countcolumn][k] = Ek[k];
			}
			countcolumn++;
			ff = 0;
		}
	}
	while(mytime <= (totaltime+TimeContinue));

	/**********************************/

	finish = clock();
	finalize(mytime, fp, cp, ff, ff2);
	dataoutput2(result, result_star, Ek_evo, countcolumn, f_distr, f_star, f_Ek, countcolumncf, filefrag, filecoag, frag, coag, TimeContinue); 

}

/**************functions***************/
int examine(double *n, double *star_mass, double *back_mass, double *total_mass, double *total_mass_core)
{
	return 1;
};

double *r_gen(double *m, double *dens)               
{
	double *r, temp;
	r = (double *)malloc(sizeof(double) * 100);
	int i;
	for(i = 0; i < 100; i++)
	{
		temp = 3 * m[i]/4/Pi/dens[i];
		r[i] = pow( temp, (double)1/3);
	}
	return r;
}

double *dens_gen(double *m)
{
	double *dens, temp;
	dens = (double *)malloc(sizeof(double) * 100) ;
	int i;
	for(i = 0; i<100; i++)
	{
//		dens[i] = rhoc * pow(m[i]/m[idens], -0.44);//// Lada2008: M_c~R^2.56
		dens[i] = rhoc;
	}
	return dens;
}

int initialize(double *mytime, double *TimeContinue, int *ff, int*ff2)
{
	int i, j;
	int init = 10;
	double a = 1.07897;//a=exp((log(100)-log(0.05))/2)=m[i+1]/m[i];
	double A;
	char flag;
	
//constants initialize:
	m[0] = 0.05 * Msolar;
	A = Totalmass_core0/pow(m[0],1.0-alpha_init);
	A = A*(1-pow(a,1.0-alpha_init));
	A = A/(1-pow(a,(1.0-alpha_init)*(bin+1)));
	sum[0] = 0;
	m_insolar[0] = (double)m[0]/Msolar;
	m[100] = 100 * Msolar;
	delta_n[0] = 0;
	delta_n_coag[0] = 0;
	delta_n_frag[0] = 0;
	delta_n_cond[0] = 0;
	delta_n_evap[0] = 0;
	for( i = 1; i < 100; i++)
	{ 
		m[i] = m[i-1] * a;              
		m_insolar[i] = (double)m[i]/Msolar;
		sum[i] = sum[i-1] + m[i-1];
		delta_n[i] = 0;
		delta_n_coag[i] = 0;
		delta_n_frag[i] = 0;
		delta_n_cond[i] = 0;
		delta_n_evap[i] = 0;
		n_star[i] = 0;
		for(j = 0; j<4; j++)
		{
			rk[j][i] = 0;
		}
	}
	n_star[0] = 0;
//interaction:
//    printf("Use the default initial settings? y/n:\n");
//	char flag = 'n';
//	flag = getchar();
  flag = 'y';
  if (flag != 'y')
	{
		readdata(mytime, TimeContinue, ff, ff2);
		n_star[0] = 0;/// just for follow 0513-11-cp.txt
		total_mass_core = 0;
		totEk = 0;
		for(i = 0; i<100; i++)
		{
			Ek[i] = 0.5*m[i]*n[i]*v_d[i]*v_d[i];
			totEk += Ek[i];
			total_mass_core += n[i]*m[i];
		}
		total_mass = total_mass_core + back_mass + star_mass;
		rhob = 3 * back_mass/4/Pi/pow(Rb,3);
		sf_rate_gen(sf_rate, m);
		dens = dens_gen(m);
		r = r_gen(m, dens);
		frag_rate = frag_rate_gen(m);
		taoKH_gen(taoKH, r);
		evap_rate = evap_rate_gen();
		return 1;
	}
	else
	{
		star_mass = 0;
		back_mass = Back_mass;
		ghost_mass = 0;
		for(i = 0; i<bin; i++)
		{
			n[i] = A*pow(m[i],-alpha_init);
		}
		total_mass_core = Totalmass_core0;
		for(i = bin; i<100; i++)
		{
			n[i] = 0;
		}
	}
//v & Ek initialize:
	dens = dens_gen(m);
    r = r_gen(m, dens);
	for(i = 0; i<100; i++)
	{
		v_d[i] = vc*pow(m[i]/m[40],v_m);
		Ek[i] = 0.5*m[i]*n[i]*v_d[i]*v_d[i];		
		totEk += Ek[i];
		delta_Ek[i] = 0;
	}
//scalar:
	total_mass = star_mass + back_mass + total_mass_core;
	rhob = 3 * back_mass/4/Pi/pow(Rb,3);
//arrays:
	sf_rate_gen(sf_rate, m);
	frag_rate = frag_rate_gen(m);
	taoKH_gen(taoKH, r);
	evap_rate = evap_rate_gen();

	return 1;
};
int update()
{
	int i;
	total_mass = 0;
	total_mass_core = 0;
	totEk = 0;
	for(i = 0; i < 100; i++)
	{
		n[i] += delta_n[i];
		delta_n[i] = 0;
        total_mass_core += n[i] * m[i];
		Ek[i] += delta_Ek[i];
		totEk += Ek[i];
		delta_Ek[i] = 0;
// whether update the v(m)??
//		if(n[i] != 0)
//			v_d[i] = sqrt(2*Ek[i]/m[i]/n[i]);
	}
	double temp_rhob = 3 * back_mass/4/Pi/pow(Rb,3);
	double tempratio = temp_rhob/rhob;
	for(i = 0; i < 100; i++)
	{
		r[i] *= pow(tempratio, -1.0/3.0);
	}
	rhob = temp_rhob;
	taoKH_gen(taoKH, r);
	total_mass = total_mass_core + back_mass + star_mass + ghost_mass;
	return 1;
};
#endif
