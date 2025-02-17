# Primjer datoteke za prevođenje

CFLAGS = -Wall -MMD
LDFLAGS = -O
LDLIBS = -lm -lpthread

PROGRAM = main
OBJEKTI = main.o medjuspremnik.o slucajni_brojevi.o

KLIJENT = klijent
OBJEKTI2 = klijent.o slucajni_brojevi.o

STATUS = status.txt
CIJEV = /tmp/lab4cijev

all: $(PROGRAM) $(KLIJENT)

$(PROGRAM): $(OBJEKTI)
	$(CC) $(LDFLAGS) $(OBJEKTI) $(LDLIBS) -o $(PROGRAM)

$(KLIJENT): $(OBJEKTI2)
	$(CC) $(LDFLAGS) $(OBJEKTI2) $(LDLIBS) -o $(KLIJENT)

H_VEZE := $(OBJEKTI:.o=.d) $(OBJEKTI2:.o=.d)

.PHONY: pokreni obrisi slanje red_obrisi

pokreni: $(PROGRAM)
	@./$(PROGRAM)

slanje: $(KLIJENT)
	@./$(KLIJENT) `pidof $(PROGRAM)`

red_obrisi: red_obrisi.c
	$(CC) $(LDFLAGS) red_obrisi.c $(LDLIBS) -o red_obrisi
	@./red_obrisi
	@rm red_obrisi

obrisi: red_obrisi
	-rm -rf $(OBJEKTI) $(OBJEKTI2) $(H_VEZE) $(PROGRAM) \
	$(KLIJENT) $(STATUS) $(CIJEV)

-include $(H_VEZE)
