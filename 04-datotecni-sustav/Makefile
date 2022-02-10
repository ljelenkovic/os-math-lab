# Primjer datoteke za prevođenje

CFLAGS = -Wall -MMD
LDFLAGS = -O
LDLIBS = 

PROGRAM = lab4
OBJEKTI = lab4.o datoteke.o disk.o

$(PROGRAM): $(OBJEKTI)
	$(CC) $(LDFLAGS) $(OBJEKTI) $(LDLIBS) -o $(PROGRAM)

H_VEZE := $(OBJEKTI:.o=.d)

.PHONY: pokreni obrisi

pokreni: $(PROGRAM)
	@./$(PROGRAM)

pokreni-test: $(PROGRAM)
	@./$(PROGRAM) < ispitno-pokretanje.txt

obrisi:
	-rm -rf $(OBJEKTI) $(H_VEZE) $(PROGRAM)

-include $(H_VEZE)
