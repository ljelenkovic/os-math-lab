//Neke postavke i makroi

#define DEBUG //komentirati ako se ne želi taj ispis
#define VEL_M	8
#define BROJ_DRETVI 3

//da ne bi paralelno pristupali međuspremniku
//signali i dretve
#include <signal.h>
#include <semaphore.h>
#include <stdlib.h>

static sigset_t signali_prije __attribute__((unused));

static inline void zakljucaj()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, &signali_prije);
	extern sem_t sem;
	sem_wait(&sem);
}
static inline void otkljucaj()
{
	sigprocmask(SIG_SETMASK, &signali_prije, NULL);
	extern sem_t sem;
	sem_post(&sem);
}

#ifdef DEBUG
#include <stdio.h>

//ispis, ali zelenom bojom
//korištenje: log = printf, uz \n na kraju (ne treba \n dodavati kad se koristi log)
#define log(format, ...)			\
do {						\
	zakljucaj();				\
	printf("\x1b[32m");			\
	printf(format "\n", ##__VA_ARGS__);	\
	printf("\x1b[39m");			\
	otkljucaj();				\
}						\
while(0)

#else

#define log(format, ...)

#endif
