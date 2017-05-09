# Robot Rosetta
Projet Master 2 Informatique
Jérémie Décome
## Logiciel de contrôle du robot

Ce logiciel permet le contrôle d'un robot via une application Android (Dépôt : https://github.com/teranmoc/rosettaAndroidApplication ). 

La communication entre le robot et l'application mobile est réalisé par les sockets C++. 
Le logiciel embarqué utilise 3 threads pour fonctionner :
 * Un pour le programme principal et l'exécution des commandes
 * Un pour la lecture du socket et récupérer l'ordre envoyé
 * Un pour la gestion des capteurs ultra sons

### Prérequis
Ces sources doivent être compilées sur une plateforme **Raspberry Pi** avec la librairie [wiringPi](http://wiringpi.com/) et avec Python.

### Installation
Après avoir cloner le dépôt, utiliser le **makefile** pour compiler les sources :
> $ make

### Lancement
Le logiciel embarqué peut être démarré par la console :
> $ ./Soft

(Si il est impossible de lancer, s'assurer que le fichier *Soft* a le droit de s'exécuter :

> $ chmod +x Soft

Il est possible de lancer le logiciel au démarrage de la Raspberry Pi via un daemon (dossier **daemon** de ce dépôt). 

Le logiciel embarqué doit être démarré avant toute connexion par un client. 

### Utilisation du client de test
Le dossier **Client** contient un petit programme en C++ permettant le contrôle du robot par la communication avec le logiciel embarqué. 
Il se compile avec G++ :
> $ g++ main.cpp -o Client

