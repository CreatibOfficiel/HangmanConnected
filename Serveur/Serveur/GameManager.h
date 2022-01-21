#pragma once
#include <vector>
#include <string>
#include <time.h>

class CGameManager {
	std::vector<std::string> m_listOfWords; // Liste des mots enregistr�
	std::vector<bool> m_listOfLetterFind; // Tableau de bool�ens. Chaque case correspond � une lettre du mot secret. 0 = lettre non trouv�e, 1 = lettre trouv�e

	int m_coupsRestants = 8; // Nombre de coups disponibles pour le joueur avant d'�tre pendu

	std::string m_secretWord; // Mot secret

public:

	// <CONSTRUCTOR>
	CGameManager(char diff) {
		if (diff != '4') // Mot dans BDD
		{
			readFile(diff);
			setRandomWord();
		}
		else
			askForWordToServer();
	}

	// Getter : Renvoie le mot � trouver
	std::string getSecretWord() {
		return m_secretWord;
	}

	int getCoupsRestants();				// Renvoie le nombres de coups restant au Joueur
	bool wordIsFound();					// Getter : Le mot a-t-il �t� trouv� ?
	char ifLetterIsInWord(char);		// Renvoie le r�sultat de la lettre : F, T, D, V
	char getOtherCasseForLetter(char);	// Renvoie la casse inverse de la lettre en param�tre (si "a" alors "A", si "H" alors "h")
	bool isFrench(std::string);			// Getter : Le mot est-il fran�ais ?

	void askForWordToServer();	// Demande le mot � deviner au Serveur (Personne derri�re l'�cran)
	void setRandomWord();		// D�termine le mot al�atoirement dans la liste propos�e par readFile()
	void readFile(char);		// R�cup�re la liste de mot dans le fichier
	void lookAdvancementPlayer(char, char);	// Affiche l'avanc�e du Joueur dans le jeu

	void reset();
};