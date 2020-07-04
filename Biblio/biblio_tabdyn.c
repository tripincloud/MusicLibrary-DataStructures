#include "biblio_tabdyn.h"

Biblio *nouvelle_biblio(void) 
{
    Biblio *bib = malloc(sizeof(Biblio));
    bib->T = NULL;
    bib->nE = 0;
    bib->capacite = 0;
    return bib;
}

void libere_biblio(Biblio *bib)
{
    int i;
    for(i=0; i < bib->nE; i++) {
        free(bib->T[i].titre);
        free(bib->T[i].artiste);
    }
    free(bib->T);
    free(bib);
}


static void double_capacite(Biblio *bib)
{
    if (bib->T == NULL) {
        bib->T = malloc(sizeof(CellMorceau));
        bib->capacite = 1;
        return;
    }
    bib->capacite *= 2;
    bib->T = realloc(bib->T, bib->capacite * sizeof(CellMorceau));
}


void insere(Biblio *bib, int numero, char *tital, char *artist)
{
    if (bib->capacite == bib->nE) double_capacite(bib);
    CellMorceau * morceau = &bib->T[bib->nE];
    morceau->titre = tital;
    morceau->artiste = artist;
    morceau->num = numero;
    bib->nE++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("| %8d | %-32.32s | %-32.32s |\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *bib)
{
    CellMorceau *it = bib->T;
    while (it != bib->T + bib->nE) {
        afficheMorceau(it);
        it ++;
    }
    printf("La bibliotheque contient %d morceaux [Capacite : %d]\n", bib->nE, bib->capacite);
}



Biblio *uniques (Biblio *bib)
{
    Biblio *Bextr = nouvelle_biblio();
    long long int cpt = 0;
    CellMorceau *it = bib->T;
    CellMorceau *end = bib->T + bib->nE;
    while (it != end) {
        CellMorceau *it2 = bib->T;
        while (it2 != end) {
            cpt++;
            if (strcmp(it->titre, it2->titre) == 0
                && strcmp(it->artiste, it2->artiste) == 0
                && it != it2)
                break;
            it2++;
        }
        if (it2 == bib->T + bib->nE)
            insere(Bextr, it->num, strdup(it->titre), strdup(it->artiste));
        it++;
    }
    
    printf("Nombre de tours : %lld\n", cpt);
    return Bextr;
}


CellMorceau * rechercheParNum(Biblio *bib, int numero)
{
	if (bib == NULL) return NULL;
	int i = 0;
	for (i = 0; i < bib->nE; i++)
		if ((bib->T + i)->num == numero)
			return bib->T + i;
	return NULL;
}


CellMorceau *rechercheParTitre(Biblio *bib, char * tital)
{
	if (bib == NULL) return NULL;
	int i = 0;
	for (i = 0; i < bib->nE; i++)
		if (!strcmp((bib->T + i)->titre, tital))
			return bib->T + i;
	return NULL;
}


Biblio *extraireMorceauxDe(Biblio *bib, char * artist)
{
	Biblio* nB = nouvelle_biblio();
	int i = 0;
	for (i = 0; i < bib->nE; i++)
		if (!strcmp((bib->T + i)->artiste, artist)) {
			CellMorceau * morc = bib->T + i;
			insere(nB, morc->num, strdup(morc->titre), strdup(morc->artiste));
		}
	if (nB->nE == 0) {
		libere_biblio(nB);
		return NULL;
	}
	return nB;
}

void insereSansNum(Biblio *bib, char *tital, char *artist)
{
	insere(bib, bib->nE, strdup(tital), strdup(artist)); 
}


int supprimeMorceau(Biblio *bib, int numero)
{
	if (bib == NULL || bib->nE == 0) return 0;
	int i = 0;
	while (i < bib->nE && (bib->T + i)->num != numero)
		i ++;
	if (i == bib->nE) return 0;
	free(bib->T[i].titre);
	free(bib->T[i].artiste);
	int j;
	for (j = i+1; j < bib->nE; j++) {
		bib->T[j-1].num = bib->T[j].num;
		bib->T[j-1].titre = bib->T[j].titre;
		bib->T[j-1].artiste = bib->T[j].artiste;
	}
	bib->nE--;
	if (bib->nE == bib->capacite/2) {
		bib->capacite/=2;
		bib->T = realloc(bib->T, bib->capacite * sizeof(CellMorceau));
	}
	return 1;
}




































