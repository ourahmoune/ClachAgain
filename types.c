#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void hello(){
    printf("hello\n");
};

Tcible position (Tunite* unite){
    return unite->maposition;
}
Tcouleur getcolor (Tunite* unite){
    return unite->couleur;
}

TListePlayer AjouterUnite(TListePlayer player, Tunite *nouvelleUnite){
    TListePlayer new_player;
    new_player=(TListePlayer)malloc(sizeof(struct T_cell ));
    new_player->pdata = nouvelleUnite;
    new_player->suiv= player;
    player= new_player;
    return new_player;
}
TListePlayer supprimerUnite(TListePlayer player, Tunite *UniteDetruite){
    TListePlayer tmp,suprime,x;
    if(player != NULL ){
        if(player->pdata == UniteDetruite){
            tmp=player->suiv;
            free(player);
            player=tmp;
        }else{
            tmp=player;
            while((tmp->suiv)->pdata != UniteDetruite && tmp != NULL){
                tmp=tmp->suiv;
            }
           if(tmp != NULL){
                suprime=tmp->suiv;
                tmp->suiv= suprime->suiv;
                free(suprime);
            }

        }
    }
    return player;
}

TListePlayer creatNewListeFromFusion(TListePlayer l1 , TListePlayer l2){
    TListePlayer NewList= NULL;
    while(l1 !=  NULL){
        NewList=AjouterUnite(NewList , l1->pdata);
        l1=l1->suiv;
    }
    while(l2 != NULL) {
        NewList=AjouterUnite(NewList , l2->pdata);
        l2=l2->suiv;
    }
    return NewList;
};

TListePlayer CleanList (TListePlayer player){
    TListePlayer tmp=player;
    while(tmp != NULL){
        if(tmp->pdata->pointsDeVie<=0 ){
            player=supprimerUnite(player , tmp->pdata);
        }
        tmp=tmp->suiv;
    }
    return player;
};


bool comp_vitteseAsupB(Tunite*a ,Tunite*b){
    return(a->vitesseAttaque>b->vitesseAttaque);
};

;

bool comp_PointDeVieAsupB(Tunite*a , Tunite*b){
    return (a->pointsDeVie>b->pointsDeVie);
};


/***********************************************************************/
/**                les fonctions utils pour les tri                 **/
bool listeVide( TListePlayer l){
    return (l==NULL);
}

TListePlayer getptrLastCell(TListePlayer l)
{
    TListePlayer courant = l;

    if (listeVide(courant)) {
        if (DEBUG) printf("Erreur getptrLastCell liste vide");
    }
    else {
        while(courant->suiv != NULL){
            courant=courant->suiv;
        }
    }
    return courant;
};
TListePlayer getptrNextCell(TListePlayer l)
{
    TListePlayer courant = l;

    if (listeVide(courant)) {
        if (DEBUG) printf("Erreur getptrNextCell liste vide");
    }
    else {
        courant=courant->suiv;
    }
    return courant;
};
Tunite* getPtrData(TListePlayer l)
{
    if (listeVide(l)) {
        if (DEBUG) printf("Erreur getPtrData liste vide");
        return NULL;  // fera planter le main
    }
    else return l->pdata;  // ptr sur notre entier stocké
};
void swapPtrData( TListePlayer source, TListePlayer destination )
{
    if (listeVide(source) || listeVide(destination)){
            if (DEBUG) printf("Erreur swapPtrData ptr = NULL");
    }
    else {  //swap
    int* tmp = source->pdata;
    source->pdata = destination->pdata;
    destination->pdata = tmp;
    }
};
void tri_selection_liste(TListePlayer l, bool(*fcomp)(Tunite *a, Tunite* b))
{
    TListePlayer en_cours, plus_petit, j, fin;  //pointeurs sur cellule donc T_liste

    fin = getptrLastCell (l); //pour ne faire qu'un seul appel de cette fonction en O(n)

    //nous ne faisons ici que des branchements et déplacements de pointeurs
    for (en_cours = l; en_cours != fin; en_cours=getptrNextCell(en_cours)) //avec "en_cours != fin", nous nous arrêtons bien sur l'avant dernière cellule
    {
        plus_petit = en_cours;
        for (j = en_cours ; j != fin; j=getptrNextCell(j))
        {
            if (fcomp(getPtrData(plus_petit),getPtrData(j)))  //MAJ fcomp
                plus_petit = j;  //branchement de "plus_petit" sur la cellule ayant une valeur pointée par data plus petite que celle pointée par plus_petit
        }
        //comparaison avec la cellule fin non comparée dans le FOR ci-dessus
        if (fcomp(getPtrData(plus_petit), getPtrData(fin))) plus_petit = fin;  //MAJ fcomp

        //swap
        swapPtrData(en_cours, plus_petit);
    }
};
/***********************************************************************/
