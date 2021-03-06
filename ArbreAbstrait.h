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
    virtual int  executer() =0 ; // Méthode pure (non implémentée) qui rend la classe abstraite
    virtual void ajoute(Noeud* instruction) { throw OperationInterditeException(); }
    virtual ~Noeud() {} // Présence d'un destructeur virtuel conseillée dans les classes abstraites
    virtual void traduitEnPHP(ostream & cout, unsigned int indentation)const;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSeqInst : public Noeud {
// Classe pour représenter un noeud "sequence d'instruction"
//  qui a autant de fils que d'instructions dans la séquence
  public:
     NoeudSeqInst();   // Construit une séquence d'instruction vide
    ~NoeudSeqInst() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();    // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction);  // Ajoute une instruction à la séquence
    void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    
  private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////
class NoeudAffectation : public Noeud {
// Classe pour représenter un noeud "affectation"
//  composé de 2 fils : la variable et l'expression qu'on lui affecte
  public:
     NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
    ~NoeudAffectation() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();        // Exécute (évalue) l'expression et affecte sa valeur à la variable
    void traduitEnPHP(ostream& cout, unsigned int indentation) const override;
    
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
   ~NoeudOperateurBinaire() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();            // Exécute (évalue) l'opération binaire)
    void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    
  private:
    Symbole m_operateur;
    Noeud*  m_operandeGauche;
    Noeud*  m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstSi : public Noeud {
// Classe pour représenter un noeud "instruction si"
//  et ses 2 fils : la condition du si et la séquence d'instruction associée
  public:
    NoeudInstSi(Noeud* condition, Noeud* sequence);
     // Construit une "instruction si" avec sa condition et sa séquence d'instruction
   ~NoeudInstSi() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction si : si condition vraie on exécute la séquence
    void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    
  private:
    Noeud* m_condition;
    Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstTantQue : public Noeud{
    // "tantque"
    public:
        NoeudInstTantQue(Noeud* condition, Noeud* sequence);
        ~NoeudInstTantQue(){}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

        
    private:
        Noeud* m_condition;
        Noeud* m_sequence;
};
////////////////////////////////////////////////////////////////////////////////
class NoeudInstSiRiche : public Noeud{
    //"si" "sinonsi" "sinon"
    public:
        NoeudInstSiRiche(vector<Noeud*> conditions, vector<Noeud*> sequences);
        ~NoeudInstSiRiche(){}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        vector<Noeud*> m_conditions;
        vector<Noeud*> m_sequences;
    
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstRepeter : public Noeud{
    // "repeter" "jusqua"
    public:
        NoeudInstRepeter(Noeud* condition, Noeud* sequence);
        ~NoeudInstRepeter(){}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

        
    private:
        Noeud* m_condition;
        Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstPour : public Noeud{
    // "pour" 
    public:
        NoeudInstPour(Noeud* condition, Noeud* sequence, Noeud* affectation1, Noeud* affectation2);
        ~NoeudInstPour(){}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

        
    private:
        Noeud* m_condition;
        Noeud* m_sequence;
        Noeud* m_affectation1;
        Noeud* m_affectation2;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstEcrire : public Noeud{
    //"ecrire"
    public :
        NoeudInstEcrire(vector<Noeud*> elements);
        ~NoeudInstEcrire() {}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        vector<Noeud*> m_elems;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstLire : public Noeud{
    //"lire"
    public :
        NoeudInstLire(vector<Noeud*> variables);
        ~NoeudInstLire() {}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        vector<Noeud*> m_vars;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstAppelProcedure : public Noeud{
    //"procedure"
    public :
        NoeudInstAppelProcedure(vector<Noeud*> variables, vector<string> oldVariables, Noeud* sequence, string nom);
        ~NoeudInstAppelProcedure() {}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        vector<Noeud*> m_vars;
        vector<string> m_oldVars;
        Noeud* m_sequence;
        string m_nom;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstAppelFonction : public Noeud{
    //"procedure"
    public :
        NoeudInstAppelFonction(vector<Noeud*> variables, vector<string> oldVariables, Noeud* sequence, Noeud* varReturn, string nom);
        ~NoeudInstAppelFonction() {}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        vector<Noeud*> m_vars;
        vector<string> m_oldVars;
        Noeud* m_sequence;
        Noeud* m_varReturn;
        string m_nom;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstIncrementation : public Noeud{
    public:
        NoeudInstIncrementation(Noeud* var);
        ~NoeudInstIncrementation() {}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        Noeud* m_variable;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstDecrementation : public Noeud{
    public:
        NoeudInstDecrementation(Noeud* var);
        ~NoeudInstDecrementation() {}
        int executer();
        void traduitEnPHP(ostream& cout, unsigned int indentation) const override;

    private:
        Noeud* m_variable;
};
#endif /* ARBREABSTRAIT_H */
