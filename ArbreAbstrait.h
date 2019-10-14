#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////

class Noeud {
    // Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
    // Remarque : la classe ne contient aucun constructeur
public:
    virtual int executer() = 0; // Méthode pure (non implémentée) qui rend la classe abstraite

    virtual void ajoute(Noeud* instruction) {
        throw OperationInterditeException();
    }

    virtual ~Noeud() {
    } // Présence d'un destructeur virtuel conseillée dans les classes abstraites
};

////////////////////////////////////////////////////////////////////////////////

class NoeudSeqInst : public Noeud {
    // Classe pour représenter un noeud "sequence d'instruction"
    //  qui a autant de fils que d'instructions dans la séquence
public:
    NoeudSeqInst(); // Construit une séquence d'instruction vide

    ~NoeudSeqInst() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction) override; // Ajoute une instruction à la séquence

private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////

class NoeudAffectation : public Noeud {
    // Classe pour représenter un noeud "affectation"
    //  composé de 2 fils : la variable et l'expression qu'on lui affecte
public:
    NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation

    ~NoeudAffectation() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute (évalue) l'expression et affecte sa valeur à la variable

private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudOperateurBinaire : public Noeud {
    // Classe pour représenter un noeud "opération binaire" composé d'un opérateur
    //  et de 2 fils : l'opérande gauche et l'opérande droit
public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit

    ~NoeudOperateurBinaire() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute (évalue) l'opération binaire)

private:
    Symbole m_operateur;
    Noeud* m_operandeGauche;
    Noeud* m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstSi : public Noeud {
    // Classe pour représenter un noeud "instruction si"
    //  et ses 2 fils : la condition du si et la séquence d'instruction associée
public:
    NoeudInstSi(Noeud* condition, Noeud* sequence);
    // Construit une "instruction si" avec sa condition et sa séquence d'instruction

    ~NoeudInstSi() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction si : si condition vraie on exécute la séquence

private:
    Noeud* m_condition;
    Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstTantque : public Noeud {
private:
    Noeud* m_condition;
    Noeud* m_sequence;

public:

    NoeudInstTantque(Noeud* condition, Noeud* sequence);

    int executer() override;
    
    virtual ~NoeudInstTantque(){};
       
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstSiRiche : public Noeud {
private:
    std::vector<Noeud*> m_conditions;
    std::vector<Noeud*> m_sequences;
    
public:
    NoeudInstSiRiche(std::vector<Noeud*> conditions, std::vector<Noeud*> sequences);
    
    int executer() override;
    
    virtual ~NoeudInstSiRiche(){};
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstRepeter : public Noeud{
private:
    Noeud* m_condition;
    Noeud* m_sequence;
    
public :
    NoeudInstRepeter(Noeud* condition,Noeud* sequence);
    int executer() override;    
    virtual ~NoeudInstRepeter(){};
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstPour : public Noeud{
private:
    Noeud* m_condition;
    Noeud* m_sequence;
    Noeud* m_affectation1;
    Noeud* m_affectation2;
public :
    NoeudInstPour(Noeud* affectation1,Noeud* condition,Noeud* affectation2,Noeud* sequence);
    int executer() override;    
    virtual ~NoeudInstPour(){};
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstEcrire : public Noeud{
private:
    Noeud* m_exprouchaine;
    
public:
    NoeudInstEcrire(Noeud* exprouchaine);
    int executer() override;
    virtual ~NoeudInstEcrire(){};
};



#endif /* ARBREABSTRAIT_H */
