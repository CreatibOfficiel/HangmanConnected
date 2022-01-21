#pragma once
#include <stdio.h>	
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

class CClient
{
private:
	bool m_isConnected; // Est ce que la connexion est r�alis�e ?
	WSADATA wsa;			// Socket
	SOCKET sock;			// Socket
	SOCKADDR_IN sin;		// Socket
	char ip[15]; // Ip du serveur
	int port; // Port du serveur

public:
	void startup();			// Pr�lancer la connexion
	void init();			// Initialiser les valeurs de connexion (Ip et Port de connexion) c�t� Client
	void createSocket();	// Cr�ation de la socket qui fera la liaison
	void connectToSocket();	// Connexion � la socket
	void exchange();		// Echange d'informations et Coeur du programme (Jeu de Pendu)

	SOCKET getSocket() { return sock; }	// Getter : Renvoie la Socket

private:
	void end(); // Fermeture de la liaison
};

