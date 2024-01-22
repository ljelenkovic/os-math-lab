/* Primjer rada s datotekama */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//globalne varijable; koriste se (ili će se koristiti) u funkcijama i obradama signala
char *dat_stat, *dat_obrada;
int broj = 0;

/* funkcije za rad s datotekama */
int procitaj_status();
void zapisi_status(int broj);
void dodaj_broj(int broj);
int pronadji_zadnji_broj();

int main(int argc, char *argv[])
{
	int i, x;
	if (argc < 3) {
		printf("Koristenje: %s <status-datoteka> <datoteka-s-podacim>",
			argv[0]);
		return 1;
	}
	dat_stat = argv[1];
	dat_obrada = argv[2];

	/* simulacija rada */
	/* pocetak */
	broj = procitaj_status();
	if (broj == 0) {
		printf("program bio prekinut, potraga za brojem...\n");
		broj = pronadji_zadnji_broj();
		broj = (int) sqrt(broj);
	}
	zapisi_status(0); //radim
	printf("krecem s radom, zadnji broj=%d\n", broj);

	//simulacija obrade
	for (i = 0; i < 5; i++) {
		broj++;
		x = broj * broj;
		dodaj_broj(x);
		sleep(5);
	}

	//kraj
	zapisi_status(broj);
	printf("kraj rada, zadnji broj=%d\n", broj);

	return 0;
}

int procitaj_status()
{
	int br;
	FILE *fp;

	fp = fopen(dat_stat, "r");
	if (!fp) {
		printf("Ne mogu otvoriti %s\n", dat_stat);
		exit(1);
	}
	if (fscanf(fp, "%d", &br) != 1) {
		printf("Nije procitan broj iz %s!\n", dat_stat);
		exit(1);
	}
	fclose(fp);
	return br;
}

void zapisi_status(int br)
{
	FILE *fp;

	fp = fopen(dat_stat, "w");
	if (!fp) {
		printf("Ne mogu otvoriti %s\n", dat_stat);
		exit(1);
	}
	if (fprintf(fp, "%d\n", br) < 1) {
		printf("Nije upisan broj u %s!\n", dat_stat);
		exit(1);
	}
	fclose(fp);
}

void dodaj_broj(int br)
{
	FILE *fp;

	fp = fopen(dat_obrada, "a");
	if (!fp) {
		printf("Ne mogu otvoriti %s\n", dat_obrada);
		exit(1);
	}
	if (fprintf(fp, "%d\n", br) < 1) {
		printf("Nije upisan broj u %s!\n", dat_obrada);
		exit(1);
	}
	fclose(fp);
}

int pronadji_zadnji_broj()
{
	FILE *fp;
	int br = -1;

	fp = fopen(dat_obrada, "r");
	if (!fp) {
		printf("Ne mogu otvoriti %s\n", dat_obrada);
		exit(1);
	}
	while(!feof(fp))
		if (fscanf(fp, "%d", &br) != 1)
			break;
	fclose(fp);
	return br;
}
