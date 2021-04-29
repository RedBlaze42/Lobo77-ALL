#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "util.h"
#include "init.h"
#include "gestion_manche.h"
#include "affichage.h"
#include "declarations.h"
#include "debug.h"

int main()
{
    srand(time(NULL));
    color(BLANC, NOIR);
    //SetConsoleOutputCP(1252);
    apparence_console();

    index_pile = DIM_pile-1;
    initialiser_pile(pile);
    melanger_pile(pile, index_pile);

    banniere();
    printf("Bienvenue sur LOBO77. Par Hugo ALLAIRE et Tom ALLARD\n\n");

    initialiser_joueurs(joueurs, &nb_joueurs);
    donneur_aleatoire(joueurs, nb_joueurs);
    distribuer_jetons(joueurs, nb_joueurs);

    int num_manche = 1;
    do
    {
        system("cls");
        afficher_joueurs(joueurs, nb_joueurs);
        afficher_encadree_int("Manche numero: %d", num_manche);
        system("pause");

        manche(joueurs, nb_joueurs, pile, &index_pile);

        donneur_suivant(joueurs, nb_joueurs); //Rotation du donneur

        system("cls");
        afficher_joueurs(joueurs, nb_joueurs);
        afficher_encadree_int("Fin de la manche %d", num_manche);
        color(JAUNE, NOIR); printf("\nLe nouveau donneur est %s\n\n", joueurs[get_donneur(joueurs, nb_joueurs)].nom); color(BLANC, NOIR);
        system("pause");
        num_manche++;
    } while (nb_joueur_valide(joueurs, nb_joueurs) > 1); //TODO rotation donneur

    system("cls");
    afficher_joueurs(joueurs, nb_joueurs);
    for(int i = 0; i < nb_joueurs; i++)
    {
        if(joueurs[i].nb_jetons >= 0)
        {
            color(VERT, NOIR);
            afficher_encadree_str("Le joueur %s a gagne !", joueurs[i].nom);
            color(BLANC, NOIR);
        }
    }

    system("pause");

    return 0;
}
