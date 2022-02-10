/* Zaglavlje za sučelja s operacijama nad signalima */

#pragma once /* da se ovo zagljave ne uključuje više puta u istu datoteku */

extern int broj, nije_kraj;
/* funkcije za obradu signala */
void postavi_signale();
void obradi_dogadjaj(int sig);
void obradi_sigterm(int sig);
void obradi_sigint(int sig);
