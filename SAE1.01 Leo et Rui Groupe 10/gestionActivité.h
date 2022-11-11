#include <stdio.h>
int chargementAdherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tPhys);

int chargementActivite(int tabActivite[],int tabPrix[], int tabEntrees[], int tPhys);

void sauvegardeActivite(int tabActivite[],int tabPrix[], int tabEntrees[], int tLog);

void sauvegardeAdherents(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tLog);

void supprAdherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int *tLog);

void crediterPoints(int tabClient[], int tabCredits[],char tabStatut[] ,int tLog);

void Affichage1Adherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tLog);

void AffichageAllAdherents(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tLog);

void AffichageActivite(int tabActivite[],int tabPrix[], int tabEntrees[], int tLog);

int recherche(int tabClient[], int tLog, int idClient, int *trouvee);

void bloquerCarte(int tabClient[], int tabActif[] ,int tLog);

void creerAdherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int *tLog, int tPhys);

void afficheMainMenu();

void afficheMenuAdh();

void afficheMenuAffich();

void afficheMenuActi(int tabPrix[]);

int choixMainMenu(void);

int choixMenuAdh(void);

int choixMenuAffich(void);

int choixMenuActi(int tabPrix[]);

int verifClient(int tabClient[], int tabActif[], int tLog, int *pos);

int verifCredit(int tabCredit[], int tabUtil[], int pos, int cout);

int verifInterdit(int tabInterdit[], int pos);