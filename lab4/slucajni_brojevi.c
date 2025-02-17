//Generator slučajnih brojeva prema LCG algoritmu

#include "slucajni_brojevi.h"
#include "postavke.h"

//konstante iz https://en.wikipedia.org/wiki/Linear_congruential_generator
//stupac: POSIX rand48

#define A 0x5DEECE66DLL
#define C 11
#define MOD ((1LL << 48) - 1)

static long long seed = 1;

long long lcg_postavi(long long new_seed)
{
	long long old = seed;
	seed = new_seed;
	return old;
}

long lcg_gen()
{
	zakljucaj();
	seed = (A * seed + C) & MOD;
	otkljucaj();

	return (long) (seed >> 16);
}

int lcg_zapisi_stanje(FILE *fp)
{
	fprintf(fp, "%lld\n", seed);
	return 0;
}

int lcg_ucitaj_stanje(FILE *fp)
{
	fscanf(fp, "%lld\n", &seed);
	return 0;
}
