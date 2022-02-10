#include <string.h>

#include "disk.h"

static char disk[BLOCKS][BLOCK_SIZE];

int dohvati_blok(int id, char *p)
{
	if (id < 0 || id >= BLOCKS)
		return -1;
	memcpy(p, &disk[id][0], BLOCK_SIZE);
	return 0;
}
int pohrani_blok(int id, char *p)
{
	if (id < 0 || id >= BLOCKS)
		return -1;
	memcpy(&disk[id][0], p, BLOCK_SIZE);
	return 0;
}
