#include <mqueue.h>
#include "postavke.h"

int main(int argc, char *argv[])
{
	if (!mq_unlink(NAZIV_REDA))
		printf("obrisan red poruka %s\n", NAZIV_REDA);
	return 0;
}