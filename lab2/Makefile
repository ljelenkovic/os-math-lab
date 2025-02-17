# Primjer datoteke za prevođenje

CFLAGS = -Wall -MMD
LDFLAGS = -O
LDLIBS = -lm -lpthread

PROGRAM = main
OBJEKTI = main.o medjuspremnik.o slucajni_brojevi.o
STATUS = status.txt

$(PROGRAM): $(OBJEKTI)
	$(CC) $(LDFLAGS) $(OBJEKTI) $(LDLIBS) -o $(PROGRAM)

H_VEZE := $(OBJEKTI:.o=.d)

.PHONY: pokreni obrisi

pokreni: $(PROGRAM)
	@./$(PROGRAM)

obrisi:
	-rm -rf $(OBJEKTI) $(H_VEZE) $(PROGRAM) $(STATUS)

-include $(H_VEZE)
