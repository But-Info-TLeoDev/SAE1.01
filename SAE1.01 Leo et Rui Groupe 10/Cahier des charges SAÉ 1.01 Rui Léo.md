SAÉ 1.01 : Gestion des activités d'un camping
=============================================
- TUAILLON Léo
- MARTINS DA SILVA GOMES Rui

Dans le cadre de la SAÉ 1.01 "Implémentation d'un besoin client", nous avons conçu ce projet en langage C qui aura pour but de gérer les activités au sein d'un camping.

Il doit pouvoir:
---
- Afficher un menu ainsi que des sous-menus
- Récupérer le contenu de fichiers dans des tableaux pour traiter les informations client et celles des activités
- Mettre à jour / Sauvegarder les informations client et celles des activités dans les tableaux puis dans les fichiers
- Créer/supprimer un profil client
- Bloquer/Débloquer une carte client (en cas de perte ou de mauvais comportement)                                        
- Reconnaitre si un client existe
- Vérifier si ses informations lui permettent de participer à des activités ou non                                       
- Empêcher un client de participer à une activité s'il n'en a pas le droit ou s'il n'a pas assez de crédits
- Offrir un système de recharge de points contre de l'argent                                                             
- Offrir un système de "points bonus" calculés en fonction des points utilisés la veille                          
- Afficher les informations client et celles des activités
- Gérer les erreurs de saisie
- Gérer les autres erreurs (Profil non valide, Carte bloquée, Pas assez de crédits, Pas accès à une activité, etc...)

Activités proposées
===================

1. Tour de Karting (10 Crédits)
2. 1 Partie de Mini-Golf (15 Crédits)
3. 1H de Tennis (8 Crédits)
4. Entrée au parc aquatique (1fois/jour) (30 Crédits)

Répartition du travail
======================

**Léo :**
+ Chargement des fichiers dans les tableaux
+ Sauvegarde des tableaux dans les fichiers
+ Fonction de recherche dans les tableaux
+ Créer/Supprimer une carte
+ Bloquer/Débloquer une carte
+ Créditer points
+ Affichage clients/activités
+ Fonction Globale (main)
+ Doxygen fonctions de Léo

**Rui :**
+ Affichage du Menu et des sous-menus
+ Gestion des choix dans les différents menus
+ Structure qui enchaine les menus
+ Vérification profil client (ID et Carte bloquée ou non)
+ Vérification de crédits suffisants
+ Vérification d'interdiction de participation à une activité
+ Doxygen fonctions de Rui

>La mise en commun des deux travaux à été effectuée par nous deux mais essentiellement Léo.
Le cahier des charges à été effectué par nous deux mais essentiellement Rui.