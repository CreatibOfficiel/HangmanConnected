#include "Client.h"
#include "GameValues.h"

// Taille maximale pour un mot français => Taille maximale pour l'échange de données
#define N 25

// Prélancer la connexion
void CClient::startup()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0) {
		std::cout << "Probleme...";
	}
}

// Initialiser les valeurs de connexion (Ip et Port de connexion) côté Client
void CClient::init()
{
	printf("Ip : ");
	std::cin >> ip;

	printf("%s", "\nPort : ");
	std::cin >> port;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(port);
}

// Création de la socket qui fera la liaison
void CClient::createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

// Connexion à la socket
void CClient::connectToSocket()
{
	if (connect(sock, (SOCKADDR*)&sin, sizeof(sin)))
	{
		printf("La connexion a echouee\n");
		
		system("PAUSE");
		exit(0);
	}
	else {
		printf("Connexion reussie!");
		m_isConnected = true;
	}
}

// Echange d'informations et Coeur du programme (Jeu de Pendu)
void CClient::exchange()
{
	char buffer[N] = "111111111111111111111111", input = '!';
	int err = 0;
	GameValues gv;
	std::cout << "\nEn attente du mot...";

	while (err > -1)
	{
		err = recv(sock, buffer, sizeof(buffer), 0);
		std::cout << "\nMot reçu, lancement du jeu !";
		gv.setWord(buffer);

		while(gv.getIsEnd() == false) {
			gv.draw();
			std::cout << "\n\nVotre mot : " << gv.returnWord(input) << std::endl;
			std::cout << "Ecrivez une lettre pour trouver le mot : ";
			std::cin >> buffer;
			// Gérer les nons-lettres :
			while (buffer[0] < 65 || (buffer[0] > 90 && buffer[0] < 97) || buffer[0] > 122) // N'est pas dans l'alphabet (maj et min)
			{
				std::cout << "Ce n'est pas une lettre, veuillez en proposer une : ";
				std::cin >> buffer;
			}
			// Gérer les lettres déja demandées :
			while (gv.isAlreadyAsked(buffer[0]))
			{
				std::cout << "Vous avez deja propose cette lettre, veuillez en choisir une nouvelle : ";
				std::cin >> buffer;
			}

			input = buffer[0]; // stockage de la lettre
			err = send(sock, buffer, sizeof(buffer), 0);
			err = recv(sock, buffer, sizeof(buffer), 0);
			gv.analyseAnswer(buffer[0]);
		}
		std::cout << "\nVoulez-vous rejouez ? (o/n)\n";
		std::cin >> buffer;
		err = send(sock, buffer, sizeof(buffer), 0);
		if (buffer[0] == 'o' || buffer[0] == 'O')
		{
			std::cout << "\nEn attente du retour du serveur...\n";
			gv.reset();
			input = '!';
		}
		else
		{
			std::cout << "\nVous pouvez fermer l'application.\nMerci d'y avoir joué !\n";
			gv.reset();
			input = '!';
			err = -1;
		}
	}
	end();
}

// Fermeture de la liaison
void CClient::end()
{
	closesocket(sock);
	printf("\n\nConnexion terminée\n\n");
	m_isConnected = false;
	WSACleanup();
}
