#pragma once
#include <vector>
#include <string>
#include <time.h>

class CGameManager {
	std::vector<std::string> m_listOfWords; // Liste des mots enregistré
	std::vector<bool> m_listOfLetterFind; // Tableau de booléens. Chaque case correspond à une lettre du mot secret. 0 = lettre non trouvée, 1 = lettre trouvée

	int m_coupsRestants = 8; // Nombre de coups disponibles pour le joueur avant d'être pendu

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

	// Getter : Renvoie le mot à trouver
	std::string getSecretWord() {
		return m_secretWord;
	}

	int getCoupsRestants();				// Renvoie le nombres de coups restant au Joueur
	bool wordIsFound();					// Getter : Le mot a-t-il été trouvé ?
	char ifLetterIsInWord(char);		// Renvoie le résultat de la lettre : F, T, D, V
	char getOtherCasseForLetter(char);	// Renvoie la casse inverse de la lettre en paramètre (si "a" alors "A", si "H" alors "h")
	bool isFrench(std::string);			// Getter : Le mot est-il français ?

	void askForWordToServer();	// Demande le mot à deviner au Serveur (Personne derrière l'écran)
	void setRandomWord();		// Détermine le mot aléatoirement dans la liste proposée par readFile()
	void readFile(char);		// Récupère la liste de mot dans le fichier
	void lookAdvancementPlayer(char, char);	// Affiche l'avancée du Joueur dans le jeu

	void reset();
};