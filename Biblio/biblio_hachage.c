#include "biblio_hachage.h"

Biblio *nouvelle_biblio(void) 
{
    Biblio *bib = malloc(sizeof(Biblio));
    bib->m = TAILLE_TABLE;
    bib->nE = 0;
    bib->T = malloc(sizeof(CellMorceau)*bib->m);// calloc(bib->m, sizeof(CellMorceau));
  	int i;
  	for (i = 0; i < bib->m; i++)
  		bib->T[i] = NULL;
    return bib;
}

void libere_biblio(Biblio *bib)
{
    int i;
    for (i = 0; i < bib->m; i++) {
        CellMorceau *cell = bib->T[i];
        while (cell != NULL) {
            CellMorceau *suppr = cell;
            cell = cell->suiv;
            free(suppr->titre);
            free(suppr->artiste);
            free(suppr);
        }
    }
    free(bib->T);
    free(bib);
}

static unsigned int fonction_cle(const char *artist)
{
    unsigned int key = 0;
    while (*artist != '\0') {
        key = key * 129 + (unsigned char)(*artist);
        artist++;
    }
    return key;
}

static unsigned int fonction_hachage(unsigned int k, int morceau)
{
    double ka = k*A;
    return (unsigned int)(morceau * (ka - floor(ka)));
}

void insere(Biblio *bib, int numero, char *tital, char *artist)
{
    CellMorceau *nouv = malloc(sizeof(CellMorceau));
    unsigned int key = fonction_cle(artist);
    nouv->cle = key;
    nouv->num = numero;
    nouv->titre = tital;
    nouv->artiste = artist;
    
    unsigned int hash = fonction_hachage(key, bib->m);
    nouv->suiv = bib->T[hash];
    bib->T[hash] = nouv;
    bib->nE++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("| %8d | %-32.32s | %-32.32s |\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *bib)
{
    int i;
    for (i = 0; i < bib->m; i++) {
        CellMorceau *cell = bib->T[i];
        while (cell != NULL) {
            afficheMorceau(cell);
            cell = cell->suiv;
        }
    }
    printf("La bibliotheque contient %d morceaux\n", bib->nE);
}



Biblio *uniques (Biblio *bib)
{
    Biblio *Bextr = nouvelle_biblio();
    long long int cpt = 0;
    int i;
    for (i = 0; i < bib->m; i++) {
        CellMorceau *cour = bib->T[i];
        while (cour != NULL) {
            CellMorceau *cour2 = bib->T[i];
            while (cour2 != NULL) {
                cpt++;
                if (cour->cle == cour2->cle
                    && strcmp(cour->titre, cour2->titre) == 0
                    && strcmp(cour->artiste, cour2->artiste) == 0
                    && cour != cour2) 
                    break;
                cour2 = cour2->suiv;
            }
            if (cour2 == NULL)
                insere(Bextr, cour->num, strdup(cour->titre), strdup(cour->artiste));
            cour = cour->suiv;
        }
    }
    
    printf("Nombre de tours : %lld\n", cpt);
    return Bextr;
}

CellMorceau * rechercheParNum(Biblio *bib, int numero)
{
	int i;
    for (i = 0; i < bib->m; i++) {
    	CellMorceau *cour = bib->T[i];
    	while (cour != NULL && cour->num != numero)
    		cour = cour->suiv;
    	if (cour != NULL)
    		return cour;
    }
    return NULL;
}


CellMorceau *rechercheParTitre(Biblio *bib, char * tital)
{
	int i;
    for (i = 0; i < bib->m; i++) {
    	CellMorceau *cour = bib->T[i];
    	while (cour != NULL && strcmp(cour->titre, tital) != 0)
    		cour = cour->suiv;
    	if (cour != NULL)
    		return cour;
    }
    return NULL;
}


Biblio *extraireMorceauxDe(Biblio *bib, char * artist)
{
	unsigned int key = fonction_cle(artist);
	unsigned int hash = fonction_hachage(key, bib->m);
	CellMorceau * morceau = bib->T[hash];
	if (morceau == NULL) return NULL;
	Biblio * bib_art = nouvelle_biblio();
	while (morceau != NULL) {
		insere(bib_art, morceau->num, strdup(morceau->titre), strdup(morceau->artiste));
		morceau = morceau->suiv;
	}
	return bib_art;
}

void insereSansNum(Biblio *bib, char *tital, char *artist)
{
	int i;
	int numeroMax = 0;
    for (i = 0; i < bib->m; i++) {
    	CellMorceau *cour = bib->T[i];
    	while (cour != NULL) {
    		if (cour->num >= numeroMax)
    			numeroMax = cour->num;
    		cour = cour->suiv;
    	}
    }
    insere(bib, numeroMax + 1, strdup(titre), strdup(artist));
}


int supprimeMorceau(Biblio *bib, int numero)
{
	if (bib->nE == 0) 
		return 0;
	
	int i;
    for (i = 0; i < bib->m; i++) {
    	CellMorceau *cour = bib->T[i];
    	if (cour != NULL) {
    		if (cour->num == numero) {
    			CellMorceau * suppr = cour;
    			bib->T[i] = suppr->suiv;
    			free(suppr->titre);
		        free(suppr->artiste);
		        free(suppr);
		        bib->nE--;
		        return 1;
    		}
    		
			while (cour->suiv != NULL && cour->suiv->num != numero)
				cour = cour->suiv;
			if (cour->suiv != NULL) {
				CellMorceau * suppr = cour;
				cour->suiv = suppr->suiv;
				free(suppr->titre);
		        free(suppr->artiste);
		        free(suppr);
		        bib->nE--;
		        return 1;
			}	
		}
    }
    return 0;
}





































