//Lab1 - signali

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include "postavke.h"
#include "slucajni_brojevi.h"
#include "medjuspremnik.h"

static int pocetno_postavljanje();
static void obradi_signal(int sig);

static int kraj_rada = 0;
static int status = 0;

int main()
{
	log("Pocetna inicijalizacija");
	if (pocetno_postavljanje())
		return -1;

	log("Inicijalizacija gotova, krecem s radom (PID=%ld)", (long) getpid());

	//glavna petlja s nekim poslom
	while (!kraj_rada) {
		sleep(1);//malo uspori
		//uzmi slučajni broj, ali da ne bude djeljiv s dva, tri ili pet
		long broj = lcg_gen();
		while ((broj & 1) == 0 || broj % 3 == 0 || broj % 5 == 0)
			broj = lcg_gen();

		while (!kraj_rada && dodaj_u_medjuspremnik(broj) == -1)
			pause(); //nema mjesta, čekaj signal

		if (kraj_rada)
			break;

		log("dodan broj %ld", broj);
	}

	//kraj_rada postavljen na SIGTERM
	FILE *fp = fopen("status.txt", "w");
	if (!fp) {
		fprintf(stderr, "Greska pri otvaranju status.txt");
		status = -1;
	}
	else {
		lcg_zapisi_stanje(fp);
		zapisi_stanje_medjuspremnika(fp);
		fclose(fp);
	}

	return status;
}

static int pocetno_postavljanje()
{
	//ako postoji datoteka status.txt iz nje pročitati stanje
	FILE *fp = fopen("status.txt", "r");

	/* Očekivani format:
	<podaci generatora slučajnih brojeva>
	<podaci iz međuspremnika>
	*/

	if (fp) {
		//postoji
		lcg_ucitaj_stanje(fp);
		ucitaj_stanje_medjuspremnika(fp);
		fclose(fp);
	}
	else {
		//ne postoji, inicijaliziraj generator slučajnih brojeva
		lcg_postavi((long long) time(NULL));
	}

	//postavi signale
	struct sigaction act;

	/* 1. maskiranje signala SIGUSR1 */
	act.sa_handler = obradi_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);

	/* 2. maskiranje signala SIGTERM */
	act.sa_handler = obradi_signal;
	sigemptyset(&act.sa_mask);
	sigaction(SIGTERM, &act, NULL);

	return 0;
}

static void obradi_signal(int sig)
{
	if (sig == SIGUSR1) {
		log("\nsignal SIGUSR1");
		long broj = uzmi_iz_medjuspremnika();
		printf("%ld\n", broj);
	}
	else if (sig == SIGTERM) {
		log("\nsignal SIGTERM");
		kraj_rada = 1;
	}
}
