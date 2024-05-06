#include "SDL.h"
#include "clashagain.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///********************* NOUVEAUTE ***************************
#include "zone.h"
#include "types.h"

///********************* NOUVEAUTE ***************************

//types utilisés:
//typedef Tunite* ** TplateauJeu;

/**/
void PositionnePlayerOnPlateau_Upgade(TListePlayer player, TplateauJeuUpgrade jeuUpgrade){
    int x,y;
    Tunite* unite;
    while(player != NULL){
        unite= player->pdata;
        x= unite->posX;
        y= unite->posY;
        jeuUpgrade[x][y]=ajouterUnitedansZone(jeuUpgrade[x][y],unite);
        player=player->suiv;
    }

}
/**/
//=========================================================

void ConversionEnTplateauJeu(TplateauJeu new_jeu ,TplateauJeuUpgrade jeuEncours,int largeur ,int hauteur){
    TplateauJeuUpgrade tmp;
    int x,y;
    Tzone z;
    TListePlayer l=NULL;
    Tunite* unite=NULL;
    initPlateauAvecNULL(new_jeu,largeur,hauteur);
    for(int i=0; i<largeur;i++){
        for(int j=0 ;j<hauteur;j++){
            l=getAllUnitInZone(&jeuEncours[i][j]);
            while(l != NULL){
                unite=l->pdata;
                x=unite->posX;
                y=unite->posY;
                new_jeu[x][y]=unite;
                l=l->suiv;
            }
        }
    }
};
//=========================================================

TplateauJeuUpgrade AlloueTab2D_Tzone(int largeur, int hauteur){
    TplateauJeuUpgrade jeu;
    jeu = (Tzone**)malloc(sizeof(Tzone*)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tzone*)malloc(sizeof(Tzone)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
//=========================================================
int  nombre_aleatoire (int a , int b ){
    int nb;
    nb=a + rand()%(b + 1-a);
    return nb ;

}
//=========================================================
TPlayer initPlayer(Tcouleur couleur){
    TPlayer p;
    p.listeU=NULL;
    p.couleurJoueur=couleur;
    p.elixir=40;//nombre_aleatoire(2,10);
    return p;
};

//=========================================================
TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
//=========================================================
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }

}
//=========================================================
void initPlateauUpAvecNULL(TplateauJeuUpgrade jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}
//=========================================================
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};
    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}
//=========================================================
Tunite *creeTour(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tour;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
//=========================================================
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 120;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
//=========================================================
Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 2;
    return nouv;

}
//=========================================================
Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom =gargouille  ;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 1;
    return nouv;
}
//=========================================================
Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom =dragon  ;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 3;
    return nouv;

}
//=========================================================
Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom =chevalier  ;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 4;
    return nouv;
}
//=========================================================

bool tourRoiDetruite(TListePlayer player){
    bool trouve=false;
    bool detruite= true;
    while(player != NULL && !trouve ){
        if(player->pdata->nom == tourRoi){
            trouve=true;
            if(player->pdata->pointsDeVie > 0){
                detruite=false;
            }
        }
        player=player->suiv;
    }
    return detruite;
}

//=========================================================

Tunite * AcheteUnite(TPlayer* player){
    Tunite *new_unit=NULL;
    bool debiter=0;
    int nb=nombre_aleatoire(1,8); // un nombre entr e 1 et 8
    if (nb<=4){

        switch(nb){
            case 1 :{
                if((player->elixir)>=4){
                    new_unit =creeChevalier(0,0);
                    new_unit->couleur= player->couleurJoueur;
                    (player->elixir)=(player->elixir)-4;
                }
                break;

            }
            case 2:{
                if((player->elixir)>=3){
                    new_unit=creeDragon(0,0);
                    new_unit->couleur= player->couleurJoueur;
                    (player->elixir)=(player->elixir)-3;
                }else
                break;
            }
            case 3:{
                if((player->elixir)>=2){
                    new_unit=creeArcher(0,0);
                    new_unit->couleur= player->couleurJoueur;
                    (player->elixir)=(player->elixir)-2;
                }else
                break;
            }
            case 4 :{
                if((player->elixir)>=1){
                    new_unit=creeGargouille(0,0);
                    new_unit->couleur= player->couleurJoueur;
                    (player->elixir)=(player->elixir)-1;
                }else
                break;
            }
        }

    }

    return new_unit;

};


//=========================================================
void deplacement (TplateauJeuUpgrade jeuEncours , int largeur , int hauteur ){
    Tunite * unite = NULL;
    TListePlayer list= NULL ;
    Tcouleur colorplayer;
    int x,y,d; 
    for(int i=0; i<largeur ; i++){
        for(int j=0 ; j<hauteur ; j++){
            list=getAllUnitInZone(& jeuEncours[i][j] ) ;
            //vider la pile 
            while(!estvide(jeuEncours[i][j]) ){
                jeuEncours[i][j]= supprimerUnitedansZone (jeuEncours[i][j] ,teteTzone(jeuEncours[i][j]) );
            }
            while(list != NULL){
                unite=getPtrData(list);
                x=unite->posX;
                y=unite->posY;
                d=unite->vitessedeplacement;
                colorplayer = unite->couleur;
                                                       /*calcule de position*/ /**/
                
                if(x !=  i || y != j) printf(" WARNING !!y'a une errur de positionemment !!\n");
                if(colorplayer == rouge){ // le player1
                    y=y+d;
                    if(x != 5 ){
                        if(y>8) y=8;
                        if(x < 5){
                            x=x+d;
                            if(x>5) x=5;
                            while(  !UniteDeLaMemeCouleur(&jeuEncours[x][y]  , unite) ){
                                x--;
                                y--;
                            }
                        }else{ // le cas ou x > 5
                            x=x-d;
                            if(x<5) x=5;
                            while(  !UniteDeLaMemeCouleur(&jeuEncours[x][y]  , unite) ){
                                x++;
                                y--;
                            }

                        }
                    }else { // le cas ou x==5
                        if( y> 16 ) y=16 ;
                        while(  !UniteDeLaMemeCouleur(&jeuEncours[x][y]  , unite) ){
                            y--;
                        }
                    }
                }else{ // le player2
                    y=y-d;
                    if(x!= 5){
                        if(y <8 ) y=8;
                        if (x<5){
                            x=x+d;
                            if( x>5 ) x=5;
                            while(  !UniteDeLaMemeCouleur(&jeuEncours[x][y]  , unite) ){
                                x--;
                                y++;
                            }
                        }else{ // le cas ou x>5
                            x=x-d;
                            if (x < 5) x=5;
                            while(  !UniteDeLaMemeCouleur(&jeuEncours[x][y]  , unite) ){
                                x++;
                                y++;
                            }
                        }
                    }else{
                        if(y<2) y=2;
                        while(  !UniteDeLaMemeCouleur(&jeuEncours[x][y]  , unite) ){
                            y++;
                        }
                    }
                }
                                               /* fin calcule de position*/

                unite->posX=x;
                unite->posY=y;
                jeuEncours[x][y] = ajouterUnitedansZone(jeuEncours[x][y] , unite );
                list= list->suiv;

            }
        }
    }
};
//=========================================================
void updatelist( TListePlayer player){
    while(player!=NULL){
        player->pdata->peutAttaquer=1;
        player=player->suiv;
    }
}
//=========================================================
int positionX (){
    int nb , posx=0;
    nb=nombre_aleatoire(1,4);
    if(nb ==1 || nb==3){
        posx=nb;
    }else{
        if(nb==2){
            posx=7;
        }else{
            posx=9;
        }
    }
    return posx;
};

TListePlayer GetAllUniteInTplateuUPgrade (TplateauJeuUpgrade jeuEncours, int largeur,int hauteur){
    TListePlayer list=NULL,tmp=NULL;
    for(int i=0; i<largeur ;i++){
        for(int j=0;j<hauteur;j++){
            tmp=getAllUnitInZone(&jeuEncours[i][j]);
            if(tmp!=NULL){
                list=creatNewListeFromFusion(list,tmp);
            }
        }
    }

    return list;
};
//=========================================================
TListePlayer quiEstAPortee( Tunite*unite_attaque ,TplateauJeuUpgrade jeuEncours){
    TListePlayer list=NULL,tmp=NULL,l1=NULL;
    int x,y;
    x=unite_attaque->posX;
    y=unite_attaque->posY;
    int dist, dx,dy;
    Tunite *unite;
    int a,b,c,d;
    /**   **/
    /*ajouter toutes les unites de la Tzone correspondant  a celle qui va attaquer */
    tmp=getAllUnitInZone(&jeuEncours[x][y]);
    /**   **/
    /*ajouter toutes les unites présentes dans les Tzones autour de P à une distance de 4 */
    a=x-4;
    if(a<0) a=0;
    b=x+4;
    if(b>10) b=10;
    c=y-4;
    if(c<0) c=0;
    d=y+4;
    if(d>18) d=18;
    for(int i=a; i<=b ;i++){
        for(int j=c; j<=d;j++){
            dx=x-i;
            dy=y-j;
            dist=sqrt(dx*dx + dy*dy);
            if(dist<= 4 ){
                l1=getAllUnitInZone(&jeuEncours[i][j]);
                tmp=creatNewListeFromFusion(tmp,l1);
            }
        }
    }

    /**   **/
    while(tmp != NULL){
        unite=getPtrData(tmp);
        if( unite->peutAttaquer == 1){
            list=AjouterUnite(list,unite);
        }
        tmp=tmp->suiv;
    }
    /**   **/
    return list;
};
//=========================================================
void combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur){
    Tunite *unite_attaque=NULL;
    bool attack=false;
    while( player!= NULL && uneUniteDeLautreJoueur->pointsDeVie > 0){
        unite_attaque=getPtrData(player);
        if(unite_attaque->couleur != uneUniteDeLautreJoueur->couleur){
            printf("attack par (%d %d)\n",unite_attaque->posX, unite_attaque->posY);
            uneUniteDeLautreJoueur->pointsDeVie=uneUniteDeLautreJoueur->pointsDeVie - unite_attaque->degats; 
            unite_attaque->peutAttaquer=0;
            if(uneUniteDeLautreJoueur->peutAttaquer==1){
                printf("attack par (%d %d)\n",uneUniteDeLautreJoueur->posX, uneUniteDeLautreJoueur->posY);
                uneUniteDeLautreJoueur->peutAttaquer=0;
                unite_attaque->pointsDeVie=unite_attaque->pointsDeVie - uneUniteDeLautreJoueur->degats;
            }
        }
        
          

        player=player->suiv;
    }
};
void affiche (TListePlayer p){
    if(p==NULL){
        printf("la list est vide \n");
    }else{
        while(p!= NULL){
            printf("%d\n",p->pdata->pointsDeVie);
            p=p->suiv;

        }
    }

}

void affichezone (Tzone p){
    while(p!= NULL){
        printf("%d\n",p->elem->pointsDeVie);
        p=p->suiv;
    }
}

