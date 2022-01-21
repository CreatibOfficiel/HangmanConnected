#include <stdio.h>	
#include <winsock2.h>
#include "Client.h"
#include <iostream>

void main()
{
	system("chcp 1252");

	printf("\t\t\t\tBienvenue dans le Pendu !\n\n"); // Affichage du Titre
	CClient client; // Création d'un client (joueur)

	// Initialisation et saisie des informations
	client.startup();
	client.init();

	// Création de la socket
	client.createSocket();

	// Connexion a la socket
	client.connectToSocket();

	// Lancement du jeu
	client.exchange();
}
