#include "biblio_arbrelex.h"

Biblio *nouvelle_biblio(void) 
{
    Biblio *Bib = malloc(sizeof(Biblio));
    Bib->A = NULL;
    Bib->nE = 0;
    return Bib;
}


static void libere_noeud(Noeud *noeud)
{
    if (noeud == NULL) return;
    CellMorceau *it = noeud->liste_morceaux;
    while (it != NULL) {
    	CellMorceau *suppr = it;
    	it = it->suiv;
        free(suppr->titre);
        free(suppr->artiste);
        free(suppr);
    }
    
    
    libere_noeud(noeud->liste_car);
    libere_noeud(noeud->car_suiv);
    free(noeud);
}

void libere_biblio(Biblio *Bib)
{
    libere_noeud(Bib->A);
    free(Bib);
}

static Noeud * creerNoeud(char lettre)
{
	Noeud *n = malloc(sizeof(Noeud));
	n->liste_car = NULL;
	n->car_suiv = NULL;
	n->liste_morceaux = NULL;
	n->car = lettre;
	return n;
}

static Noeud *chercheParmiAlternatives(Noeud *noeud, char c)
{
	if (noeud == NULL) return NULL;
	if (noeud->car == c) return noeud;
	return chercheParmiAlternatives(noeud->liste_car, c);
}

static Noeud* insererNoeud(Noeud *noeud, int numero, char *titre, char *artiste)
{
	Noeud *nd_aretourner;
	Noeud *nd = chercheParmiAlternatives(noeud, *artiste);
	if (nd == NULL){
		nd = creerNoeud(*artiste);
		nd->liste_car = noeud; 
		nd_aretourner = nd; 	}
	else {
		nd_aretourner = noeud;
	}
	
	Noeud *tmp = nd, *noeud_fils;
	int i = 1;
	while (i < strlen(artiste)){
		noeud_fils = chercheParmiAlternatives(tmp->car_suiv, artiste[i]);
		if (noeud_fils == NULL) {
			noeud_fils = creerNoeud(artiste[i]);
			noeud_fils->liste_car = tmp->car_suiv; 
			tmp->car_suiv = noeud_fils;	
		}
		tmp = noeud_fils;
		i++;
	}
	
	CellMorceau *m = malloc(sizeof(CellMorceau));
	m->titre = titre; m->num = numero; m->artiste = artiste; 
	m->suiv = tmp->liste_morceaux;
	tmp->liste_morceaux = m;
	return nd_aretourner;
}


void insere(Biblio *bib, int numero, char *titre, char *artiste)
{
    
    bib->A = insererNoeud(bib->A, numero, titre, artiste);
    
    bib->nE++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("| %8d | %-32.32s | %-32.32s |\n", cell->num, cell->titre, cell->artiste);
}

static void affiche_cell(Noeud *A)
{
    if (A == NULL) return;
    CellMorceau *it = A->liste_morceaux;
    while (it != NULL) {
    	afficheMorceau(it);
    	it = it->suiv;
    }
    
    affiche_cell(A->car_suiv);
    affiche_cell(A->liste_car);
}

void affiche(Biblio *bib)
{
    affiche_cell(bib->A);
    printf("La bibliotheque contient %d morceaux\n", bib->nE);
}

static long long int noeuds_uniques(Biblio *Bextr, Noeud *A)
{
    if (A == NULL) return 0;
    long long int cpt = 0;
    CellMorceau *cour = A->liste_morceaux;
    while (cour != NULL) {
        CellMorceau *cour2 = A->liste_morceaux;
        while (cour2 != NULL) {
            cpt++;
            if (strcmp(cour->titre, cour2->titre) == 0 && cour != cour2)
                break;
            cour2 = cour2->suiv;
        }
        if (cour2 == NULL)
            insere(Bextr, cour->num, strdup(cour->titre), strdup(cour->artiste));
        cour = cour->suiv;
    }
    cpt +=  noeuds_uniques(Bextr, A->car_suiv);
    cpt += noeuds_uniques(Bextr, A->liste_car);
    return cpt;
}



Biblio *uniques (Biblio *bib)
{
    Biblio *Bextr = nouvelle_biblio();
    long long int cpt = noeuds_uniques(Bextr, bib->A);
    printf("NB tour: %lld\n", cpt);
    return Bextr;
}
static CellMorceau *rechercheParNumNoeud(Noeud *noeud, int numero)
{
	if (noeud == NULL) return NULL;
	CellMorceau *tmp = noeud->liste_morceaux;
	while (tmp != NULL && tmp->num != numero)
		tmp = tmp->suiv;
	if (tmp != NULL) return tmp;
	
	tmp = rechercheParNumNoeud(noeud->liste_car, numero);
	if (tmp != NULL) return tmp;
	tmp = rechercheParNumNoeud(noeud->car_suiv, numero);
	return tmp;
}

CellMorceau * rechercheParNum(Biblio *bib, int numero)
{
	if (bib->nE == 0) return NULL;
	
	return rechercheParNumNoeud(bib->A, numero);
}


static CellMorceau *rechercheParTitreNoeud(Noeud *noeud, char * titre)
{
	if (noeud == NULL) return NULL;
	CellMorceau *tmp = noeud->liste_morceaux;
	while (tmp != NULL && strcmp(tmp->titre, titre) != 0)
		tmp = tmp->suiv;
	if (tmp != NULL) return tmp;
	
	tmp = rechercheParTitreNoeud(noeud->liste_car, titre);
	if (tmp != NULL) return tmp;
	tmp = rechercheParTitreNoeud(noeud->car_suiv, titre);
	return tmp;
}


CellMorceau *rechercheParTitre(Biblio *bib, char * titre)
{
	if (bib->nE == 0) return NULL;
	
	return rechercheParTitreNoeud(bib->A, titre);
}


static Noeud * rechercheNoeudRacine(Noeud *noeud, char *chaine)
{
	if (noeud == NULL) return NULL;
	
	if (strlen(chaine) == 1) {
		if (noeud->car == *chaine) 
			return noeud;
		Noeud *tmp = noeud->liste_car;
		while (tmp && tmp->car != *chaine)
			tmp = tmp->liste_car;
		return tmp;
	}
	
	if (noeud->car == *chaine) 
		return rechercheNoeudRacine(noeud->car_suiv, chaine+1);
	
	Noeud *tmp = noeud->liste_car;
	while (tmp && tmp->car != *chaine)
		tmp = tmp->liste_car;
	if (tmp == NULL)
		return NULL;
	return rechercheNoeudRacine(tmp->car_suiv, chaine+1);
}

Biblio *extraireMorceauxDe(Biblio *bib, char * artiste)
{
	if (bib->nE == 0) return NULL;
	Noeud * n = rechercheNoeudRacine(bib->A, artiste);
	if (n == NULL) return NULL;
	CellMorceau *tmp = n->liste_morceaux;
	if (tmp == NULL) return NULL;
	
	Biblio *b_art = nouvelle_biblio();
	while (tmp != NULL) {
		insere(b_art, tmp->num, strdup(tmp->titre), strdup(tmp->artiste));
		tmp = tmp->suiv;
	}
	return b_art;
}

static void morceauNumMax(Noeud *noeud, int *numero_max)
{
	if (noeud == NULL) return;
	
	CellMorceau *tmp = noeud->liste_morceaux;
	while (tmp != NULL) {
		if (tmp->num > *numero_max)
			*numero_max = tmp->num;
		tmp = tmp->suiv;
	}
	
	morceauNumMax(noeud->liste_car, numero_max);
	morceauNumMax(noeud->car_suiv, numero_max);
}


void insereSansNum(Biblio *bib, char *titre, char *artiste)
{
	int numero_max = 0;
	morceauNumMax(bib->A, &numero_max);
	insere(bib, num_max+1, strdup(titre), strdup(artiste));
}

static Noeud * rechercheNoeudDe(Noeud *racine, int num)
{
	if (racine == NULL) return NULL;
	CellMorceau *tmp = racine->liste_morceaux;
	while (tmp != NULL && tmp->num != numero)
		tmp = tmp->suiv;
	
	if (tmp != NULL) return racine;
	
	Noeud *tmpN = rechercheNoeudDe(racine->liste_car, numero); 
	if (tmpN != NULL) return tmpN;
	return rechercheNoeudDe(racine->car_suiv, numero);
}


int supprimeMorceau(Biblio *bib, int numero)
{
	Noeud *nodeOfNum = rechercheNoeudDe(bib->A, numero);
	
	if (nodeOfNum == NULL) return 0;
	CellMorceau *tmp = nodeOfNum->liste_morceaux;
	if (tmp->num == numero) {
		CellMorceau *suppr = tmp;
		nodeOfNum->liste_morceaux = suppr->suiv;
		bib->nE--;
   
        free(suppr->titre);
        free(suppr->artiste);
        free(suppr);
        return 1;
	}
	
	CellMorceau *c = nodeOfNum->liste_morceaux;
	while (c->suiv->num != numero)
		c = c->suiv;
	
	
	CellMorceau *suppr = c->suiv;
	c->suiv = suppr->suiv;
	
	free(suppr->titre);
    free(suppr->artiste);
    free(suppr);
    bib->nE--;
    return 1;
}
































