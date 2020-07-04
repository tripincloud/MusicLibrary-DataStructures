#include "biblio_liste.h"

Biblio * nouvelle_biblio(void) 
{
    Biblio *bib = malloc(sizeof(Biblio));
    bib->L = NULL;
    bib->nE = 0;
    return bib;
}

void insere(Biblio *bib, int numero, char *tital, char *artist)
{
    CellMorceau *nouv = malloc(sizeof(CellMorceau));
    nouv->num = numero;
    nouv->titre = tital;
    nouv->artiste = artist;
    
    nouv->suiv = bib->L;
    bib->L = nouv;
    bib->nE++;
}

void libere_biblio(Biblio *bib)
{
    CellMorceau * cell = bib->L;
    while (cell != NULL) {
        CellMorceau *suppr = cell;
        cell = cell->suiv;
        free(suppr->titre);
        free(suppr->artiste);
        free(suppr);
    }
    free(bib);
}

void afficheMorceau(CellMorceau *cell)
{
	printf("| %8d | %-32.32s | %-32.32s |\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *bib)
{
    CellMorceau *cell = bib->L;
    while (cell != NULL) {
        afficheMorceau(cell);
        cell = cell->suiv;
    }
    printf("La bibliotheque contient %d morceaux\n", bib->nE);
}

Biblio *uniques (Biblio *bib)
{
    Biblio *Bextr = nouvelle_biblio();
    long long int cpt = 0;
    CellMorceau *cour = bib->L;
    while (cour != NULL) {
        CellMorceau *cour2 = bib->L;
        while (cour2 != NULL) {
            cpt++;
            if (strcmp(cour->titre, cour2->titre) == 0
                && strcmp (cour->artiste, cour2->artiste) == 0
                && cour != cour2) {
                break;
            }
            cour2 = cour2->suiv;
        }
        
        if (cour2 == NULL)
            insere(Bextr, cour->num, strdup(cour->titre), strdup(cour->artiste));
        cour = cour->suiv;
    
    }
    
    printf("NB tour: %lld\n", cpt);
    return Bextr;
}

CellMorceau * rechercheParNum(Biblio *bib, int numero)
{
	CellMorceau * cell = bib->L;
	while (cell != NULL && cell->num != numero) 
		cell = cell->suiv;
	return cell; 
}

CellMorceau *rechercheParTitre(Biblio *bib, char * tital)
{
	CellMorceau * cell = bib->L;
	while (cell != NULL && strcmp(cell->titre, tital) != 0) 
		cell = cell->suiv;
	return cell;
}

Biblio *extraireMorceauxDe(Biblio *bib, char * artist)
{
	Biblio * b_art = nouvelle_biblio();
	CellMorceau * cell = bib->L;
	while (cell != NULL) {
		if (strcmp(cell->artiste, artist) == 0)
			insere(b_art, cell->num, strdup(cell->titre), strdup(cell->artiste));
		cell = cell->suiv;
	}
	if (b_art->nE == 0){
		libere_biblio(b_art);
		return NULL;
	}
	return b_art;
}


void insereSansNum(Biblio *bib, char *tital, char *artist)
{
	int max = 0;
	CellMorceau * cell = bib->L;
	while (cell != NULL) {
		if (cell->num > max)
			max = cell->num;
		cell = cell->suiv;
	}
	insere(bib, max+1, strdup(tital), strdup(artist));
}

int supprimeMorceau(Biblio *bib, int numero)
{
	if (bib->nE == 0)
		return 0;
	
	if (bib->L->num == numero){
		CellMorceau *suppr = bib->L;
		bib->L = suppr->suiv;
		bib->nE--;
   
        free(suppr->titre);
        free(suppr->artiste);
        free(suppr);
        return 1;
	}
	
	CellMorceau *cell = bib->L;
	while (cell->suiv != NULL && cell->suiv->num != numero)
		cell = cell->suiv;
	if (cell->suiv == NULL)
		return 0;
	
	CellMorceau *suppr = cell->suiv;
	cell->suiv = cell->suiv->suiv;
	
	free(suppr->titre);
    free(suppr->artiste);
    free(suppr);
    return 1;
}
































