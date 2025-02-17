//Generator slučajnih brojeva prema LCG algoritmu - sučelje

#include <stdio.h>

long long lcg_postavi(long long new_seed);
long lcg_gen();

int lcg_zapisi_stanje(FILE *fp);
int lcg_ucitaj_stanje(FILE *fp);
