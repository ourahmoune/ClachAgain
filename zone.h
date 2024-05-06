#ifndef ZONE_H_INCLUDED
#define ZONE_H_INCLUDED

///********************* NOUVEAUTE ***************************
#include "piles.h"
#include "types.h"
///********************* NOUVEAUTE ***************************

typedef pile Tzone;


TListePlayer getAllUnitInZone(Tzone *z);
Tzone creerTzoneVide(void);
Tzone ajouterUnitedansZone(Tzone z, Tunite *u);
Tzone supprimerUnitedansZone(Tzone z,Tunite *u);
bool UniteDeLaMemeCouleur (Tzone *z  , Tunite *u);
bool estvide(Tzone z);

bool UniteEstPresentedansZone(Tzone *z, Tunite *u); 

bool UniteAuSolPresente(Tzone *z);
bool UniteEnVolPresente(Tzone *z);





#endif // ZONE_H_INCLUDED
