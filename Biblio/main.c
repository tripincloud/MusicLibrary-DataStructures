#include "biblio.h"


void menu()
{
	printf("Menu:\n");
	printf("0-Sortie\n");
	printf("1-Affichage\n");
	printf("2-Recherche morceaux uniques\n");
	printf("3-Recherche morceau par titre\n");
	printf("4-Recherche morceau par artiste\n");
	printf("5-Recherche morceau par num\n");
	printf("6-Supprimer morceau par num (! Opération irréversible !)\n");
	printf("7-Insertion d'un nouveau\n");
	printf("Votre choix : ");
}

int main(int argc, const char *argv[])
{

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}
	
	const char *nomfic = argv[1];
	int nlignes = atoi(argv[2]);
	char titre[249];
	char artiste[249];
	int num;
	printf("Lecture :\n");
	Biblio *biblio = charge_n_entrees(nomfic, nlignes);
	
	int ch;
	do {
		menu();
		int lus = scanf("%d", &ch);
		if (lus == 0)
			ch = 0;
		
		switch(ch) {
			case 1 :
				printf("Affichage\n");
				affiche(biblio);
				break;
			case 2:
				{
					Biblio *Bunique = uniques(biblio);
					if (Bunique != NULL) { 
						affiche(Bunique);
						libere_biblio(Bunique);
					} 
					else
						printf("La bibliothèque est vide !!!\n");
					break;
				}
			case 3 :
				{
					printf("Saisir le titre du morceau :\n");
					scanf(" %[^\n]", titre);
					CellMorceau * r = rechercheParTitre(biblio, titre);
					if (r == NULL) printf("Aucun morceau de titre : %s!!!\n", titre);
					else afficheMorceau(r);
					break;
				}
			case 4 :
				{
					printf("Saisir le nom de l'artiste :\n");
					scanf(" %[^\n]", artiste);
					Biblio *r = extraireMorceauxDe(biblio, artiste);
					if (r == NULL) printf("%s n'a aucun morceau dans la bibliothèque!!!\n", artiste);
					else {
						affiche(r);
						libere_biblio(r);
					}
					break;
				}
			case 5 :
				{
					printf("Saisir le num du morceau :\n");
					scanf(" %d", &num);
					CellMorceau * r = rechercheParNum(biblio, num);
					if (r == NULL) printf("Aucun morceau de num : %d!!!\n", num);
					else afficheMorceau(r);
					break;
				}
			case 6 :
				{
					printf("Saisir le num du morceau :\n");
					scanf(" %d", &num);
					if (supprimeMorceau(biblio, num)){
						printf("Le morceau %d a bien a été supprimé\n", num);
					}else{
						printf("Suppression impossible : Aucun morceau de num : %d!!!\n", num);
					}
					break;
				}
			case 7 :
				{
					printf("Saisir le nom de l'artiste :\n");
					scanf(" %[^\n]", artiste);
					printf("Saisir le titre du morceau :\n");
					scanf(" %[^\n]", titre);
					insereSansNum(biblio, titre, artiste);
					break;
				}
			default :
				ch = 0;
				break;
		
		}
		
	} while (ch != 0);
	
	libere_biblio(biblio);
	printf("Au revoir\n");
	
	return 0;
}
