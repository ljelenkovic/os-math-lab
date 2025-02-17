#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mqueue.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "postavke.h"
#include "slucajni_brojevi.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
	int cijev;

	if (argc < 2) {
		fprintf(stderr, "Upotreba: %s PID\n", argv[0]);
		exit(1);
	}

	lcg_postavi((long long) time(NULL));

	mqd_t opisnik_reda;
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_PORUKA_U_REDU;
	attr.mq_msgsize = MAX_VELICINA_PORUKE;
	opisnik_reda = mq_open(NAZIV_REDA, O_WRONLY | O_CREAT, 00600, &attr);
	if (opisnik_reda == (mqd_t) -1) {
		perror("klijent:mq_open");
		return -1;
	}

	pid_t pid = (pid_t) atoi(argv[1]);

	if (mkfifo(NAZIV_CIJEVI, S_IWUSR | S_IRUSR))
		perror("klijent:mkfifo"); /* možda već postoji */

	cijev = open(NAZIV_CIJEVI, O_RDONLY); /* čekaj da i pisač otvara */
	if (cijev == -1) {
		perror("klijent:open");
		exit(1);
	}
	printf("klijent otvorio cijev\n");

	int signali[] = {SIGINT, SIGUSR1, SIGUSR2};
	char *signalis[] = {"SIGINT", "SIGUSR1", "SIGUSR2"};

	while(1) {
		sleep(3);
		int akcija = lcg_gen() % 3;
		int brojeva = 1;

		if (signali[akcija] == SIGINT || signali[akcija] == SIGUSR2) {
			brojeva = lcg_gen() % 15 + 1;
			char poruka[3];
			sprintf(poruka, "%d", brojeva);
			size_t duljina = strlen (poruka) + 1;
			unsigned prioritet = 10;
			if (mq_send(opisnik_reda, poruka, duljina, prioritet)) {
				perror("mq_send");
				exit(1);
			}
		}
		printf("Saljem signal %s (brojeva=%d)\n", signalis[akcija], brojeva);
		kill(pid, signali[akcija]);

		if (signali[akcija] == SIGINT)
			continue;

		int i;
		for (i = 0; i < brojeva; i++) {
			//očekuje 'brojeva' podataka; toliko ih treba i poslati čak i ako ih nema
			long broj = 0;
			read(cijev, &broj, sizeof(broj));
			printf("Primljeno: %ld\n", broj);
		}
	}

	return 0;
}