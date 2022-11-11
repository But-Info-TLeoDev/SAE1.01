#include "gestionActivité.h"

/**
 * @brief Fonction globale qui gère le démarage du programme et la fin + toutes le fonctions et la gestion du menu
 * @author TUAILLON Léo
 * @date 2022-11-10
 * @return int retourne 0 (erreurs de compilation des fichiers)
 */
int main(void)
{
    int choixMain, choixAdh, choixAffich, choixActi, verifC, pos, cout, done, verifI;
    int tabClient[100], tabCredit[100], tabUtil[100], tabActif[100], tabInterdit[100], tPhysAd=100,tLog;
    int tabActivite[10],tabPrix[10],tabEntrees[10],tPhysAc=10, tLogAc;
    char tabStatut[100];
    tLog=chargementAdherent(tabClient, tabCredit, tabActif, tabInterdit, tabUtil, tabStatut, tPhysAd);
    tLogAc=chargementActivite(tabActivite,tabPrix,tabEntrees,tPhysAc);
    choixMain = choixMainMenu();
    while (choixMain!=9)
    {
        if (choixMain == 1)
            {
                choixAdh = choixMenuAdh();
                while (choixAdh!=9)
                {
                    if (choixAdh == 1)
                        creerAdherent(tabClient,tabCredit,tabActif,tabInterdit,tabUtil,tabStatut,&tLog,tPhysAd);

                    if (choixAdh == 2)
                        supprAdherent(tabClient,tabCredit,tabActif,tabInterdit,tabUtil, tabStatut, &tLog);

                    if (choixAdh == 3)
                        crediterPoints(tabClient,tabCredit,tabStatut,tLog);
                    
                    if (choixAdh == 4)
                        bloquerCarte( tabClient, tabActif ,tLog);

                    choixAdh = choixMenuAdh();
                }

            }

        if (choixMain == 2)
            {
                choixAffich = choixMenuAffich();
                while (choixAffich!=9)
                {
                    if (choixAffich == 1)
                        Affichage1Adherent(tabClient,tabCredit, tabActif, tabInterdit, tabUtil, tabStatut, tLog);

                    if (choixAffich == 2)
                        AffichageAllAdherents(tabClient,tabCredit, tabActif,tabInterdit,tabUtil, tabStatut,tLog);

                    if (choixAffich == 3)
                        AffichageActivite(tabActivite,tabPrix,tabEntrees,tLogAc);

                    choixAffich = choixMenuAffich();
                }
            }

        if (choixMain == 3)
            {
                verifC = verifClient(tabClient, tabActif, tLog, &pos);
                if (verifC == 0)
                    printf("Échec de vérification.");
                if (verifC == 1)
                {
                    printf("Vérification validée.");
                    choixActi = choixMenuActi(tabPrix);
                    while (choixActi!=9)
                    {
                        if (choixActi == 1)
                        {
                            cout = 10;
                            done = verifCredit(tabCredit, tabUtil, pos, cout);
                            if (done == 0)
                            {
                                printf(" Il ne vous reste que %d crédits hors cette activité coute %d",tabCredit[pos],cout);
                            }
                            if (done == 1)
                            {
                                printf("Inscription validée. Votre nouveau solde est de %d crédits",tabCredit[pos]);
                                tabEntrees[0]+=1;
                            }
                        }
                        if (choixActi == 2)
                        {
                            cout = 15;
                            done = verifCredit(tabCredit, tabUtil, pos, cout);
                            if (done == 0)
                            {
                                printf("Il ne vous reste que %d crédits hors cette activité coute %d",tabCredit[pos],cout);
                            }
                            if (done == 1)
                            {
                                printf("Inscription validée. Votre nouveau solde est de %d crédits",tabCredit[pos]);
                                tabEntrees[1]+=1;
                            }
                        }
                        if (choixActi == 3)
                        {
                            cout = 8;
                            done = verifCredit(tabCredit, tabUtil, pos, cout);
                            if (done == 0)
                            {
                                printf(" Il ne vous reste que %d crédits hors cette activité coute %d",tabCredit[pos],cout);
                            }
                            if (done == 1)
                            {
                                printf("Inscription validée. Votre nouveau solde est de %d crédits",tabCredit[pos]);
                                tabEntrees[2]+=1;
                            }
                        }
                        if (choixActi == 4)
                        {
                            cout = 30;
                            verifI=verifInterdit(tabInterdit,pos);
                            if (verifI== 0)
                            {
                                printf("\nErreur: Activité déjà effectué aujourd'hui");
                            }
                            if (verifI == 1)
                            {
                                done = verifCredit(tabCredit, tabUtil, pos, cout);
                                if (done == 0)
                                {
                                    printf("Il ne vous reste que %d crédits hors cette activité coute %d",tabCredit[pos],cout);
                                }
                                if (done == 1)
                                {
                                    printf("Inscription validée. Votre nouveau solde est de %d crédits",tabCredit[pos]);
                                    tabEntrees[3]+=1;
                                    tabInterdit[pos] = 1;
                                }
                            }   
                        }
                        choixActi = choixMenuActi(tabPrix);
                    }
                }
                
            }

        choixMain = choixMainMenu();

    }
    sauvegardeAdherents(tabClient,tabCredit,tabActif,tabInterdit, tabUtil,tabStatut, tLog);
    sauvegardeActivite(tabActivite,tabPrix,tabEntrees, tLogAc);
    return 0;
}
