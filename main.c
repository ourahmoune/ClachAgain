//NOM prénom étudiant 1 : OURAHMOUNE NADIR 	
//NOM prénom étudiant 2 : ROKHAYA DARY

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonction d'affichage pour le jeu 2048
#include "clashagain.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{

    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
    SDL_Surface* pSpriteTour = SDL_LoadBMP("./data/Tour.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 1
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 2
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 3
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 4
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 5
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 6  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 7 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 8 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 9 idem

    // ASTUCE : on stocke le sprite d'une unité à l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unité (NULL dans le plateau) et en foction de certains indices x,y définissant le chemin central
    SDL_Surface* TabSprite[10]={pSpriteTour,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};


    if ( pSpriteTour )  //si le permier sprite a bien été chargé, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        ///********************* NOUVEAUTE ***************************
        TplateauJeuUpgrade jeuUpgrade = AlloueTab2D_Tzone(LARGEURJEU,HAUTEURJEU);  //code fourni
        initPlateauUpAvecNULL( jeuUpgrade, LARGEURJEU,  HAUTEURJEU);
        srand(time(NULL));
        TPlayer player1 = initPlayer(rouge);
        TPlayer player2 = initPlayer(bleu);
        ///********************* fin NOUVEAUTE ***************************

        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^

        message("Welcome in ClashAgain","Ceci est un point de depart de votre future interface de votre jeu ClashAgain");
        message("et fin","ECHAP->quitter, A,D,C et G pour les achats d'unités (si version humain vs ordi)");

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
        /*              remarque : player1, player2 et jeuU_pgrade  sont definis lignes 52-55*/
        FILE *fic;
        Tunite *unite_cible=NULL,*unite_tmp=NULL , *new_unit=NULL, *x,*y,*z,*t;
        TListePlayer list_cible=NULL,tmp=NULL , list_attaque=NULL ,listeUoutesUniteAuMemeCombat=NULL;
        bool suprime;

        unite_tmp=creeTour(5,3);
        unite_tmp->couleur=player1.couleurJoueur;
        player1.listeU =AjouterUnite(player1.listeU ,unite_tmp);
        unite_tmp=creeTourRoi(5,1);
        unite_tmp->couleur=player1.couleurJoueur;
        player1.listeU =AjouterUnite(player1.listeU,unite_tmp);


        unite_tmp=creeTour(5,15);
        unite_tmp->couleur=player2.couleurJoueur;
        player2.listeU =AjouterUnite(player2.listeU,unite_tmp);
        unite_tmp=creeTourRoi(5,17);
        unite_tmp->couleur=player2.couleurJoueur;
        player2.listeU =AjouterUnite(player2.listeU ,unite_tmp);





        printf("elxir de player 1 %d\n",player1.elixir);
        printf("elxir de player 2 %d\n",player2.elixir);


        // FIN de vos variables
        /**********************************************************************/

        // boucle principale du jeu
        /**********************************************************************/



        /**********************************************************************/
        int cont = 1;
        int i=0;
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events


                /****************************** Nouveautés *****************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                //
                /*  Vous manipulez ici:

                //
                //  player1, player2 et jeuUpgrade

                /*                                                                     */
                /*                                                                     */
                updatelist(player1.listeU);
                updatelist(player2.listeU);
                // FIN DE VOS APPELS
                /******************************* fin nouveautés****************************************/
                ///********************* NOUVEAUTE ***************************
                /**/
                initPlateauUpAvecNULL( jeuUpgrade, LARGEURJEU,  HAUTEURJEU);
                PositionnePlayerOnPlateau_Upgade( player1.listeU, jeuUpgrade);
                PositionnePlayerOnPlateau_Upgade( player2.listeU, jeuUpgrade);
                deplacement(jeuUpgrade ,LARGEURJEU , HAUTEURJEU );
                ConversionEnTplateauJeu(jeu ,jeuUpgrade,LARGEURJEU,HAUTEURJEU);
                /**/
                ///********************* fin NOUVEAUTE ***************************
                /*        la creation des unités et les ajoutes dans les listes des players      */
                /**/
                srand(time(NULL));
                if(player1.elixir>0){
                        new_unit=AcheteUnite(&player1);
                        if(new_unit != NULL){
                                new_unit->couleur = player1.couleurJoueur;
                                new_unit->posY=3;
                                new_unit->posX=positionX();
                                player1.listeU =AjouterUnite(player1.listeU ,new_unit);

                        }
                }
                if(player2.elixir>0){
                        new_unit=AcheteUnite(&player2);
                        if(new_unit != NULL){
                                new_unit->couleur = player2.couleurJoueur;
                                new_unit->posY=15;
                                new_unit->posX=positionX();
                                player2.listeU =AjouterUnite(player2.listeU ,new_unit);

                        }
                }
                /**/
                /*                        Fin de la creation des unités                       */


                /*                               phase de combat                              */ /**/



                tmp=player2.listeU;
                listeUoutesUniteAuMemeCombat=quiEstAPortee(tmp->pdata ,jeuUpgrade );
                while(listeUoutesUniteAuMemeCombat != NULL){
                        tri_selection_liste(listeUoutesUniteAuMemeCombat ,comp_PointDeVieAsupB);
                        unite_cible=listeUoutesUniteAuMemeCombat->pdata;
                        list_attaque=NULL;
                        tmp=listeUoutesUniteAuMemeCombat;
                        while(tmp != NULL){
                                list_attaque=AjouterUnite(list_attaque, tmp->pdata);
                                tmp=tmp->suiv;
                        }
                        tri_selection_liste(list_attaque ,comp_vitteseAsupB);
                        combat( list_attaque , unite_cible);
                        suprime=0;
                        //vider la liste list_attaque est supperimer les unites mortes dans la list  listeUoutesUniteAuMemeCombat
                        while(list_attaque !=NULL){
                                unite_tmp=list_attaque->pdata;
                                list_attaque=supprimerUnite(list_attaque,unite_tmp);
                                if(unite_tmp->pointsDeVie<=0){
                                         suprime=1;
                                        listeUoutesUniteAuMemeCombat=supprimerUnite(listeUoutesUniteAuMemeCombat , unite_tmp);

                                }
                        }
                        //*********************************************************************************************************

                        if(suprime==0){
                                listeUoutesUniteAuMemeCombat=listeUoutesUniteAuMemeCombat->suiv;
                        }
                }
                if (tourRoiDetruite(player2.listeU)) break ;
                if (tourRoiDetruite(player1.listeU)) break ;

                player2.listeU=CleanList(player2.listeU);
                player1.listeU=CleanList(player1.listeU);
                          

                          /*********************************************//**/
                tmp=player1.listeU;
                listeUoutesUniteAuMemeCombat=quiEstAPortee(tmp->pdata ,jeuUpgrade );
                while(listeUoutesUniteAuMemeCombat != NULL){
                        tri_selection_liste(listeUoutesUniteAuMemeCombat ,comp_PointDeVieAsupB);
                        unite_cible=listeUoutesUniteAuMemeCombat->pdata;
                        list_attaque=NULL;
                        tmp=listeUoutesUniteAuMemeCombat;
                        while(tmp != NULL){
                                list_attaque=AjouterUnite(list_attaque, tmp->pdata);
                                tmp=tmp->suiv;
                        }
                        tri_selection_liste(list_attaque ,comp_vitteseAsupB);
                        combat( list_attaque , unite_cible);
                        suprime=0;
                        //vider la liste list_attaque est supperimer les unites mortes dans la list  listeUoutesUniteAuMemeCombat
                        while(list_attaque !=NULL){
                                unite_tmp=list_attaque->pdata;
                                list_attaque=supprimerUnite(list_attaque,unite_tmp);
                                if(unite_tmp->pointsDeVie<=0){
                                         suprime=1;
                                        listeUoutesUniteAuMemeCombat=supprimerUnite(listeUoutesUniteAuMemeCombat , unite_tmp);

                                }
                        }
                        //*********************************************************************************************************

                        if(suprime==0){
                                listeUoutesUniteAuMemeCombat=listeUoutesUniteAuMemeCombat->suiv;
                        }
                }
                if (tourRoiDetruite(player2.listeU)) break ;
                if (tourRoiDetruite(player1.listeU)) break ;

                player2.listeU=CleanList(player2.listeU);
                player1.listeU=CleanList(player1.listeU);


                /**/


                /*                         END phase de combat                              */

                //affichage du jeu à chaque tour
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(150);  //valeur du délai à modifier éventuellement

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_G] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */
                        sauvgardeSEQ(fic,player1 , player2 );

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'une Gargouille");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */
                        player1.listeU=NULL;
                        player2.listeU=NULL;
                        restaurSEQ(fic ,&player1 ,&player2);
                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'un Chevalier");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'un Dragon?");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_Q] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appyue sur S */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'un Archer");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTour); // Libération de la ressource occupée par le sprite
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
