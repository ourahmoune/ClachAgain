#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;
#include <stdbool.h>
#define DEBUG 0
typedef enum{rouge,bleu} Tcouleur;
typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unit�s que l�on peut attaquer
    Tcible maposition;		//indique soit � air � soit � sol �, utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c�est petit plus c�est rapide
    int degats;
    int portee ;			//en m�tre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de g�rer le fait que chaque unit� attaque une
                            //seule fois par tour ;
                            //0 = a d�j� attaqu�, 1 = peut attaquer ce tour-ci
                            // � remettre � 1 au d�but de chaque tour
    int coutEnElixir;
    Tcouleur couleur;
} Tunite;

typedef struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unit�
} *TListePlayer;

///********************* NOUVEAUTE ***************************


typedef struct{
    TListePlayer listeU;  //la liste des unit�s du joueur
    int elixir;
    Tcouleur couleurJoueur;
} TPlayer;

Tcible position (Tunite* unite);
Tcouleur getcolor (Tunite* unite);
TListePlayer AjouterUnite(TListePlayer player, Tunite *nouvelleUnite);
TListePlayer supprimerUnite(TListePlayer player, Tunite *UniteDetruite);
TListePlayer FusionList(TListePlayer p1, TListePlayer p2);
TListePlayer creatNewListeFromFusion(TListePlayer l1 , TListePlayer l2);
TListePlayer CleanList (TListePlayer player);

///********************* fin NOUVEAUTE ***************************
/*                    fonction de comparaison              */
bool comp_vitteseAsupB(Tunite*a ,Tunite*b);
bool comp_PointDeVieAsupB(Tunite*a , Tunite*b);
/*                    fonction de tri                      */
bool listeVide( TListePlayer l);
void tri_selection_liste(TListePlayer l, bool(*fcomp)(Tunite *a, Tunite* b));
void swapPtrData( TListePlayer source, TListePlayer destination );
Tunite* getPtrData(TListePlayer l);
TListePlayer getptrNextCell(TListePlayer l);
TListePlayer getptrLastCell(TListePlayer l);
#endif // TYPES_H_INCLUDED
