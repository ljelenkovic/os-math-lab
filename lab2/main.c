//Lab2 - dretve i semafori

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "postavke.h"
#include "slucajni_brojevi.h"
#include "medjuspremnik.h"

static int pocetno_postavljanje();
static void obradi_signal(int sig);
static void *posao_dretve(void *x);

static int kraj_rada = 0;
static int status = 0;
static pthread_t opisnik[BROJ_DRETVI];
sem_t sem, sem2[BROJ_DRETVI];
static long id_dretvi = 1; //svaka dretva uzima jedan id, počevši od 1

int main()
{
	sem_init(&sem, 0, 1); //potrebno zbog log
	log("Pocetna inicijalizacija");
	if (pocetno_postavljanje())
		return -1;

	log("Inicijalizacija gotova, krecem s radom (PID=%ld)", (long) getpid());

	//stvori dretve
	// NAPRAVITI

	//čekaj na kraj rada dretvi
	// NAPRAVITI

	//kraj_rada postavljen na SIGTERM, zapiši stanje
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

static void *posao_dretve(void *x)
{
	long id = __atomic_fetch_add(&id_dretvi, 1, __ATOMIC_SEQ_CST);

	log("Dretva %ld krece s radom", id);
	while (!kraj_rada) {
		// NAPRAVITI
	}
	log("Dretva %ld zavrsava", id);

	return NULL;
}

static int pocetno_postavljanje()
{
	//isto kao i prije, plus inicijalizacija semafora

	return 0;
}

static void posalji_signale_dretvama(int sig)
{
	int i;
	for (i = 0; i < BROJ_DRETVI; i++)
		sem_post(&sem2[i]);
		//pthread_kill(opisnik[i], SIGCONT);
		//ako se ovo koristi dodati i taj signal u prethodnu funkciju
}
static void obradi_signal(int sig)
{
	if (sig == SIGUSR1) {
		log("\nsignal SIGUSR1");
		long broj = uzmi_iz_medjuspremnika();
		printf("%ld\n", broj);
		posalji_signale_dretvama(sig);
	}
	else if (sig == SIGUSR2) {
		// NAPRAVITI
	}
	else if (sig == SIGTERM) {
		// NAPRAVITI
	}
	else if (sig == SIGINT) {
		// NAPRAVITI
	}
}
