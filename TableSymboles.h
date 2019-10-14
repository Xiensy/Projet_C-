#ifndef TABLESYMBOLES_H
#define TABLESYMBOLES_H

#include "SymboleValue.h"
#include <vector>
#include <iostream>
using namespace std;

class TableSymboles {
public:
    TableSymboles(); // Construit une table vide de pointeurs sur des symboles valués
    SymboleValue* chercheAjoute(const Symbole & symbole);
    // si symbole est identique à un symbole valué déjà présent dans la table,
    // on renvoie un pointeur sur ce symbole valué
    // Sinon on insère un nouveau symbole valué correspondant à symbole
    // et on renvoie un pointeur sur le nouveau symbole valué inséré

    inline unsigned int getTaille() const {
        return m_table.size();
    } // Taille de la table des symboles valués

    inline const SymboleValue & operator[](unsigned int i) const {
        return *m_table[i];
    } // accès au ième SymboleValue de la table
    friend ostream & operator<<(ostream & cout, const TableSymboles & ts); // affiche ts sur cout

private:
    vector<SymboleValue*> m_table; // La table des symboles valués, triée sur la chaine
    // (on aurait dû plus judicieusement utiliser map au lieu de vector)
};
#endif /* TABLESYMBOLES_H */
