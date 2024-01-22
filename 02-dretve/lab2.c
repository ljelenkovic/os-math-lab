/* Glavna datoteka za lab2 s funkcijom main */

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "signali.h"
#include "datoteke.h"

//globalne varijable; koriste se (ili će se koristiti) u funkcijama i obradama signala
char *dat_status, *dat_obrada, *dat_mreza;
int broj = 0;
int nije_kraj = 1;

/* funkcije koje rade dretve */
void *obrada(void *);
void *mreza(void *);

int main(int argc, char *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Koristenje: %s <status-datoteka> "
		 "<datoteka-s-podacima> <cjevovod>\n", argv[0]);
		exit(1);
	}
	dat_status = argv[1];
	dat_obrada = argv[2];
	dat_mreza = argv[3];

	postavi_signale();
	/* dohvati prvi broj i zapisi 0 u status */
	/* todo */

	/* stvori dretve: radnu i mreznu */
	/* todo */

	while(nije_kraj) {
		//procitaj broj iz konzole, npr. sa scanf
		//ako je > 0 onda ga postavi kao broj
		//inace prekidni s radom => postavi nije_kraj = 0
	}

	//cekaj na kraj dretve obrada, ali ne i one druge mrezne

	return 0;
}

void *obrada(void *p)
{
	/* vise-manje glavni dio iz lab1 */

	return NULL;
}

void *mreza(void *p)
{
	//u petlji cekaj da se nesto pojavi u cijevi
	//ako je procitano > 0 onda ga postavi u broj

	return NULL;
}
