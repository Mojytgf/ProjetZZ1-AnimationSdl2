CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_ttf -lm

all: mon_programme

mon_programme: graphe.o methode_de_fourmie.o recuit_simule.o  main.o
	$(CC) $(CFLAGS) -o mon_programme graphe.o methode_de_fourmie.o recuit_simule.o main.o $(LDFLAGS)

graphe.o: graphe.c graphe.h
	$(CC) $(CFLAGS) -c graphe.c

methode_de_fourmie.o: methode_de_fourmie.c methode_de_fourmie.h graphe.h
	$(CC) $(CFLAGS) -c methode_de_fourmie.c

recuit_simule.o: recuit_simule.c recuit_simule.h graphe.h
	$(CC) $(CFLAGS) -c recuit_simule.c

main.o: main.c methode_de_fourmie.h recuit_simule.h graphe.h
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean
clean:
	rm -f mon_programme graphe.o recuit_simule.o methode_de_fourmie.o main.o
