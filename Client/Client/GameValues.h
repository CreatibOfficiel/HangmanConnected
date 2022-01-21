#pragma once
#include <vector>
#include <string>

//********************************
// Am�liorations :
// Enlever m_word
//
//********************************

// Classe pour g�rer le Jeu de Pendu
class GameValues
{
private:
	bool m_isEnd = false; // Le jeu est-il termin� ?
	int m_coups = 8; // Nombre de coups disponibles pour le joueur avant d'�tre pendu
	std::string m_word; // Mot � trouver du joueur (sert pour l'affichage) 
	std::vector<bool> m_lettersFind; // Tableau de bool�ens. Chaque case correspond � une lettre du mot secret. 0 = lettre non trouv�e, 1 = lettre trouv�e
	std::string m_strAlreadyAsked; // Tableau de Char conservant les lettres d�j� demand�es par le joueur

public:
	bool getIsEnd() { return m_isEnd; } // Getter : Le jeu est-il termin� ?
	void setIsEnd() { m_isEnd = true; } // Setter : Le jeu est termin�

	std::string returnWord(char);		// Renvoie l'affichage du mot avec ses caract�res "*" => Seulement les lettres trouv�es
	char getOtherCasseForLetter(char);	// Renvoie la casse inverse de la lettre en param�tre (si "a" alors "A", si "H" alors "h")
	bool isAlreadyAsked(char);			// Renvoie TRUE si la lettre a d�j� �t� demand�e

	void analyseAnswer(char);	// Analyse le r�sultat obtenu avec la lettre demand�e (param�tre = F, T, D, V)
	void setWord(char*);		// Enregistre le mot � trouver (param�tre) dans m_word
	void setCorrectSize();		// Resize le tableau de bool�an qui stocke les positions des lettres trouv�es
	void draw();				// Affichage du pendu selon l'avanc�e du joueur

	void reset();
};

