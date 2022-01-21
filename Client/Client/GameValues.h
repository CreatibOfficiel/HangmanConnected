#pragma once
#include <vector>
#include <string>

//********************************
// Améliorations :
// Enlever m_word
//
//********************************

// Classe pour gérer le Jeu de Pendu
class GameValues
{
private:
	bool m_isEnd = false; // Le jeu est-il terminé ?
	int m_coups = 8; // Nombre de coups disponibles pour le joueur avant d'être pendu
	std::string m_word; // Mot à trouver du joueur (sert pour l'affichage) 
	std::vector<bool> m_lettersFind; // Tableau de booléens. Chaque case correspond à une lettre du mot secret. 0 = lettre non trouvée, 1 = lettre trouvée
	std::string m_strAlreadyAsked; // Tableau de Char conservant les lettres déjà demandées par le joueur

public:
	bool getIsEnd() { return m_isEnd; } // Getter : Le jeu est-il terminé ?
	void setIsEnd() { m_isEnd = true; } // Setter : Le jeu est terminé

	std::string returnWord(char);		// Renvoie l'affichage du mot avec ses caractères "*" => Seulement les lettres trouvées
	char getOtherCasseForLetter(char);	// Renvoie la casse inverse de la lettre en paramètre (si "a" alors "A", si "H" alors "h")
	bool isAlreadyAsked(char);			// Renvoie TRUE si la lettre a déjà été demandée

	void analyseAnswer(char);	// Analyse le résultat obtenu avec la lettre demandée (paramètre = F, T, D, V)
	void setWord(char*);		// Enregistre le mot à trouver (paramètre) dans m_word
	void setCorrectSize();		// Resize le tableau de booléan qui stocke les positions des lettres trouvées
	void draw();				// Affichage du pendu selon l'avancée du joueur

	void reset();
};

