#include "zone.h"
#include <stdlib.h>

// a vous de coder les fonctions citées dans zone.h
// + celles que vous pourriez inventer pour MANIPULER UN TZONE.

TListePlayer getAllUnitInZone(Tzone *z){
    TListePlayer list=NULL;
    Tzone zoneA=creerPileVide();
    Tunite* unite=NULL;
    while(!estVide(*z)){
        unite=tetePile(*z);
        list=AjouterUnite(list,unite);
        zoneA=empiler(zoneA , unite);
        (*z)=depiler(*z);
    }

    while(!estVide(zoneA)){
        (*z)=empiler ((*z) , tetePile(zoneA));
        zoneA=depiler(zoneA);
    }
    return list;
}
/******************************************************************************/
Tzone creerTzoneVide(void){
    Tzone z=creerPileVide();

    return z;
};

/******************************************************************************/
Tzone ajouterUnitedansZone(Tzone z, Tunite *u){
    z=empiler(z,u);
    return z;
};

/******************************************************************************/
Tzone supprimerUnitedansZone(Tzone z,Tunite *u){
    Tzone zoneA=creerPileVide();
    bool trouve= false ;

    while(!estVide(z)  && !trouve){
        if( tetePile(z) ==u){
            z=depiler(z);
            trouve=1;
        }else{
            zoneA=empiler(zoneA,tetePile(z));
            z=depiler(z);
        }
    }

    while(!estVide(zoneA)){
        z=empiler(z,tetePile(zoneA));
        zoneA=depiler(zoneA);
    }
    return z;
};

/******************************************************************************/
bool UniteEstPresentedansZone(Tzone *z, Tunite *u){
    bool presente=false;
    Tzone zoneA=creerPileVide();
    while(!estVide(*z) && !presente){
        if(tetePile(*z)==u){
            presente=1;
        }else{
            zoneA=empiler(zoneA , tetePile(*z));
            (*z)=depiler(*z);
        }
    }

    while(!estVide(zoneA)){
        (*z)=empiler((*z),tetePile(zoneA));
        zoneA=depiler(zoneA);
    }
    return presente;
};

/******************************************************************************/
bool UniteAuSolPresente(Tzone *z){
    bool sol=false;
    Tzone zoneA=creerPileVide();

    while(!estVide(*z)  && !sol){
        if(position(tetePile(*z)) ==sol ){
            sol=1;
        }
        zoneA=empiler( zoneA, tetePile(*z));
        (*z)=depiler(*z);
    }

    while(!estVide(zoneA)){
        (*z)=empiler((*z) ,tetePile(zoneA));
        zoneA=depiler(zoneA);
    }
};

/******************************************************************************/

bool UniteEnVolPresente(Tzone *z){
    bool air=false;
    Tzone zoneA=creerPileVide();
    while(!estVide(*z)  && !air){
        if(position(tetePile(*z)) ==air ){
            air=1;
        }
        zoneA=empiler(zoneA , tetePile(*z));
        (*z)=depiler(*z);
    }

    while(!estVide(zoneA)){
        (*z)=empiler((*z) , tetePile(zoneA));
        zoneA=depiler(zoneA);
    }
};
/******************************************************************************/
bool estvide(Tzone z){
    return estVide(z);
};

/******************************************************************************/
Tunite* teteTzone (Tzone z){
    return tetePile(z);
};
/******************************************************************************/
bool UniteDeLaMemeCouleur (Tzone *z  , Tunite *u){
    Tcouleur color=getcolor(u);
    bool samecolor= true;
    Tunite *unite=NULL;
    Tzone zoneA=creerPileVide();
    while(!estVide(*z) && samecolor ){
        unite=tetePile(*z);
        if(getcolor(unite) != samecolor){
            samecolor=0;
        }else{
            zoneA=empiler(zoneA , tetePile(*z));
            (*z)=depiler(*z);
        }
    }

    while(!estVide(zoneA)){
        (*z)=empiler((*z),tetePile(zoneA));
        zoneA=depiler(zoneA);
    }
    return samecolor;
};
/******************************************************************************/
/*                       test (a sup)                     */


/*                       test (a sup)                     */
