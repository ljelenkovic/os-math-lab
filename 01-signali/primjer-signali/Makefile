# Primjer datoteke za prevođenje

CFLAGS = -Wall
LDFLAGS = -O
LDLIBS =

PROGRAM = signali
KOD = signali.c

$(PROGRAM): $(KOD)
	$(CC) $(KOD) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(PROGRAM)

.PHONY: pokreni obrisi
pokreni: $(PROGRAM)
	@./$(PROGRAM)

obrisi:
	-rm -rf $(PROGRAM)
