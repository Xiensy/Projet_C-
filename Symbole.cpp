#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "Exceptions.h"
#include "Symbole.h"

const char * Symbole::FICHIER_MOTS_CLES = "motsCles.txt";

Symbole::Symbole(const string & s) : m_chaine(s) {
  // attention : l'ordre des tests ci-dessous n'est pas innocent !
  if (s == "") this->m_categorie = FINDEFICHIER;
  else if (isdigit(s[0])) this->m_categorie = ENTIER;
  else if (s.size() >= 2 && s[0] == '"' && s[s.size() - 1] == '"') this->m_categorie = CHAINE;
  else if (isMotCle(s)) this->m_categorie = MOTCLE;
  else if (isalpha(s[0])) this->m_categorie = VARIABLE;
  else this->m_categorie = INDEFINI;
}

bool Symbole::operator==(const string & ch) const {
  return this->m_chaine == ch ||
          (this->m_categorie == VARIABLE     && (ch == "<VARIABLE>"     || ch == "<variable>")) ||
          (this->m_categorie == ENTIER       && (ch == "<ENTIER>"       || ch == "<entier>"))   ||
          (this->m_categorie == CHAINE       && (ch == "<CHAINE>"       || ch == "<chaine>"))   ||
          (this->m_categorie == INDEFINI     && (ch == "<INDEFINI>"     || ch == "<indefini>")) ||
          (this->m_categorie == FINDEFICHIER && (ch == "<FINDEFICHIER>" || ch == "<findefichier>"));
}

bool Symbole::isMotCle(const string & s) const {
  static vector<string> motsCles;
  // si on n'a pas encore chargé les mots clés dans le vecteur, on le fait !
  if (!motsCles.size()) {
    ifstream fichier(FICHIER_MOTS_CLES);
    if (fichier.fail()) throw FichierException();
    while (!fichier.eof()) {
      string mot;
      getline(fichier, mot);
      if (mot != "") { // insertion triée de mot dans le vecteur des mots clés
        vector<string>::iterator it = motsCles.begin();
        while (it < motsCles.end() && *it < mot) it++;
        if (it == motsCles.end() || *it != mot) // si pas trouvé...
          motsCles.insert(it, mot);
      }
    }
    fichier.close();
  }
  // on recherche  s dans le vecteur des mots clés triés
  unsigned int i;
  for (i = 0; i < motsCles.size() && motsCles[i] < s; i++);
  return (i < motsCles.size() && motsCles[i] == s);
}

ostream & operator<<(ostream & cout, const Symbole & symbole) {
  cout << "Symbole de type ";
  if      (symbole.m_categorie == Symbole::MOTCLE)       cout << "<MOTCLE>      ";
  else if (symbole.m_categorie == Symbole::VARIABLE)     cout << "<VARIABLE>    ";
  else if (symbole.m_categorie == Symbole::ENTIER)       cout << "<ENTIER>      ";
  else if (symbole.m_categorie == Symbole::CHAINE)       cout << "<CHAINE>      ";
  else if (symbole.m_categorie == Symbole::INDEFINI)     cout << "<INDEFINI>    ";
  else if (symbole.m_categorie == Symbole::FINDEFICHIER) cout << "<FINDEFICHIER>";
  cout << " : \"" << symbole.m_chaine << "\"";
  return cout;
}
