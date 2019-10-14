#ifndef SYMBOLE_H
#define SYMBOLE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Symbole représente un élément du langage (mot-clé, entier, identificateur de variable, ...)
class Symbole {
public:
	Symbole(const string & s = "");  // Construit le symbole à partir de la chaine (string) ch lue par le lecteur de symbole dans un fichier
	bool operator == (const string & ch) const ; // Pour tester l'égalité entre le symbole et une chaîne
	inline bool operator != (const string  & ch) const { return ! (*this == ch); } // Pour tester la différence...
	inline const string & getChaine() const { return m_chaine;} // Accesseur
	friend ostream & operator <<(ostream & cout, const Symbole & symbole); // Fonction amie pour pouvoir afficher un symbole sur cout 

private:
    	enum m_categorie { MOTCLE, VARIABLE, ENTIER, CHAINE, INDEFINI, FINDEFICHIER };
	string           m_chaine;             // Chaîne du symbole
	m_categorie      m_categorie;          // Categorie du symbole (voir type énuméré ci-dessus)
	bool             isMotCle(const string & s) const;  // Renvoie vrai si s est un mot clé du langage
        static const char * FICHIER_MOTS_CLES; // Le fichier des mots clés du langage
};

#endif /* SYMBOLE_H */
