#ifndef LECTEUR_H
#define LECTEUR_H

#include <fstream>
#include <string>
using namespace std;

#include "Symbole.h"

// Lecteur pour parcourir un fichier texte caractère par caractère

class LecteurCaractere {
public:
    LecteurCaractere(ifstream & fichier); // Construit le lecteur pour parcourir fichier

    inline char getCaractere() const {
        return m_caractere;
    } // Caractere courant

    inline unsigned int getLigne() const {
        return m_ligne;
    } // Ligne du caractère courant

    inline unsigned int getColonne() const {
        return m_colonne;
    } // Colonne du caractère courant
    void avancer(); // Passe au caractere suivant, s'il existe, sinon reste sur le caractère de fin de fichier (EOF)

private:
    ifstream& m_fichier; // Le fichier texte que l'on parcourt
    char m_caractere; // Le caractere courant
    unsigned int m_ligne; // Ligne du caractere courant dans le fichier
    unsigned int m_colonne; // Colonne du caractere courant dans le fichier
};

// Lecteur pour parcourir un fichier texte symbole par symbole

class Lecteur {
public:
    Lecteur(ifstream & fichier); // Résultat : symbole = premier symbole du fichier
    void avancer(); // Passe au symbole suivant du fichier

    inline const Symbole& getSymbole() const {
        return m_symbole;
    } // Symbole courant

    inline unsigned int getLigne() const {
        return m_ligne;
    } // Ligne du symbole courant

    inline unsigned int getColonne() const {
        return m_colonne;
    } // Colonne du symbole courant

private:
    LecteurCaractere m_lecteurCar; // Le lecteur de caractères utilisé
    Symbole m_symbole; // Le symbole courant du lecteur de symboles
    unsigned int m_ligne, m_colonne; // Coordonnees, dans le fichier, du symbole courant
    void sauterSeparateurs(); // Saute avec m_lecteurCar une suite de séparateurs, commentaires consécutifs
    string motSuivant(); // Lit avec m_lecteurCar la chaîne du prochain symbole et la renvoie en résultat
};

#endif /* LECTEUR_H */ 
