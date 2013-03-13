#include "io.h" 
int filename_gen(char *f_txt, char*f_distr, char*f_mass, char*f_star, char*f_Ek, char*cp, char*filefrag, char*filecoag)
{
	int i;
//	printf("please input the number of the txt file:\n");
	start2 = clock();
//scanf("%s", f_txt);
	end2 = clock();
  strcpy(f_distr, f_txt);
	strcpy(f_mass, f_txt);
	strcpy(f_star, f_txt);
	strcpy(cp,f_txt);
	strcpy(f_Ek,f_txt);
	strcpy(filefrag, f_txt);
	strcpy(filecoag, f_txt);
	i = 0;
	do
	{
		i++;
	}
	while(f_distr[i] != '.');
	do
	{
		f_distr[i] = '\0';
		f_mass[i] = '\0';
		f_star[i] = '\0';
		f_Ek[i] = '\0';
		cp[i] = '\0';
		filefrag[i] = '\0';
		filecoag[i] = '\0';
		i++;
	}
	while(f_distr[i] != '\0' || f_mass[i] != '\0');
	strcat(f_distr, "-distr_r.txt");
	strcat(f_mass, "-massd.txt");
	strcat(f_star, "-star.txt");
	strcat(f_Ek, "-distr_Ek40.txt");
	strcat(cp, "-cp.txt");
	strcat(filefrag, "-frag.txt");
	strcat(filecoag, "-coag.txt");
  printf("outputfiles will be %s %s %s %s %s %s %s %s\n",f_txt,f_distr,f_mass,f_star,f_Ek,cp,filefrag,filecoag);
	return 0;
}


int print_paras(FILE *fp, double back_mass, double TimeContinue, double total_mass_core,char * f_rst)
{
	//float al = alpha, be = beta, q_be = q_beta, sf = SF_rate * myr, g1 = Gauss1, g2 = Gauss2, fif = fifa;
	float BEmass = mBE, rb = Rb/pc, bm = (double)back_mass/Msolar, timestep = Timestep / yr, eva = Evap_rate*100*kyr,drho = Drho, rhoc1=rhob*Drho*1e16;
	if(TimeContinue)
	{
		fprintf(fp,"this continues file %s\ninitial time is: %fmyr\n", f_rst, TimeContinue/myr);
	}
	fprintf(fp, "bin: %d\nalpha: %f\nbeta: %f\nSF_rate: %f /myr\nGaussian sigma1: %f\nGaussian sigema2: %f\nfilling factor: %f\n",bin, alpha, beta, SF_rate*myr, Gauss1, Gauss2, (double)total_mass_core/back_mass/drho);
	fprintf(fp, "Rb: %f pc\nBackground mass: %f Msolar\ntimestep: %f yr\nevaporation rate: %f%% per kyr\nrhoc: %fe-16\nDensity contrast: %f\n", rb, bm, timestep, eva, rhoc1, drho);
	fprintf(fp, "v_m index: %f\n", v_m);
	fprintf(fp, "Bonnor-Ebert mass: %f Msolar\n", BEmass/Msolar);
	fprintf(fp, "dn/dq = q^q_beta, q_beta=%f\n", q_beta);
	fprintf(fp, "\ncondensation kappa=%f\n", kappa);
	fprintf(fp, "\nvelocity dispersion=%f\n", vc);
	return 0;
}

int readdata(double *mytime, double *TimeContinue, int *ff, int *ff2, char *f_rst)
{
	int i;
//	char y[25], z[25];
	FILE *fpdata;
	strcat(f_rst,"-cp.txt");
  fpdata = fopen(f_rst, "r");
	fscanf(fpdata, "%lf", TimeContinue);
	mytime[0] = TimeContinue[0];
	fscanf(fpdata, "%lf", &star_mass);
	fscanf(fpdata, "%lf", &back_mass);
	fscanf(fpdata, "%lf", &ghost_mass);
	for(i = 0; i<100; i++) 
	{
		fscanf(fpdata, "%lf", n+i);
	}
	for(i = 0; i<100; i++)
	{
		fscanf(fpdata, "%lf", v_d+i);
	}
	for(i = 0; i<100; i++)
	{
		fscanf(fpdata, "%lf", n_star);
	}
	fscanf(fpdata, "%d\n%d", ff, ff2);
	fclose(fpdata);
	return 0;
}


int dataoutput2(double result[15][100], double result_star[15][100], double Ek_evo[15][100], int countcolumn, char*f_distr, char *f_star, char*f_Ek, int countcolumncf, char *filefrag, char *filecoag, double frag[15][100], double coag[15][100], double TimeContinue)
{
	int i = 0, j = 0;
	FILE* fptemp, *fpfrag, *fpcoag, *fpEk, *fpstar;
	fptemp = fopen(f_distr,"w");
	fpEk = fopen(f_Ek, "w");
	fpstar = fopen(f_star, "w");
	fpfrag = fopen(filefrag, "w");
  fpcoag = fopen(filecoag, "w");
  
	for(i = 0; i < 100; i++) /* 100 is the total number of bins*/
	{
		if(TimeContinue==0)
		{
			fprintf(fptemp,"%f\t",m_insolar[i]);
			fprintf(fpEk,"%f\t",m_insolar[i]);
			fprintf(fpstar,"%f\t",m_insolar[i]);
  			fprintf(fpfrag,"%f\t",m_insolar[i]);
    			fprintf(fpcoag,"%f\t",m_insolar[i]);
		}
		for(j = 0; j < countcolumn; j++)
		{
			fprintf(fptemp, "%f\t", result[j][i]);
			fprintf(fpfrag, "%f\t", frag[j][i]);
			fprintf(fpcoag, "%f\t", coag[j][i]);
			fprintf(fpEk, "%f\t", Ek_evo[j][i]/pow(10,40));
			fprintf(fpstar, "%f\t", result_star[j][i]);
		}
		fprintf(fptemp, "\n");
		fprintf(fpfrag, "\n");
		fprintf(fpcoag, "\n");
		fprintf(fpEk, "\n");
		fprintf(fpstar, "\n");
//		for(j = 0; j < countcolumncf - 1; j++)
//		{
//!!			fprintf(fpfrag, "%f\t", frag[j][i]);
//!!			fprintf(fpcoag, "%f\t", coag[j][i]);
//		}
//!!		fprintf(fpfrag, "%f\n", frag[j][i]);
//!!		fprintf(fpcoag, "%f\n", coag[j][i]);
	}
	fclose(fpEk);
	fclose(fptemp);
	fclose(fpstar);
	fclose(fpfrag);
	fclose(fpcoag);
	return 1;
}
int finalize(double mytime, FILE *fp, char *cp, int ff, int ff2)
{
	int i;
	double time1;
	time1 = (double)(mytime/myr);
	fprintf(fp, "%lf myr\n", time1);
	fprintf(fp, "cost time: %fs\n", (double)(finish - start + start2 - end2)/CLOCKS_PER_SEC);
	fclose(fp);
	FILE *fcp;
	fcp = fopen(cp,"w");
	fprintf(fcp, "#mytime = %f\n", mytime);
	fprintf(fcp, "#star_mass = %f\n", star_mass);
	fprintf(fcp, "#back_mass = %f\n", back_mass);
	fprintf(fcp, "#ghost_mass = %f\n", ghost_mass);
	fprintf(fcp, "#Nbin N VD NSTAR\n", ghost_mass);
	fprintf(fcp, "#[1] [2] [3] [4]\n", ghost_mass);
	for(i = 0; i<100; i++)
	{
		fprintf(fcp, "%d %f %f %f\n", i,n[i],v_d[i],n_star[i]);
	}
	/*fprintf(fcp, "\n");
	*for(i = 0; i<100; i++)
	*{
	*	fprintf(fcp, "%f\n", v_d[i]);
	*}
	*for(i = 0; i<100; i++)
	*{
	*	fprintf(fcp, "%f\n", n_star[i]);
	*}*/
	fprintf(fcp, "%d\n%d\n", ff, ff2);
	fclose(fcp);
	return 1;
};



