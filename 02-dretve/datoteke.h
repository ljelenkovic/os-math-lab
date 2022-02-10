/* Zaglavlje za sučelja s operacijama nad datotekama */

#pragma once /* da se ovo zagljave ne uključuje više puta u istu datoteku */

extern char *dat_status, *dat_obrada, *dat_mreza;
/* funkcije za rad s datotekama */
int procitaj_status();
void zapisi_status(int broj);
void dodaj_broj(int broj);
int pronadji_zadnji_broj();
int dohvati_iz_cijevi();
