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
static void stvori_dretve(int n);
static void *posao_dretve(void *x);

static int kraj_rada = 0;
static int status = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t red = PTHREAD_COND_INITIALIZER;

static int broj_dretvi = BROJ_DRETVI;
static int postavljeni_broj_dretvi = BROJ_DRETVI;
static long id_dretvi = 1;

int main()
{
	log("Pocetna inicijalizacija");
	if (pocetno_postavljanje())
		return -1;

	log("Inicijalizacija gotova, krecem s radom (PID=%ld)", (long) getpid());

	//stvori dretve
	stvori_dretve(BROJ_DRETVI);

	//čekaj na kraj rada dretvi
	while (!kraj_rada)
		pause();

	//ako još koja dretva nije gotova
	sleep(1);

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

static void stvori_dretve(int n)
{
}

static void *posao_dretve(void *x)
{
	pthread_detach(pthread_self());

	long id = __atomic_fetch_add(&id_dretvi, 1, __ATOMIC_SEQ_CST);

	log("Dretva %ld krece s radom", id);
	while (!kraj_rada) {
		//napraviti
	}
	log("Dretva %ld zavrsava", id);

	return NULL;
}

static int pocetno_postavljanje()
{
	//napraviti

	return 0;
}

static void obradi_signal(int sig)
{
	if (sig == SIGUSR1) {
		log("\nsignal SIGUSR1");
		long broj = uzmi_iz_medjuspremnika();
		printf("%ld\n", broj);
		pthread_cond_broadcast(&red);
	}
	else if (sig == SIGUSR2) {
	}
	else if (sig == SIGTERM) {
	}
	else if (sig == SIGINT) {
	}
}
