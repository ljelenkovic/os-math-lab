//Kružni međuspremnik

#include "postavke.h"
#include "medjuspremnik.h"

static long medjuspremnik[VEL_M] = {}; //početno sve nule
static int prvi = 0, zadnji = 0, mjesta = VEL_M;

int dodaj_u_medjuspremnik(long broj)
{
	zakljucaj();
	if (mjesta == 0) {
		otkljucaj();
		return -1;
	}
	mjesta--;
	medjuspremnik[zadnji] = broj;
	zadnji = (zadnji + 1) % VEL_M;
	otkljucaj();

	return 0;
}

long uzmi_iz_medjuspremnika()
{
	zakljucaj();
	if (mjesta == VEL_M) {
		otkljucaj();
		return -1;
	}

	long broj = medjuspremnik[prvi];
	mjesta++;
	prvi = (prvi + 1) % VEL_M;
	otkljucaj();

	return broj;
}

int zapisi_stanje_medjuspremnika(FILE *fp)
{
	//zakljucaj();
	//bez provjere grešaka
	int ima = VEL_M - mjesta;
	fprintf(fp, "%d\n", ima);
	int i;
	for (i = 0; i < ima; i++)
		fprintf(fp, "%ld\n", medjuspremnik[(prvi + i) % VEL_M]);
	//otkljucaj();

	return 0;
}

int ucitaj_stanje_medjuspremnika(FILE *fp)
{
	//zakljucaj();
	//bez provjere grešaka
	int ima;
	fscanf(fp, "%d\n", &ima);
	int i;
	for (i = 0; i < ima; i++) {
		long broj;
		fscanf(fp, "%ld\n", &broj);
		dodaj_u_medjuspremnik(broj);
	}
	//otkljucaj();

	return 0;
}
