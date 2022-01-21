#pragma once
#pragma once
#include <stdio.h>	
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

class CServeur
{
private:
	bool m_isConnected; // Est ce que la connexion est réalisée ?
	WSADATA wsa;				// Socket
	SOCKET server;				// Socket
	SOCKET sock;				// Socket
	SOCKADDR_IN sinserv;		// Socket
	SOCKADDR_IN sin;			// Socket
	int port; // Port du serveur

public:
	void startup();			// Prélancer la connexion
	void init();			// Initialiser les valeurs de connexion (Ip et Port de connexion) côté Client
	void createSocket();	// Création de la socket qui fera la liaison
	void connectToSocket();	// Connexion à la socket
	void exchange(char);	// Echange d'informations et Coeur du programme (Jeu de Pendu), le paramètre règle la difficulté

private:
	void end(); // Fermeture de la liaison
};

