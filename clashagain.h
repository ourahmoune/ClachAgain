#ifndef CLASHAGAIN_H_INCLUDED
#define CLASHAGAIN_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19

///********************* NOUVEAUTE ***************************
#include "zone.h"
#include "types.h"
#include <stdlib.h>
#include <stdio.h>

typedef Tunite* ** TplateauJeu; //le plateau du jeu pour l'affichage (reprise du systreme du projet clashLoyal)
typedef Tzone ** TplateauJeuUpgrade;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des Tzone

TPlayer initPlayer(Tcouleur couleur);

///********************* fin NOUVEAUTE ***************************


TplateauJeuUpgrade AlloueTab2D_Tzone(int largeur, int hauteur);  //fourni dans clashagain.c
TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);


Tunite *creeTour(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);


///********************* NOUVEAUTE ***************************


void PositionnePlayerOnPlateau_Upgade(TListePlayer player, TplateauJeuUpgrade jeuUpgrade);
void ConversionEnTplateauJeu(TplateauJeu new_jeu,TplateauJeuUpgrade jeuEncours,int largeur ,int hauteur);


void combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur);


int  nombre_aleatoire (int a , int b );
Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
bool tourRoiDetruite(TListePlayer player);
TListePlayer quiEstAPortee( Tunite*unite_attaque ,TplateauJeuUpgrade jeuEncours);
void initPlateauUpAvecNULL(TplateauJeuUpgrade jeu,int largeur, int hauteur);

///********************* NOUVEAUTE ***************************
//void AcheteUnite(TPlayer player);  //achete une unité et la rajoute dans la liste des unités de player
// Attention remarquer bien l'utilisation du type Tplayer
///********************* fin NOUVEAUTE ***************************
void deplacement (TplateauJeuUpgrade jeuEncours , int largeur , int hauteur );
Tunite * AcheteUnite(TPlayer* player);
void updatelist( TListePlayer player);
int positionX ();
TListePlayer GetAllUniteInTplateuUPgrade (TplateauJeuUpgrade jeuEncours, int largeur,int hauteur);
void sauvgardeSEQ (FILE *fichier , TPlayer player1 , TPlayer player2);
void restaurSEQ (FILE* fichier ,TPlayer *p1 , TPlayer *p2);
#endif // CLASHAGAIN_H_INCLUDED
