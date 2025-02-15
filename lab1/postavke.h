//Neke postavke i makroi

#define VEL_M	8

#define DEBUG //komentirati ako se ne želi taj ispis

#ifdef DEBUG
#include <stdio.h>

//ispis, ali zelenom bojom
//korištenje: log = printf, uz \n na kraju (ne treba \n dodavati kad se koristi log)
#define log(format, ...) \
do {\
	printf("\x1b[32m");\
	printf(format "\n", ##__VA_ARGS__);\
	printf("\x1b[39m");\
}\
while(0)

#else

#define log(format, ...)

#endif


//da ne bi paralelno pristupali međuspremniku
//za sada problem može biti zbog signala
#include <signal.h>
#include <stdio.h>

static inline void zakljucaj()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
}
static inline void otkljucaj()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
}
