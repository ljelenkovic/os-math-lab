//Neke postavke i makroi

#define DEBUG //komentirati ako se ne želi taj ispis
#define VEL_M		8
#define BROJ_DRETVI	3
#define NAZIV_CIJEVI	"/tmp/lab4cijev"
#define NAZIV_REDA	"/lab4red"
#define MAX_PORUKA_U_REDU	5
#define MAX_VELICINA_PORUKE	20

//da ne bi paralelno pristupali međuspremniku
//signali i dretve
#include <signal.h>
#include <pthread.h>

static inline void zakljucaj()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
	extern pthread_mutex_t m;
	pthread_mutex_lock(&m);
}
static inline void otkljucaj()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	extern pthread_mutex_t m;
	pthread_mutex_unlock(&m);
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
