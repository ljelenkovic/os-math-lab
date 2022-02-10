/* Zaglavlje s definicijom sučelja diska i veličinom i brojem blokova */

#pragma once

#define BLOCKS 16
#define BLOCK_SIZE 512

int dohvati_blok(int id, char *p);
int pohrani_blok(int id, char *p);
