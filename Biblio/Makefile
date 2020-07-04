CC=gcc
CFLAGS=
EXEC=biblio_arbrelex biblio_liste biblio_tabdyn biblio_hachage

all: $(EXEC)

biblio_hachage: biblio_hachage.o parser.o biblio.o main.o
	$(CC) $(CFLAGS) -o biblio_hachage biblio_hachage.o parser.o biblio.o main.o -lm

biblio_tabdyn: biblio_tabdyn.o parser.o biblio.o main.o
	$(CC) $(CFLAGS) -o biblio_tabdyn biblio_tabdyn.o parser.o biblio.o main.o

biblio_arbrelex: biblio_arbrelex.o parser.o biblio.o main.o
	$(CC) $(CFLAGS) -o biblio_arbrelex biblio_arbrelex.o parser.o biblio.o main.o
	
biblio_liste: biblio_liste.o parser.o biblio.o main.o
	$(CC) $(CFLAGS) -o biblio_liste biblio_liste.o parser.o biblio.o main.o

main.o : main.c biblio.h
	$(CC) $(CFLAGS) -c main.c

biblio_liste.o: biblio_liste.c biblio_liste.h biblio.h
	$(CC) $(CFLAGS) -c biblio_liste.c

biblio_tabdyn.o: biblio_tabdyn.c biblio_tabdyn.h biblio.h
	$(CC) $(CFLAGS) -c biblio_tabdyn.c

biblio_hachage.o: biblio_hachage.c biblio_hachage.h biblio.h
	$(CC) $(CFLAGS) -c biblio_hachage.c

biblio_arbrelex.o: biblio_arbrelex.c biblio_arbrelex.h biblio.h
	$(CC) $(CFLAGS) -c biblio_arbrelex.c

parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c
	
biblio.o: biblio.c biblio.h parser.h
	$(CC) $(CFLAGS) -c biblio.c

clean:
	rm -f *.o $(EXEC)
