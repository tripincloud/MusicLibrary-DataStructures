#include "biblio.h"

Biblio *charge_n_entrees(const char *fichier, int number)
{
    Biblio *Bib = nouvelle_biblio ();
    FILE *file = fopen(fichier , "r");
    if (file == NULL) {
        printf("Fichier %s non trouve\n", fichier);
        exit(1);
    }
    
    int i = 0;
    while (!end_of_file(file) && i < number) {
        int num;
        char *title = NULL;
        char *artist = NULL;
        int ltitle, lartist;
        
        if (!(parse_int(file, &num)
            && parse_char(file, '\t')
            && parse_string(file, &title, &ltitle, '\t')
            && parse_char(file, '\t')
            && parse_string(file, &artist, &lartist, '\n')
            && parse_char(file, '\n'))) {
            printf("Format de fichier incorrect a la ligne %d\n", i+1);
            exit(1);
       }
       
       insere(Bib, num, title, artist);
       i++;
    }
    fclose(file);
    return Bib;    
}



