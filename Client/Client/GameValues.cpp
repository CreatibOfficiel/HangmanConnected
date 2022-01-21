#include "GameValues.h"
#include <iostream>

using namespace std;

// Renvoie l'affichage du mot avec ses caractères "*" => Seulement les lettres trouvées
std::string GameValues::returnWord(char c)
{
	if (m_lettersFind.size() == 0)
		setCorrectSize();

    m_strAlreadyAsked.push_back(c);

	std::string phrase;
	for (int i = 0; i < m_word.size(); i++)
	{
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { // Si c'est bien une lettre
            if (c == m_word[i] || getOtherCasseForLetter(c) == m_word[i]) // Si la lettre y est
                m_lettersFind[i] = true; // On met à 1 la case du tableau de booléens correspondant à la lettre actuelle
        }

		if (m_lettersFind[i] == true){
			phrase += m_word[i];
		}
		else {
			phrase += '*';
		}		
	}

	return phrase;
}

// Renvoie la casse inverse de la lettre en paramètre (si "a" alors "A", si "H" alors "h")
char GameValues::getOtherCasseForLetter(char letter) // Change la casse de la lettre en paramètre
{
    if (letter - 97 < 0) // La lettre est en Majuscule
        return letter + 32; // On la renvoie en minuscule
    else // La lettre est en minuscule
        return letter - 32; // On la renvoie en majuscule
}

// Renvoie TRUE si la lettre a déjà été demandée
bool GameValues::isAlreadyAsked(char letter)
{
    for (char c : m_strAlreadyAsked)
    {
        if (c == letter || getOtherCasseForLetter(letter) == c)
            return true;
    }
    return false;
}



// Analyse le résultat obtenu avec la lettre demandée(paramètre = F, T, D, V)
void GameValues::analyseAnswer(char c)
{
    system("cls");
	switch (c)
	{
	case 'V':
		setIsEnd();
		std::cout << "\nVictoire ! Vous avez trouve le mot.\n";	
		break;
	case 'T':
		std::cout << "\nBravo ! Vous avez trouve une lettre.\n";
		break;
	case 'F':
		m_coups--;
		std::cout << "\nDommage ! Ce n'est pas une bonne lettre.\n";
		break;
	case 'D':
        m_coups--;
		setIsEnd();
		std::cout << "\nAie... Vous etes mort ! Le mot etait : " << m_word << std::endl;
        draw();
		break;
	default:
		break;
	}
}

// Enregistre le mot à trouver (paramètre) dans m_word
void GameValues::setWord(char* tab)
{
    m_word = "";
	std::string word = tab;
    size_t i = 0;
	//for (char c : word) {
	//	if (c != '1')
	//		m_word += c;
	//}
    while (tab[i] != '1')
    {
        m_word += tab[i];
        ++i;
    }
    setCorrectSize();
}

// Resize le tableau de booléan qui stocke les positions des lettres trouvées
void GameValues::setCorrectSize()
{
	m_lettersFind.resize(m_word.size());
	for (int i = 0; i < m_lettersFind.size(); i++)
		m_lettersFind[i] = false;
}

// Affichage du pendu selon l'avancée du joueur
void GameValues::draw()
{
    switch (m_coups)
    {
    case 0:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|       /|\\" << endl;
        cout << "\t\t\t|        |" << endl;
        cout << "\t\t\t|       / \\" << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 1:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|       /|\\" << endl;
        cout << "\t\t\t|        |" << endl;
        cout << "\t\t\t|         \\" << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 2:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|       /|\\" << endl;
        cout << "\t\t\t|        |" << endl;
        cout << "\t\t\t|          " << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 3:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|       /|\\" << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|      " << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 4:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|        |\\" << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|       " << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 5:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|        |" << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|       " << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 6:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        0" << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|       " << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    case 7:
        cout << "\t\t\t|--------|" << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|        " << endl;
        cout << "\t\t\t|       " << endl;
        cout << "\t\t\t|" << endl;
        cout << "\t\t\t|_" << endl;
        break;
    }
}


void GameValues::reset()
{
    m_isEnd = false;
    m_coups = 8;

    for (bool b : m_lettersFind)
        b = false;

    m_strAlreadyAsked = "";
}