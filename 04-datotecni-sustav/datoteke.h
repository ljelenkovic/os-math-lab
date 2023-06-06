/* Zaglavlje s definicijom konstanti i opisnika datoteka */

#pragma once

#include "disk.h"

#define IME_DULJINA 16
#define MAX_DATOTEKA 16

#define ZA_CITANJE	1
#define ZA_PISANJE	2

struct opisnik {
	char ime[IME_DULJINA];
	size_t velicina;
	ssize_t kazaljka; //koristi se pri radu s tom datotekom
	int nacin_rada;
	int blokovi[BLOCKS];
};

void inicijaliziraj_prazni_disk();
int otvori_datoteku(char *ime, int nacin);
int zatvori_datoteku(int id);
int procitaj(int id, void *p, size_t koliko);
int zapisi(int id, void *p, size_t koliko);
