#include "init.h"

void initialiser_joueurs(S_joueur joueurs[NB_max_joueurs], int *nb_joueurs)
{
    do{
        printf("Combien de joueurs autour de la table ? (1-8) ");
        scanf("%d",nb_joueurs);
        fflush(stdin);//Au cas où l'utilisateur n'écrit pas un entier
    }while(*nb_joueurs<1 || *nb_joueurs>NB_max_joueurs);
    
    system("pause");
    system("cls");

    for(int i=0; i<*nb_joueurs; i++)
    {
        printf("Veuillez entrer le nom du joueur %d (max %d caracteres):\n",i+1,DIM_STR);
        gets_limite(DIM_STR,joueurs[i].nom);
        printf("Le joueur %d s'appelle: %s\n\n", i+1, joueurs[i].nom);
        system("pause");
        system("cls");

        for(int j=0; j<DIM_main_joeur; j++)//Initialisation des cartes à CARTE_NULLE
            joueurs[i].cartes[j]=CARTE_NULLE;
        
        joueurs[i].nb_jetons=3;
    }
}