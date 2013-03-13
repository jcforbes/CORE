#ifndef IO_H
#define IO_H
#include "define.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;
vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim) ;
int filename_gen(char *f_txt, char*f_distr, char*f_mass, char*f_star, char*f_Ek, char*cp, char*filefrag, char*filecoag);

int print_paras(FILE *fp, double back_mass, double TimeContinue, double total_mass_core, char *f_rst);
int readdata(double *mytime, double *TimeContinue, int *ff, int *ff2, char *f_rst);
int dataoutput2(double result[15][100], double result_star[15][100], double Ek_evo[15][100], int countcolumn, char*f_distr, char *f_star, char*f_Ek, int countcolumncf, char *filefrag, char *filecoag, double frag[15][100], double coag[15][100], double TimeContinue);
int finalize(double mytime, FILE *fp, char *cp, int ff, int ff2);
#endif
