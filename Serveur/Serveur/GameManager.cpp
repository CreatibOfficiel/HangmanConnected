#include "GameManager.h"
#include <fstream>
#include <iostream>

// Renvoie le nombres de coups restant au Joueur
int CGameManager::getCoupsRestants()
{
    return m_coupsRestants;
}

// Getter : Le mot a-t-il été trouvé ?
bool CGameManager::wordIsFound()
{
    for (bool b : m_listOfLetterFind) {
        if (b == false)
            return false;
    }

    return true;
}

// Renvoie le résultat de la lettre : F, T, D, V
char CGameManager::ifLetterIsInWord(char letter)
{
    char result = 'F';

    for (int i = 0; i < m_secretWord.size(); i++) // On parcourt motSecret pour vérifier si la lettre proposée y est
    {

        if (letter == m_secretWord[i] || getOtherCasseForLetter(letter) == m_secretWord[i]) // Si la lettre y est
        {
            result = 'T'; // On mémorise que c'était une bonne lettre
            m_listOfLetterFind[i] = true; // On met à 1 la case du tableau de booléens correspondant à la lettre actuelle
        }
    }

    if(result == 'F') // mauvaise lettre
        m_coupsRestants--;

    if (m_coupsRestants == 0) // mort
        result = 'D';

    if (result == 'T' && wordIsFound()) // victoire
        result = 'V';
    
	return result;
}

// Renvoie la casse inverse de la lettre en paramètre (si "a" alors "A", si "H" alors "h")
char CGameManager::getOtherCasseForLetter(char letter) // Change la casse de la lettre en paramètre
{
    if (letter - 97 < 0) // La lettre est en Majuscule
        return letter + 32; // On la renvoie en minuscule
    else // La lettre est en minuscule
        return letter - 32; // On la renvoie en majuscule
}

// Getter : Le mot est-il français ?
bool CGameManager::isFrench(std::string word)
{
    for (char c : word)
    {
        if (c < 65 || (c > 90 && c < 97) || c > 122) // N'est pas dans l'alphabet (maj et min)
        {
            std::cout << "\nATTENTION ! " << c << " n'est pas une lettre";
            return false;
        }
    }
    return true;
}




// Demande le mot à deviner au Serveur (Personne derrière l'écran)
void CGameManager::askForWordToServer()
{
    std::string word;
    std::cout << "\nVeuillez entrer le mot que vous souhaitez faire deviner : ";
    std::cin >> word;
    // On vérifie que ce soit Français
    while (!isFrench(word))
    {
        std::cout << "\nLe mot proposé (" << word << ") n'est pas correct, veuillez en reproposer un : ";
        std::cin >> word;
    }
    m_secretWord = word;
    m_listOfLetterFind.resize(word.size());
    for (int i = 0; i < m_listOfLetterFind.size(); i++)
        m_listOfLetterFind[i] = false;
}

// Détermine le mot aléatoirement dans la liste proposée par readFile()
void CGameManager::setRandomWord()
{
    srand(time(NULL));
    int r = rand() % m_listOfWords.size();
    std::string s = m_listOfWords[r];
    m_secretWord = s;
    m_listOfLetterFind.resize(s.size());
    for (int i = 0; i < m_listOfLetterFind.size(); i++)
        m_listOfLetterFind[i] = false;
}

// Récupère la liste de mot dans le fichier
void CGameManager::readFile(char diff)
{
    std::string fileName = "list_words";
    fileName.push_back(diff);
    fileName += ".txt";
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        std::cout << "Erreur fichier : " << fileName << " introuvable.";
        return;
    }

    std::string word;
    while (file >> word)
        m_listOfWords.push_back(word);
}

// Affiche l'avancée du Joueur dans le jeu
void CGameManager::lookAdvancementPlayer(char letter, char var)
{
    switch (var)
    {
    case 'F':
        std::cout << "\nLe joueur a essayé la lettre " << letter << " et a échoué. " << m_coupsRestants << " coup(s) restants.";
        break;
    case 'T':
        std::cout << "\nLe joueur a essayé la lettre " << letter << " et à réussi.";
        break;
    case 'D':
        std::cout << "\nLe joueur a scellé son destin sur la lettre " << letter << " et a tout perdu.";
        break;
    case 'V':
        std::cout << "\nLe joueur a tenté et réussi à résoudre ce pendu grâce à la lettre " << letter << ".";
    default:
        break;
    }
}

void CGameManager::reset()
{
    m_coupsRestants = 8;
    m_secretWord = "";
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

    if (choice != '4') // Mot dans BDD
    {
        readFile(choice);
        setRandomWord();
    }
    else
        askForWordToServer();
}