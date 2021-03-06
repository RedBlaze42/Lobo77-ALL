#include "util.h"

// Change la couleur de la console en fonction des couleurs définies dans declarations.h
void color (int couleurDuTexte, int couleurDuFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
}

// Retourne l'index du joueur actuel dans la liste de joueur
int get_joueur_actuel(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    for(int i = 0; i < nb_joueurs; i++)
        if(joueurs[i].sens_jeu != 0)
            return i;

    return -1; // Si le joueur actuel n'a pas été trouvé
}

// Retourne l'index du donneur actuel dans la liste de joueur
int get_donneur(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    for(int i = 0; i < nb_joueurs; i++)
        if(joueurs[i].donneur == 1)
            return i;

    return -1; // Si le donneur n'a pas été trouvé
}

// Demande à l'utilisateur une chaine de charactère non-vide et la tronque pour avoir "limite" caractères
void gets_limite(char *sortie, int limite)
{
    fflush(stdin);
    do
    {
        fgets(sortie, limite + 1, stdin);
        strtok(sortie, "\n");  // Enlève le retour à la ligne à la fin du nom
    }while(strcmp(sortie, "\n") == 0); // Le joueur ne peut pas avoir un nom vide
    fflush(stdin);
}

// Mélange les "nb_cartes" premières cartes d'une pile grâce à l'algorithme de Fisher–Yates
void melanger_pile(int cartes[DIM_pile],int nb_cartes)
{
    int i, index_aleatoire, carte_temp;

    for (i = nb_cartes; i > 0; i--) // Parcours toute les cartes de la pile de nb_cartes vers le début
    {
        index_aleatoire = rand() % (i + 1); // Trouve une case aléatoire
        carte_temp = cartes[index_aleatoire]; // Echange la case choisie aléatoirement avec la case en cours
        cartes[index_aleatoire] = cartes[i];
        cartes[i] = carte_temp;
    }
}

// Retourne 1 si le joueur a appuyé sur une touche dans le temps imparti, 0 sinon
int attend_touche(int timeout)
{
    int start = time(NULL);
    fflush(stdin); // S'assure que le buffer est vide avant d'attendre la pression d'une touche
    while (time(NULL) - start < timeout)
    {
        printf("\rVous avez %d secondes...", (int) (timeout - (time(NULL) - start))); // Affichage du décompte
        if(kbhit()!=0) // Vérifie si une touche a été pressée
            return 1; // Une touche a été pressée dans le temps imparti
    }

    return 0; // Pas de touche pressée
}

// Propose au joueur de sélectionner une carte parmi sa mains et retourne l'index de cette carte
int selectionner_carte(S_joueur joueurs[NB_max_joueurs], S_joueur joueur, int nb_joueurs, int total_defausse)
{
    char touche;
    int curseur = 0;
    for(int i = 0; i < DIM_main_joueur; i++) // Place le curseur sur une carte non-vide
    {
        if(joueur.cartes[i] != CARTE_VIDE)
        {
            curseur = i;
            break;
        }
    }

    do // Tant que le joueur n'as pas appuyé sur enter
    {
        afficher_joueurs_et_total(joueurs, nb_joueurs, total_defausse);
        afficher_cartes(joueur, curseur);

        afficher_petit_encadre("S\x82""lectionnez avec < > puis Enter");
        touche=get_fleche_horizontale();

        switch (touche)
        {
            case TOUCHE_GAUCHE:
                for(int i = curseur - 1; i >= 0; i--)
                {
                        if(joueur.cartes[i] != CARTE_VIDE) // Trouve une carte non-vide à gauche du curseur
                        {
                            curseur = i;
                            break;
                        }
                }
                break;
            case TOUCHE_DROITE:
                for(int i = curseur + 1; i < DIM_main_joueur; i++)
                {
                        if(joueur.cartes[i] != CARTE_VIDE) // Trouve une carte non-vide à droite du curseur
                        {
                            curseur = i;
                            break;
                        }
                }
                break;

            default:
                break;
        }

    }while(touche != TOUCHE_ENTER);

    return curseur;
}

// Attend que l'utilisateur appuie sur la flèche de gauche, de droite ou enter. Et retourne la touche appuyée.
char get_fleche_horizontale()
{
    char touche = 0;
    fflush(stdin);
    do
    {
        if(kbhit())
            touche = getch();
    }while(touche != TOUCHE_GAUCHE && touche != TOUCHE_DROITE && touche != TOUCHE_ENTER);

    return touche;
}

// Attend que l'utilisateur appuie sur la flèche vers le haut, vers le bas ou enter. Et retourne la touche appuyée.
char get_fleche_verticale()
{
    char touche = 0;
    fflush(stdin);
    do
    {
        if(kbhit())
            touche = getch();
    }while(touche != TOUCHE_HAUT && touche != TOUCHE_BAS && touche != TOUCHE_ENTER);

return touche;
}

// Attend que l'utilisateur appuie sur n'importe quelle flèche ou enter. Et retourne la touche appuyée
char get_fleches()
{
    char touche = 0;
    fflush(stdin);
    do
    {
        if(kbhit())
            touche = getch();
    }while(touche != TOUCHE_GAUCHE && touche != TOUCHE_DROITE  && touche != TOUCHE_HAUT && touche != TOUCHE_BAS && touche != TOUCHE_ENTER);

    return touche;
}

// Trouve un joueur vivant à gauche ou à droite (en fonction du sens de jeu) du joueur actuel et le nomme joueur actuel
int joueur_suivant(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    int index_joueur = get_joueur_actuel(joueurs, nb_joueurs);
    int sens_jeu = joueurs[index_joueur].sens_jeu;
    joueurs[index_joueur].sens_jeu = 0;

    do
    {
        index_joueur += sens_jeu; // On prend le joueur suivant en fonction du sens du jeu

        if(index_joueur >= nb_joueurs)
            index_joueur = 0;
        else if(index_joueur < 0)
            index_joueur = nb_joueurs - 1;
    }while(joueurs[index_joueur].nb_jetons < 0 || nb_cartes_joueur(joueurs[index_joueur]) == 0); // Il faut que le joueur soit vivant

    joueurs[index_joueur].sens_jeu = sens_jeu;

    return index_joueur;
}

// Trouve un joueur vivant à gauche du donneur actuel et le nomme donneur
int donneur_suivant(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    int index_donneur = get_donneur(joueurs, nb_joueurs);
    joueurs[index_donneur].donneur = 0;

    do
    {
        index_donneur = (index_donneur + 1) % nb_joueurs; // On prend le joueur suivant en fonction du sens du jeu
    }while(joueurs[index_donneur].nb_jetons < 0); // Il faut que le donneur soit vivant

    joueurs[index_donneur].donneur = 1;

    return index_donneur;
}

// Renvoie le nombre de carte non-vides que possède un joueur
int nb_cartes_joueur(S_joueur joueur)
{
    int nb_cartes = 0;
    for(int i = 0; i < DIM_main_joueur; i++)
    {
        if(joueur.cartes[i] != CARTE_VIDE)
            nb_cartes++;
    }
    return nb_cartes;
}

// Renvoie le nombre de joueurs vivants
int nb_joueur_valide(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    int compte_joueurs_valides = 0;
    for(int i = 0; i < nb_joueurs; i++)
    {
        if(joueurs[i].nb_jetons >= 0)
            compte_joueurs_valides++;
    }

    return compte_joueurs_valides;
}

// Renvoie le nombre de joueurs encore en jeu et qui ne possèdes plus de cartes
int nb_joueurs_sans_cartes(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    int compte_joueurs_sans_cartes = 0;
    for(int i = 0; i < nb_joueurs; i++)
    {
        if(joueurs[i].nb_jetons > 0 && nb_cartes_joueur(joueurs[i]) == 0)
            compte_joueurs_sans_cartes++;
    }

    return compte_joueurs_sans_cartes;
}

// Retire un jeton à un joueur et le notifie
void retirer_jeton(S_joueur *joueur)
{
    joueur->nb_jetons--;
    color(ROUGE, NOIR);
    printf(", vous avez perdu un jeton.\n\n");

    if(joueur->nb_jetons > 0)
        printf("Il ne vous en reste plus que %d.\n\n", joueur->nb_jetons);
    else if(joueur->nb_jetons == 0)
        printf("Vous n'en avez plus, donc vous \"nagez\".\nNe perdez pas encore une fois !\n\n");
    else
        printf("Vous \"nagiez\".\nVous \x88tes donc maintenant \x82limin\x82.\n\n");
    color(BLANC, NOIR);
    system("pause");
}

// Annonce le gagnant d'une partie
void annoncer_gagnant(S_joueur joueurs[NB_max_joueurs], int nb_joueurs)
{
    system("cls");
    afficher_joueurs(joueurs, nb_joueurs);
    for(int i = 0; i < nb_joueurs; i++)
    {
        if(joueurs[i].nb_jetons >= 0)
        {
            color(VERT, NOIR);
            afficher_encadre_str("Le joueur %s a gagn\x82 !", joueurs[i].nom);
            color(BLANC, NOIR);
        }
    }
}
