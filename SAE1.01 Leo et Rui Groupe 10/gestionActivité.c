#include "gestionActivité.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * @brief Fonction de chargement du fichier activité.txt dans les tableaux
 * @author TUAILLON Léo
 * @date 2022-11-01
 * @param tabActivite tableau contenant les id des activités
 * @param tabPrix  tableau contenant des prix (en crédits) correspondant à l'activité
 * @param tabEntrees tableau contenant le nombre d'entrées au cours de la journée corespondant à l'activité
 * @param tPhys est la taille physique des tableaux tabActivite tabPrix et tabEntrees
 * @return int retourne -1 en cas d'erreur ou i qui correspond à la taille logique des tableaux après l'insertion
 */
int chargementActivite(int tabActivite[],int tabPrix[], int tabEntrees[], int tPhys)
{   
    int i=0, numAct, prix,nbEntrees;
    FILE *flot;
    flot = fopen("Activités.txt","r");
    if(flot==NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return -1;
    }
    fscanf(flot,"%d%d%d",&numAct,&prix,&nbEntrees);
    while (!feof(flot))
    {
        if (i==tPhys)
        {
            printf("tableau plein\n");
            return -1;
        }
        tabActivite[i]=numAct;
        tabPrix[i]=prix;
        tabEntrees[i]=0;
        i+=1;
        fscanf(flot,"%d%d%d",&numAct,&prix,&nbEntrees);
                
    }
    fclose(flot);
    return i;
}

void sauvegardeActivite(int tabActivite[],int tabPrix[], int tabEntrees[], int tLog)
{
    int i=0;
    FILE *flot;
    flot = fopen("Activités.txt","w");
    if(flot==NULL)
    {
        printf("problème d'ouverture du fichier");
        return;
    }
    for(i=0;i<tLog;i++)
    {   
        fprintf(flot,"%d\t%d\t%d\n",tabActivite[i],tabPrix[i],tabEntrees[i]);
    }
    fclose(flot);

}

void sauvegardeAdherents(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tLog)
{
    int i=0;
    FILE *flot;
    flot = fopen("Adhérents.txt","w");
    if(flot==NULL)
    {
        printf("problème d'ouverture du fichier");
        return;
    }
    for(i=0;i<tLog;i++)
    {   
        fprintf(flot,"%d\t%d\t%d\t%d\t%d\t%c\n",tabClient[i],tabCredit[i],tabActif[i],tabInterdit[i],tabUtil[i],tabStatut[i]);
    }
    fclose(flot);

}


/**
 * @brief Fonction de chargement du fichier activité.txt dans les tableaux
 * @author TUAILLON Léo
 * @date 2022-11-01
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabCredit tableau contenant le nombre de crédits des clients
 * @param tabActif tableau contenant 0 ou 1 pour chaque client (1 correspond à une carte active et 0 si elle est bloquée)
 * @param tabInterdit tableau contenant pour chaque client 0 ou 1 (1 si le client est interdit de parc aquatique 0 sinon)
 * @param tabStatut tableau statut contenant une lettre (type char) correspondant au statut des clients (e pour enfant, j pour jeune et a pour adulte)
 * @param tabUtil tableau contenant le nombre de crédit utilisés durant la journée d'un adhérent   
 * @param tPhys est la taille physique des tableaux entrés en paramètres de la fonction
 * @return int retourne -1 en cas d'erreur ou i qui correspond à la taille logique des tableaux après l'insertion
 */
int chargementAdherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tPhys)
{   
    int i=0, idClient,crédit,carteOFF,parc,util;
    char statut;
    FILE *flot;
    flot = fopen("Adhérents.txt","r");
    if(flot==NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return -1;
    }
    fscanf(flot,"%d %d %d %d %d%*c %c%*c",&idClient,&crédit,&carteOFF,&parc,&util,&statut);
    while (!feof(flot))
    {   
        if (i==tPhys)
        {
            printf("tableau plein\n");
            return -1;
        }
        tabClient[i]=idClient;
        if(util>=10)
        {
            crédit=crédit+util*0.1;
        }
        tabCredit[i]=crédit;
        tabActif[i]=carteOFF;
        tabInterdit[i]=0;
        tabUtil[i]=0;
        tabStatut[i]=statut;
        i+=1;
        fscanf(flot,"%d %d %d %d %d%*c %c%*c",&idClient,&crédit,&carteOFF,&parc,&util,&statut);
                
    }
    fclose(flot);
    return i;
}

/**
 * @brief Fonction de recherche du numero de carte (id) d'un client dans le tableau tabClient
 * @author TUAILLON Léo
 * @date 2022-11-01
 * @param tabClient tableau contenant les numero de carte des clients  
 * @param tLog correspond à la taille logique des tableaux
 * @param idClient correspond à l'id (numero de carte) recherché
 * @param trouvee pointeur permettant de renvoyer par addresse si oui ou non l'id a été trouvé dans le tableau    
 * @return int qui retourne la position de l'id si celui-ci est trouvée ou la position ou il faudrait l'insérer sinon
 */
int recherche(int tabClient[], int tLog, int idClient, int *trouvee)

{
    int i;
    for(i=0; i<tLog; i++)
    {
        if(tabClient[i] == idClient)
        {
            *trouvee=1;
            return i;
        }
        if(tabClient[i]>idClient)
        {
            *trouvee=0;
            return i;
        }
    }
    *trouvee=0;
    return i;
}

/**
 * @brief Fonction d'affichage de la liste de tous les adhérents
 * @author TUAILLON Léo
 * @date 2022-11-01
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabCredit tableau contenant le nombre de crédits des clients
 * @param tabActif tableau contenant 0 ou 1 pour chaque client (1 correspond à une carte active et 0 si elle est bloquée)
 * @param tabInterdit tableau contenant pour chaque client 0 ou 1 (1 si le client est interdit de parc aquatique 0 sinon)
 * @param tabUtil tableau contenant le nombre de crédit utilisés durant la journée d'un adhérent 
 * @param tabStatut tableau statut contenant une lettre (type char) correspondant au statut des clients (e pour enfant, j pour jeune et a pour adulte)
 * @param tLog correspond à la taille logique des tableaux
 */
void AffichageAllAdherents(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tLog)
{
    int i;
    printf("\nNum Carte\tCrédits\t\tcarte active\tParc Interdit\tCrédits Utilisés\tStatut\n");
    for(i=0; i<tLog; i++) 
    {
        printf("%d\t\t%d\t\t",tabClient[i],tabCredit[i]);
        if(tabActif[i]==1)
            printf("oui\t\t");
        else printf("non\t\t");
        if(tabInterdit[i]==1)
            printf("oui\t\t");
        else printf("non\t\t");
        printf("%d\t\t\t",tabUtil[i]);
        if(tabStatut[i]=='e')
            printf("enfant\n");
        else if(tabStatut[i]=='j')
            printf("jeune\n");
        else
            printf("adulte\n");
    }
}

/**
 * @brief Fonction d'affichage des informations d'un adhérent
 * @author TUAILLON Léo
 * @date 2022-11-01
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabCredit tableau contenant le nombre de crédits des clients
 * @param tabActif tableau contenant 0 ou 1 pour chaque client (1 correspond à une carte active et 0 si elle est bloquée)
 * @param tabInterdit tableau contenant pour chaque client 0 ou 1 (1 si le client est interdit de parc aquatique 0 sinon)
 * @param tabUtil tableau contenant le nombre de crédit utilisés durant la journée d'un adhérent 
 * @param tabStatut tableau statut contenant une lettre (type char) correspondant au statut des clients (e pour enfant, j pour jeune et a pour adulte)
 * @param tLog correspond à la taille logique des tableaux
 */
void Affichage1Adherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int tLog)
{
    int pos, idClient, trouvee;
    printf("Quel est le numéro de carte du client ? : ");
    scanf("%d",&idClient);
    pos=recherche(tabClient, tLog, idClient, &trouvee);
    if(&trouvee==0)
    {
        printf("Erreur, ce numéro de carte ne correspond à aucun client");
        return;
    }
    printf("\n\tInformations du Client %d: \n",idClient);
    printf("Crédits Restant :\t%d\n",tabCredit[pos]);
    printf("Carte active :\t\t");
    if(tabActif[pos]==1)
            printf("oui\n");
    printf("Entrée parc aquatique :\t");
    if(tabInterdit[pos]==1)
            printf("déjà utilisé aujoud'hui\n");
    else printf("disponible\n");
    printf("Statut :\t\t");
    if(tabStatut[pos]=='e')
        printf("enfant\n");
    else if(tabStatut[pos]=='j')
        printf("jeune\n");
    else
        printf("adulte\n");
    return;
}

/**
 * @brief Fonction d'affichage des informations des informations de toutes les activités
 * @author TUAILLON Léo
 * @date 2022-11-01
 * @param tabActivite tableau contenant les id des activités
 * @param tabPrix  tableau contenant des prix (en crédits) correspondant à l'activité
 * @param tabEntrees tableau contenant le nombre d'entrées au cours de la journée corespondant à l'activité
 * @param tLog  taille logique des tableaux tabActivite tabPrix et tabEntrees
 */
void AffichageActivite(int tabActivite[],int tabPrix[], int tabEntrees[], int tLog)
{
    int i;
    printf("\nNuméro d'activité\tActivite Corespondante\tPrix\tNombre d'entrées\n");
    for(i=0; i<tLog; i++) 
    {
        printf("%d\t\t\t",tabActivite[i]);
        switch (tabActivite[i])
        {
        case 1:
            printf("karting\t\t\t");
            break;
        case 2:
            printf("Mini-golf\t\t");
            break;
        case 3:
            printf("Tennis\t\t\t");
            break;
        case 4:
            printf("Parc Aquatique\t\t");
            break;
        
        default:
            break;
        }        
        printf("%d\t%d\n",tabPrix[i],tabEntrees[i]);
    }
    printf("\n");
}

/**
 * @brief Fonction permettant de créditer des points sur la carte d'un client
 * @author TUAILLON Léo
 * @date 2022-11-05
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabCredit tableau contenant le nombre de crédits des clients
 * @param tabStatut tableau statut contenant une lettre (type char) correspondant au statut des clients (e pour enfant, j pour jeune et a pour adulte)
 * @param tLog correspond à la taille logique des tableaux
 */
void crediterPoints(int tabClient[], int tabCredits[],char tabStatut[] ,int tLog)
{
    int idClient, pos, t, credit;
    float prix, coef;
    printf("Quel est le numéro de la carte sur laquelle vous désirez créditer des points ? : ");
    scanf("%d",&idClient);
    pos=recherche(tabClient,tLog,idClient,&t);
    if(t==0)
    {
        printf("idClient non trouvé.\n");
        return;
    }
    else
    {   
        printf("NOS OFFRES :\n");
        printf("entre 5 et 20 crédits achetés : 1 crédit = 1€\n");
        printf("entre 21 et 50 crédits achetés : 1 crédit = 0.90€\n");
        printf("entre 51 et 100 crédits achetés : 1 crédit = 0.75€\n");
        printf("entre 101 et 300 crédits achetés : 1 crédit = 0.60€\n");
        printf("\t REDUCTION STATUT :\n");
        printf("Tarif enfant : -50 pourcent sur la commande\n");
        printf("Tarif jeune : -30 pourcent sur la commande\n");
        printf("Tarif adulte : pas de reductions\n");
        printf("Il vous reste %d crédits, saisissez le nombre de crédits que vous voulez ajouter : ", tabCredits[pos]);
        scanf("%d",&credit);
        while (credit<5 || credit>300)
        {
            printf("erreur de saisie : vous devez saisir un nombre de crédit entre 5 et 300 : \n");
            scanf("%d",&credit);
        }
        if(tabStatut[pos]=='e')
            coef=0.5;
        if(tabStatut[pos]=='j')
            coef=0.7;
        if(credit>0 && credit<21)
        {
            tabCredits[pos]+=credit;
            prix=credit*coef;
            printf("vous avez crédité %d crédits pour le prix de %.2f€",credit,prix);
        } 
        if(credit>20 && credit<51)
        {
            tabCredits[pos]+=credit;
            prix=credit*0.9*coef;
            printf("vous avez crédité %d crédits pour le prix de %.2f€",credit,prix);
        }
        if(credit>50 && credit<101)
        {
            tabCredits[pos]+=credit;
            prix=credit*0.75*coef;
            printf("vous avez crédité %d crédits pour le prix de %.2f€",credit,prix);
        }
        if(credit>100 && credit<=300)
        {
            tabCredits[pos]+=credit;
            prix=credit*0.6*coef;
            printf("vous avez crédité %d crédits pour le prix de %.2f€",credit,prix);
        } 
    } 
}

/**
 * @brief Fonction qui permet de bloqur / débloquer la carte d'un adhérent
 * @author TUAILLON Léo
 * @date 2022-11-05
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabActif tableau contenant 0 ou 1 pour chaque client (1 correspond à une carte active et 0 si elle est bloquée)
 * @param tLog correspond à la taille logique des tableaux
 */
void bloquerCarte(int tabClient[], int tabActif[] ,int tLog)
{
    int idClient, pos, t;
    char choix;
    float prix, coef;
    printf("Quel est le numéro de la carte que vous voulez bloquer ou debloquer : ");
    scanf("%d%*c",&idClient);
    pos=recherche(tabClient,tLog,idClient,&t);
    if(t==0)
    {
        printf("idClient non trouvé.\n");
        return;
    }
    else
    {   
        if(tabActif[pos]==0)
        {
            printf("Votre carte est actuellement bloquée, voulez vous la débloquer ? (o/n) : ");
            scanf("%c%*c",&choix);
            while (!(choix=='o' || choix=='n'))
            {
                printf("erreur de saisie : 'o' pour oui ou 'n' pour non : ");
                scanf("%c%*c",&choix);
            }
            if(choix=='o')
            {
                tabActif[pos]=1;
                printf("carte débloquée avec succès");
                return;
            }
            else printf("comme vous l'avez demandé, votre carte est toujours bloquée");
        }
        if(tabActif[pos]==1)
        {
            printf("Votre carte est actuellement active, voulez vous la bloquer ? (o/n) : ");
            scanf("%c%*c",&choix);
            while (!(choix!='o' || choix!='n'))
            {
                printf("erreur de saisie : 'o' pour oui ou 'n' pour non : ");
                scanf("%c%*c",&choix);
            }
            if(choix=='o')
            {
                tabActif[pos]=0;
                printf("carte bloquée avec succès");
                return;
            }
            else printf("comme vous l'avez demandé, votre carte est toujours active");
        }

    } 
} 

/**
 * @brief Fonction qui permet de créer et insérer un nouvel adhérent dans les tableaux
 * @author TUAILLON Léo
 * @date 2022-11-05
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabCredit tableau contenant le nombre de crédits des clients
 * @param tabActif tableau contenant 0 ou 1 pour chaque client (1 correspond à une carte active et 0 si elle est bloquée)
 * @param tabInterdit tableau contenant pour chaque client 0 ou 1 (1 si le client est interdit de parc aquatique 0 sinon)
 * @param tabUtil tableau contenant le nombre de crédit utilisés durant la journée d'un adhérent 
 * @param tabStatut tableau statut contenant une lettre (type char) correspondant au statut des clients (e pour enfant, j pour jeune et a pour adulte)
 * @param tLog pointeur qui correspond à la taille logique des tableaux et qui renvoie par adresse à la fin de la fonction la nouvelle taille logique
 * @param tPhys taille physique des tableaux 
 */
void creerAdherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int *tLog, int tPhys)
{
    int idClient, age,pos,t,j;
    char statut='a';
    if(*tLog==tPhys)
    {
        printf("erreur : tableaux pleins");
        return;
    } 
    printf("Saisissez l'id du client ? (entre 1 et 99) : ");
    scanf("%d",&idClient);
    while (idClient<1&&idClient>99)
    {
        printf("erreur l'id n'est pas valide, veuillez saisir l'id du client ? (entre 1 et 99) :");
        scanf("%d",&idClient);
    }
    pos=recherche(tabClient,*tLog,idClient,&t);
    if(t==1)
    {
        printf("Erreur : un client avec cet id est déjà existant");
        return;
    } 
    printf("Saisissez l'âge du client : ");
    scanf("%d",&age);
    while (age<0 && age>130)
    {
        printf("erreur : Veuillez saisir un âge valide");
        scanf("%d",&age);
    }
    if (age<12)
        statut='e';
    if (age>=12 && age<18)
        statut='j';
    for(j=*tLog-1;j>=pos;j--)
    {
        tabClient[j+1]=tabClient[j];
        tabCredit[j+1]=tabCredit[j];
        tabActif[j+1]=tabActif[j];
        tabInterdit[j+1]=tabInterdit[j];
        tabUtil[j+1]=tabUtil[j];
        tabStatut[j+1]=tabStatut[j];
    }
    tabClient[pos]=idClient;
    tabCredit[pos]=0;
    tabActif[pos]=1;
    tabInterdit[pos]=0;
    tabUtil[pos]=0;
    tabStatut[pos]=statut;
    *tLog=*tLog+1;
    printf("carte créer avec succès\n");
}

/**
 * @brief Fonction permettant de supprimer les données d'un adhérents
 * @author TUAILLON Léo
 * @date 2022-11-05
 * @param tabClient tableau contenant les numero de carte des clients
 * @param tabCredit tableau contenant le nombre de crédits des clients
 * @param tabActif tableau contenant 0 ou 1 pour chaque client (1 correspond à une carte active et 0 si elle est bloquée)
 * @param tabInterdit tableau contenant pour chaque client 0 ou 1 (1 si le client est interdit de parc aquatique 0 sinon)
 * @param tabUtil tableau contenant le nombre de crédit utilisés durant la journée d'un adhérent 
 * @param tabStatut tableau statut contenant une lettre (type char) correspondant au statut des clients (e pour enfant, j pour jeune et a pour adulte)
 * @param tLog pointeur qui correspond à la taille logique des tableaux et qui renvoie par adresse à la fin de la fonction la nouvelle taille logique
 */
void supprAdherent(int tabClient[],int tabCredit[], int tabActif[], int tabInterdit[], int tabUtil[], char tabStatut[], int *tLog)
{
    int idClient, idClientVerif,pos,t,j;
    printf("Saisissez l'id du client que voulez supprimer : ");
    scanf("%d",&idClient);
    while (idClient<1&&idClient>99)
    {
        printf("erreur l'id n'est pas valide, veuillez saisir l'id du client ? (entre 1 et 99) : ");
        scanf("%d",&idClient);
    }
     
    pos=recherche(tabClient,*tLog,idClient,&t);
    if(t==0)
    {
        printf("Erreur : aucun client ne correspond à l'id saisie\n");
        return;
    } 
    printf("Etes vous sûr de vouloir supprimer la carte du client %d (pas de retour en arrière possible), si vous êtes sûr veuillez saisir l'id du client une seconde fois : ",idClient);
    scanf("%d",&idClientVerif);
    if(idClient!=idClientVerif)
    {
        printf("Les deux id que vous avez saisi ne correspondent pas, suppression annulée");
        return;
    }
    else{
        for(j=pos;j<*tLog;j++)
        {
            tabClient[j]=tabClient[j+1];
            tabCredit[j]=tabCredit[j+1];
            tabActif[j]=tabActif[j+1];
            tabInterdit[j]=tabInterdit[j+1];
            tabUtil[j]=tabUtil[j+1];
            tabStatut[j]=tabStatut[j+1];
        }
        printf("supression effectuée\n");
        *tLog=*tLog-1;
    } 
    
}


/**
 * @brief Fonction affichant le menu principal
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 */
void afficheMainMenu()
{
    printf("\n\n+-------------------------------------------------+\n");
    printf("|\t Menu: \t\t\t\t\t  |\n|\t\t\t\t\t\t  |\n");
    printf("|1 \t Cartes Adhérents\t\t\t  |\n");
    printf("|2 \t Affichages\t\t\t\t  |\n");
    printf("|3 \t Activités\t\t\t\t  |\n");
    printf("|9 \t Quitter \t\t\t\t  |\n");
    printf("+-------------------------------------------------+\n\n");
}

/**
 * @brief Fonction de saisie du choix fait dans le menu principal
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @return int retourne la valeur du choix
 */
int choixMainMenu()
{
    int choice;
    afficheMainMenu();
    printf("Veuillez saisir un chiffre : ");
    scanf("%d", &choice);
    while ((choice < 1 || choice > 3) && choice != 9)
        {
            afficheMainMenu();
            printf("Erreur de saisie: Veuillez saisir un chiffre parmis le choix proposés : ");
            scanf("%d", &choice);
        }
    return choice;   
}

/**
 * @brief Fonction affichant le menu des options possibles pour les cartes adhérent
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 */
void afficheMenuAdh()
{
    printf("\n\n+-------------------------------------------------+\n");
    printf("|\t Cartes Adhérents: \t\t\t  |\n|\t\t\t\t\t\t  |\n");
    printf("|1 \t Créer une carte\t\t\t  |\n");
    printf("|2 \t Supprimer une carte\t\t\t  |\n");
    printf("|3 \t Créditer des points\t\t\t  |\n");
    printf("|4\t Blocker/Déblocker une carte\t\t  |\n");
    printf("|9 \t Retour \t\t\t\t  |\n");
    printf("+-------------------------------------------------+\n\n");
}

/**
 * @brief Fonction de saisie du choix fait dans le menu cartes adhérent
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @return int retourne la valeur du choix
 */
int choixMenuAdh()
{
    int choice;
    afficheMenuAdh();
    printf("Veuillez saisir un chiffre : ");
    scanf("%d", &choice);
    while ((choice < 1 || choice > 4) && choice != 9)
        {
            afficheMenuAdh();
            printf("Erreur de saisie: Veuillez saisir un chiffre parmis le choix proposés : ");
            scanf("%d", &choice);
        }
    return choice;   
}

/**
 * @brief Fonction affichant le menu de choix d'affichages
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 */
void afficheMenuAffich()
{
    printf("\n\n+-------------------------------------------------+\n");
    printf("|\t Affichages: \t\t\t\t  |\n|\t\t\t\t\t\t  |\n");
    printf("|1 \t Afficher un adhérent\t\t\t  |\n");
    printf("|2 \t Afficher la liste de tous les Adhdérents |\n");
    printf("|3 \t Afficher les entrées des activités\t  |\n");
    printf("|9 \t Retour \t\t\t\t  |\n");
    printf("+-------------------------------------------------+\n\n");
}

/**
 * @brief Fonction de saisie du choix fait dans le menu affichages
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @return int retourne la valeur du choix
 */
int choixMenuAffich()
{
    int choice;
    afficheMenuAffich();
    printf("Veuillez saisir un chiffre : ");
    scanf("%d", &choice);
    while ((choice < 1 || choice > 3) && choice != 9)
        {
            afficheMenuAffich();
            printf("Erreur de saisie: Veuillez saisir un chiffre parmis le choix proposés : ");
            scanf("%d", &choice);
        }
    return choice;   
}

/**
 * @brief Fonction affichant le menu des différentes activités proposées
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 */
void afficheMenuActi(int tabPrix[])
{
    printf("\n\n+----------------------------------------------------+\n");
    printf("|\tActivités: \t\t\t\t     |\n");
    printf("|\tA quelles activités voulez-vous partciper ?  |\n| \t\t\t\t\t\t     |\n");
    printf("|1  \tTour de Karting (%d crédits) \t\t     |\n",tabPrix[0]);
    printf("|2  \tPartie Mini-Golf (%d crédits) \t\t     |\n",tabPrix[1]);
    printf("|3  \t1H de Tennis (%d crédits) \t\t     |\n",tabPrix[2]);
    printf("|4  \tParc Aquatique (%d crédits) (1 fois/jour)    |\n",tabPrix[3]);
    printf("|9 \tRetour \t\t\t\t\t     |\n");
    printf("+----------------------------------------------------+\n");

}

/**
 * @brief Fonction de saisie du choix fait dans le menu de sélection des activités
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @return int retourne la valeur du choix
 */
int choixMenuActi(int tabPrix[])
{
    int choice;
    afficheMenuActi(tabPrix);
    printf("Veuillez saisir un chiffre : ");
    scanf("%d", &choice);
    while ((choice < 1 || choice > 4) && choice != 9)
        {
            afficheMenuActi(tabPrix);
            printf("Erreur de saisie: Veuillez saisir un chiffre parmis le choix proposés : ");
            scanf("%d", &choice);
        }
    return choice;   
}

/**
 * @brief Fonction pour vérifier la validité de l'ID Client et si la carte est bloquée ou pas
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @param tabClient tableau contenant les ID CLient
 * @param tabActif  tableau contenant des valeurs booléennes pour savoir si une carte est bloquée ou non
 * @param tLog taille logique des tableaux
 * @param pos stocke l'indice de position des informations d'un client donné dans tous les tableaux
 * @return int retourne 1 pour vérification validée ou 0 pour une erreur dans la vérification du profil Client
 */
int verifClient(int tabClient[], int tabActif[], int tLog, int *pos)
{
    int idClient, actif, trouvee;
    printf("Saisir ID Client : ");
    scanf("%d", &idClient);
    *pos = recherche(tabClient, tLog, idClient, &trouvee);
    if (trouvee == 0)
    {
        printf("Erreur: ID Client inexistant.\n");
        return 0;
    }
    if (trouvee == 1)
    {
        printf("ID Client vérifié avec succès.\n");

        actif = tabActif[*pos];
        if (actif == 0)
        {
            printf("Erreur: Carte Bloquée.\n");
            return 0;
        }
        if (actif == 1)
        {
            printf("Carte vérifiée avec succès.\n");
            return 1;
        }
    }
}

/**
 * @brief Fonction pour vérifier si crédits suffisants, si oui retire la valeur dans tabCredit et ajoute la valeur dans tabUtil
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @param tabCredit tableau contenant les crédits de chaque client
 * @param tabUtil tableau contenant les crédits utilisés de chaque client
 * @param pos stocke l'indice de position des informations d'un client donné dans tous les tableaux
 * @param cout est le prix associé à chaque activité
 * @return int retourne 0 si les crédits sont insuffisants 1 si tout s'est bien passé
 */
int verifCredit(int tabCredit[], int tabUtil[], int pos, int cout)
{
    int credit;
    credit = tabCredit[pos];
    if (credit-cout < 0)
    {
        printf("Crédits Insuffisants. ");
        return 0;
    }
    if (credit-cout >= 0)
    {
        credit = credit - cout;
        tabCredit[pos] = credit;
        tabUtil[pos] = tabUtil[pos] + cout;
        return 1;
    }
}

/**
 * @brief Fonction pour vérifier si la personne a déjà effectué l'activité aujourd'hui
 * @author MARTINS DA SILVA GOMES Rui
 * @date 2022-11-10
 * @param tabInterdit tableau contenant des valeurs booléennes pour savoir si oui ou non une personne est interdite de faire l'activité
 * @param pos stocke l'indice de position des informations d'un client donné dans tous les tableaux
 * @return int retourne 0 si la personne est interdite de faire l'activité ou 1 si elle a le droit
 */
int verifInterdit(int tabInterdit[], int pos)
{
    if (tabInterdit[pos] == 1)
    {
        printf("Limite atteinte pour aujourd'hui.");
        return 0;
    }
    if (tabInterdit[pos] == 0)
        return 1;
}
