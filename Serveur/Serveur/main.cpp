#include <stdio.h>	
#include <winsock2.h>
#include <iostream>
#include "Serveur.h"

#pragma comment(lib,"ws2_32.lib")

#define N 1000

void main()
{
	system("chcp 1252");

	CServeur host;
	host.startup();

	// Initialisation et saisie des informations
	host.init();

	// Création de la socket
	host.createSocket();

	// La socket est configurée pour écouter l'adresse et le port saisis
	host.connectToSocket();

	// Choix de la difficulté
	char choice = 0;
	std::cout << "\nVous pouvez au choix prendre un mot : " << std::endl
		<< "   1 - De Difficulté Facile" << std::endl
		<< "   2 - De Difficulté Moyen" << std::endl
		<< "   3 - De Difficulté Dure" << std::endl
		<< "   4 - De Votre Esprit (Il vous sera alors demandé de l'écrire)" << std::endl << std::endl
		<< " Faites votre choix en entrant son numéro : ";
	std::cin >> choice;
	while (choice != '1' && choice != '2' && choice != '3' && choice != '4')
	{
		std::cout << "Ce n'est pas un choix valable... Réessayez : ";
		std::cin >> choice;
	}

	// Lancement du jeu
	host.exchange(choice);
}
