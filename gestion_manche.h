#ifndef INCLUDE_GESTION_MANCHE_H
#define INCLUDE_GESTION_MANCHE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "declarations.h"
#include "affichage.h"
#include "util.h"
#include "init.h"

// Programme général de gestion d'une manche
void manche(S_joueur joueurs[NB_max_joueurs], int nb_joueursw, int pile[DIM_pile], int *index_pile);

// Propose à un joueur de piocher un nombre "cartes_a_piocher" de cartes
void piocher(S_joueur joueurs[NB_max_joueurs], int nb_joueurs, S_joueur *joueur, int pile[DIM_pile], int *index_pile, int cartes_a_piocher, int total_defausse);

// Vide la défausse, la place au dessus de la pioche puis mélange la pioche
void vider_defausse(int pile[DIM_pile], int defausse[DIM_pile], int *index_pile, int *index_defausse);
// Vide la main des joueurs dans la pile. Avec une animation
void vider_main_joueurs(S_joueur joueurs[NB_max_joueurs], int nb_joueurs, int pile[DIM_pile], int *index_pile);

#endif