#include "Serveur.h"
#include "GameManager.h"

#define N 2

// Taille maximale pour un mot français => Taille maximale pour l'échange de données
#define V 25

// Prélancer la connexion
void CServeur::startup()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0) {
		std::cout << "Probleme...";
	}
}

// Initialiser les valeurs de connexion (Ip et Port de connexion) côté Client
void CServeur::init()
{
	printf("Port : ");
	std::cin >> port;

	sinserv.sin_family = AF_INET;
	sinserv.sin_addr.s_addr = INADDR_ANY;
	sinserv.sin_port = htons(port);
}

// Création de la socket qui fera la liaison
void CServeur::createSocket()
{
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

// Connexion à la socket
void CServeur::connectToSocket()
{
	bind(server, (SOCKADDR*)&sinserv, sizeof(sinserv));
	//pas de file d'attente
	listen(server, 0);
	m_isConnected = true;
}

// Echange d'informations et Coeur du programme (Jeu de Pendu)
void CServeur::exchange(char difficulty)
{
	char buffer[25] = "111111111111111111111111";
	CGameManager gm{difficulty};

	std::cout << "\nLe mot à trouver pour le joueur est : " << gm.getSecretWord();

	int sinsize;
	int err = 0;
	bool continuer = true;
	while (continuer)
	{
		sinsize = sizeof(sin);

		std::cout << "\nEn attente d'un joueur...";
		//acceptation ou non des appels
		if ((sock = accept(server, (SOCKADDR*)&sin, &sinsize)) != INVALID_SOCKET)
		{
			for (int i = 0; i < gm.getSecretWord().size(); i++)
				buffer[i] = gm.getSecretWord()[i];

			err = send(sock, buffer, sizeof(buffer), 0);
			std::cout << "\nJoueur trouvé, lancement du jeu !";

			while (err > -1)
			{
				
				do {
					err = recv(sock, buffer, sizeof(buffer), 0);
					char letter = buffer[0];
					buffer[0] = gm.ifLetterIsInWord(letter);
					if (letter != buffer[0]) { gm.lookAdvancementPlayer(letter, buffer[0]); } // Test car pitit bug a la fermeture
					err = send(sock, buffer, sizeof(buffer), 0);
				} while (gm.getCoupsRestants() > 0 && !gm.wordIsFound());

				// Rejouer ?
				err = recv(sock, buffer, sizeof(buffer), 0);
				if (buffer[0] == 'o' || buffer[0] == 'O')
				{
					system("cls");
					std::cout << "\nLe joueur veut rejouer.";
					gm.reset();

					for (int i = 0; i < 25; i++)
						buffer[i] = '1';

					for (int i = 0; i < gm.getSecretWord().size(); i++)
						buffer[i] = gm.getSecretWord()[i];

					err = send(sock, buffer, sizeof(buffer), 0);
					std::cout << "\nLe mot est " << gm.getSecretWord() << ", lancement du jeu !";
				}
				else
				{
					std::cout << "\nLe joueur ne veut pas rejouer.\nVous pouvez fermer l'application.\n";
					continuer = false;
					err = -1;
				}
			}
			closesocket(sock);
		}
	}
	end();
}

// Fermeture de la liaison
void CServeur::end()
{
	closesocket(server);
	m_isConnected = false;
	WSACleanup();
}