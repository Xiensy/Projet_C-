#include "Lecteur.h"
#include "Exceptions.h"
#include <ctype.h>
#include <string.h>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////

Lecteur::Lecteur(ifstream& fichier) :
m_lecteurCar(fichier), m_symbole("") {
  avancer(); // pour aller lire le premier symbole
}

////////////////////////////////////////////////////////////////////////////////

void Lecteur::avancer() {
  sauterSeparateurs();
  // on est maintenant positionne sur le premier caractère d'un symbole
  m_ligne = m_lecteurCar.getLigne();
  m_colonne = m_lecteurCar.getColonne();
  m_symbole = Symbole(motSuivant()); // on reconstruit symbole avec le nouveau mot lu
}

////////////////////////////////////////////////////////////////////////////////

void Lecteur::sauterSeparateurs() {
  while (m_lecteurCar.getCaractere() == ' ' ||
          m_lecteurCar.getCaractere() == '\t' ||
          m_lecteurCar.getCaractere() == '\r' ||
          m_lecteurCar.getCaractere() == '\n')
    m_lecteurCar.avancer();
  if (m_lecteurCar.getCaractere() == '#') {
    do {
      m_lecteurCar.avancer();
    } while (m_lecteurCar.getCaractere() != '\r' &&
            m_lecteurCar.getCaractere() != '\n' &&
            m_lecteurCar.getCaractere() != EOF);
    sauterSeparateurs();
  }
}

////////////////////////////////////////////////////////////////////////////////

string Lecteur::motSuivant() {
  string s;
  s = "";
  if (isdigit(m_lecteurCar.getCaractere()))
    // c'est le début d'un entier
    do {
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    } while (isdigit(m_lecteurCar.getCaractere()));

  else if (isalpha(m_lecteurCar.getCaractere()))
    // c'est le début d'un mot
    do {
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    } while (isalpha(m_lecteurCar.getCaractere()) ||
            isdigit(m_lecteurCar.getCaractere()) ||
            m_lecteurCar.getCaractere() == '_');
  else if (m_lecteurCar.getCaractere() == '"') {
    // c'est le début d'une chaîne
    do {
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    } while (m_lecteurCar.getCaractere() != '"' &&
            m_lecteurCar.getCaractere() != '\n' &&
            m_lecteurCar.getCaractere() != EOF);
    if (m_lecteurCar.getCaractere() == '"') {
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    }
  } else if (m_lecteurCar.getCaractere() == '=' || m_lecteurCar.getCaractere() == '!' ||
          m_lecteurCar.getCaractere() == '<' || m_lecteurCar.getCaractere() == '>') {
    s = s + m_lecteurCar.getCaractere();
    m_lecteurCar.avancer();
    if (m_lecteurCar.getCaractere() == '=') {
      // pour lire les symbole == != <= >=
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    }
  } else if (m_lecteurCar.getCaractere() == '+') {
    s = s + m_lecteurCar.getCaractere();
    m_lecteurCar.avancer();
    if (m_lecteurCar.getCaractere() == '+') {
      // pour lire les symbole ++
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    }
  } else if (m_lecteurCar.getCaractere() == '-') {
    s = s + m_lecteurCar.getCaractere();
    m_lecteurCar.avancer();
    if (m_lecteurCar.getCaractere() == '-') {
      // pour lire les symbole --
      s = s + m_lecteurCar.getCaractere();
      m_lecteurCar.avancer();
    }
  } else if (m_lecteurCar.getCaractere() != EOF)
    // c'est un caractere spécial
  {
    s = m_lecteurCar.getCaractere();
    m_lecteurCar.avancer();
  }
  return s;
}

////////////////////////////////////////////////////////////////////////////////

LecteurCaractere::LecteurCaractere(ifstream & fichier) : m_fichier(fichier) {
  m_ligne = 1;
  m_colonne = 0;
  if (m_fichier.fail()) // si le fichier ne peut-être lu...
    throw FichierException();
  avancer();
}

////////////////////////////////////////////////////////////////////////////////

void LecteurCaractere::avancer() {
  if (m_fichier.peek() == EOF)
    m_caractere = EOF;
  else {
    if (m_caractere == '\n') {
      m_colonne = 0;
      m_ligne++;
    }
    m_fichier.get(m_caractere);
    m_colonne++;
  }
}
