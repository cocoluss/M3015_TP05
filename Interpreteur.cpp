#include "Interpreteur.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

#define TRY(X) try{X}catch(SyntaxeException e){cout << e.what() <<endl;m_comptErr++;}

using namespace std;

Interpreteur::Interpreteur(ifstream & fichier) :
m_lecteur(fichier), m_table(), m_arbre(nullptr), m_comptErr(0){
}

void Interpreteur::analyse() {
  m_arbre = programme(); // on lance l'analyse de la première règle
}

void Interpreteur::analyseproc() {
    Noeud* sequence;
    do{
        if (m_lecteur.getSymbole() == "procedure") {
            sequence = instProcedure();
        }
        else if (m_lecteur.getSymbole() == "fonction") {
            sequence = instFonction();
        }
        if (sequence != nullptr) {
            m_arbreproc[m_procActuelle] = sequence;
        }
    }while(sequence != nullptr);
}

void Interpreteur::tester(const string & symboleAttendu) const throw (SyntaxeException) {
  // Teste si le symbole courant est égal au symboleAttendu... Si non, lève une exception
  static char messageWhat[256];
  if (m_lecteur.getSymbole() != symboleAttendu) {
    sprintf(messageWhat,
            "Ligne %d, Colonne %d - Erreur de syntaxe - Symbole attendu : %s - Symbole trouvé : %s",
            m_lecteur.getLigne(), m_lecteur.getColonne(),
            symboleAttendu.c_str(), m_lecteur.getSymbole().getChaine().c_str());
    throw SyntaxeException(messageWhat);
  }
}

void Interpreteur::testerEtAvancer(const string & symboleAttendu) throw (SyntaxeException) {
  // Teste si le symbole courant est égal au symboleAttendu... Si oui, avance, Sinon, lève une exception
  tester(symboleAttendu);
  m_lecteur.avancer();
}

void Interpreteur::erreur(const string & message) const throw (SyntaxeException) {
  // Lève une exception contenant le message et le symbole courant trouvé.
  // Utilisé lorsqu'il y a plusieurs symboles attendus possibles...
  static char messageWhat[256];
  sprintf(messageWhat,
          "Ligne %d, Colonne %d - Erreur de syntaxe - %s - Symbole trouvé : %s",
          m_lecteur.getLigne(), m_lecteur.getColonne(), message.c_str(), m_lecteur.getSymbole().getChaine().c_str());
  throw SyntaxeException(messageWhat);
}

Noeud* Interpreteur::programme() {
  // <programme> ::= procedure principale() <seqInst> finproc FIN_FICHIER
  testerEtAvancer("principale");
  m_procActuelle = "principale";
  testerEtAvancer("(");
  testerEtAvancer(")");
  Noeud* sequence = seqInst();
  if(m_lecteur.getSymbole() == "finproc"){
      testerEtAvancer("finproc");
      tester("<FINDEFICHIER>");
  }
  if(m_comptErr > 0){
      cout << "Nombre d'erreur trouvé : "<< m_comptErr << endl;
      return nullptr;
  }
  return sequence;
}

Noeud* Interpreteur::seqInst() {
  // <seqInst> ::= <inst> { <inst> }
  NoeudSeqInst* sequence = new NoeudSeqInst();
      do {
          TRY(sequence->ajoute(inst());)
      } while (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "appel" || m_lecteur.getSymbole() == "si" || m_lecteur.getSymbole() == "tantque" || m_lecteur.getSymbole() == "repeter" || m_lecteur.getSymbole() == "pour" || m_lecteur.getSymbole() == "ecrire" || m_lecteur.getSymbole() == "lire");
  // Tant que le symbole courant est un début possible d'instruction...
  // Il faut compléter cette condition chaque fois qu'on rajoute une nouvelle instruction
  return sequence;
}

Noeud* Interpreteur::inst() {
  // <inst> ::= <affectation>  ; | <instSi>
        string proc = "";
    try{
        
        if (m_lecteur.getSymbole() == "<VARIABLE>") {
            Noeud *affect = affectation();
            testerEtAvancer(";");
            return affect;
        }
        
        else if(m_lecteur.getSymbole() == "si")return instSiRiche();
        else if(m_lecteur.getSymbole() == "tantque")return instTantQue();
        else if(m_lecteur.getSymbole() == "repeter")return instRepeter();
        else if(m_lecteur.getSymbole() == "pour")return instPour();  
        else if(m_lecteur.getSymbole() == "ecrire")return instEcrire();
        else if(m_lecteur.getSymbole() == "lire")return instLire();
        else if(m_lecteur.getSymbole() == "procedure")return instProcedure();
        else if(m_lecteur.getSymbole() == "appel")return instAppelProcedure();
        
        else erreur("Instruction incorrecte");
        
    }catch(SyntaxeException e){
      cout << e.what() <<endl;m_comptErr++;
       do {
        m_lecteur.avancer();
      } while (m_lecteur.getSymbole() == "appel" || m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "si" || m_lecteur.getSymbole() == "tantque" || m_lecteur.getSymbole() == "repeter" || m_lecteur.getSymbole() == "pour" || m_lecteur.getSymbole() == "ecrire" || m_lecteur.getSymbole() == "lire");
      return nullptr;
    }
}


Noeud* Interpreteur::affectation() {
  // <affectation> ::= <variable> = <expression> 
  tester("<VARIABLE>");
  Noeud* var = m_table[m_procActuelle].chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table eton la mémorise
  m_lecteur.avancer();
  if(m_lecteur.getSymbole() == "++"){
      m_lecteur.avancer();
      return new NoeudInstIncrementation(var);
  }else if(m_lecteur.getSymbole() == "--"){
      m_lecteur.avancer();
      return new NoeudInstDecrementation(var);
  }else{      
      testerEtAvancer("=");
      Noeud* exp = expression();             // On mémorise l'expression trouvée
      return new NoeudAffectation(var, exp); // On renvoie un noeud affectation
  }
}

Noeud* Interpreteur::expression() {
  // <expression> ::= <facteur> { <opBinaire> <facteur> }
  //  <opBinaire> ::= + | - | *  | / | < | > | <= | >= | == | != | et | ou
  Noeud* fact = facteur();
  Noeud* factDroit;
  while ( m_lecteur.getSymbole() == "+"  || m_lecteur.getSymbole() == "-"  ||
          m_lecteur.getSymbole() == "*"  || m_lecteur.getSymbole() == "/"  ||
          m_lecteur.getSymbole() == "<"  || m_lecteur.getSymbole() == "<=" ||
          m_lecteur.getSymbole() == ">"  || m_lecteur.getSymbole() == ">=" ||
          m_lecteur.getSymbole() == "==" || m_lecteur.getSymbole() == "!=" ||
          m_lecteur.getSymbole() == "et" || m_lecteur.getSymbole() == "ou"   ) {
    Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
    
    //priorité des opérateur, on additione des expressions
    if(m_lecteur.getSymbole() == "+"  || m_lecteur.getSymbole() == "-" || m_lecteur.getSymbole() == "ou"){
        m_lecteur.avancer();
        factDroit = expression(); // On mémorise l'opérande droit
    }else{
        m_lecteur.avancer();
        factDroit = facteur(); // On mémorise l'opérande droit
    }
    fact = new NoeudOperateurBinaire(operateur, fact, factDroit); // Et on construuit un noeud opérateur binaire
  }
  return fact; // On renvoie fact qui pointe sur la racine de l'expression
}

Noeud* Interpreteur::facteur() {
  // <facteur> ::= <entier> | <variable> | - <facteur> | non <facteur> | ( <expression> )
  Noeud* fact = nullptr;
  if (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "<ENTIER>" || m_lecteur.getSymbole() == "<CHAINE>") {
    fact = m_table[m_procActuelle].chercheAjoute(m_lecteur.getSymbole()); // on ajoute la variable ou l'entier à la table
    m_lecteur.avancer();
  } else if(m_lecteur.getSymbole() == "appel" ){
      fact = instAppelFonction();
  } else if (m_lecteur.getSymbole() == "-") { // - <facteur>
    m_lecteur.avancer();
    // on représente le moins unaire (- facteur) par une soustraction binaire (0 - facteur)
    fact = new NoeudOperateurBinaire(Symbole("-"), m_table[m_procActuelle].chercheAjoute(Symbole("0")), facteur());
  } else if (m_lecteur.getSymbole() == "non") { // non <facteur>
    m_lecteur.avancer();
    // on représente le moins unaire (- facteur) par une soustractin binaire (0 - facteur)
    fact = new NoeudOperateurBinaire(Symbole("non"), facteur(), nullptr);
  } else if (m_lecteur.getSymbole() == "(") { // expression parenthésée
    m_lecteur.avancer();
    fact = expression();
    testerEtAvancer(")");
  } else
    TRY(erreur("Facteur incorrect");)
  return fact;
}

Noeud* Interpreteur::instSi() {
  // <instSi> ::= si ( <expression> ) <seqInst> finsi
    Noeud* condition;
    Noeud* sequence;
            
    TRY(testerEtAvancer("si");)
    TRY(testerEtAvancer("(");)
    TRY(condition = expression();) // On mémorise la condition
    TRY(testerEtAvancer(")");)
    sequence = seqInst();     // On mémorise la séquence d'instruction
    TRY(testerEtAvancer("finsi");)
    return new NoeudInstSi(condition, sequence); // Et on renvoie un noeud Instruction Si
}

Noeud* Interpreteur::instTantQue() {
    //<instTantQue> ::=tantque( <expression> )<seqInst> fintantque
    Noeud* condition;
    Noeud* sequence;
    
    TRY(testerEtAvancer("tantque");)
    TRY(testerEtAvancer("(");)
    TRY(condition = expression();)
    TRY(testerEtAvancer(")");)
    sequence = seqInst(); // On mémorise la séquence d'instruction
    TRY(testerEtAvancer("fintantque");)
    return new NoeudInstTantQue(condition,sequence);
}

Noeud* Interpreteur::instSiRiche() {
    vector<Noeud*> conditions;
    vector<Noeud*> sequences;
    
    //si(<expression>) <seqInst> {sinonsi (<expression>) <seqInst>} [sinon <seqInst>] finsi
    TRY(testerEtAvancer("si");)
    TRY(testerEtAvancer("(");)
    TRY(conditions.push_back(expression());)
    TRY(testerEtAvancer(")");)
    sequences.push_back(seqInst());     // On mémorise la séquence d'instruction
    while(m_lecteur.getSymbole() == "sinonsi"){
        m_lecteur.avancer();
        TRY(testerEtAvancer("(");)
        TRY(conditions.push_back(expression());)
        TRY(testerEtAvancer(")");)
        sequences.push_back(seqInst());
    }
    if(m_lecteur.getSymbole() == "sinon"){
        TRY(m_lecteur.avancer();)
        sequences.push_back(seqInst());
    }else if(m_lecteur.getSymbole() != "finsi"){
        try{            
            TRY(erreur("oui");)
        }
        catch(SyntaxeException e){
            cout << e.what() <<endl;m_comptErr++; m_lecteur.avancer();
        }
    }
    TRY(testerEtAvancer("finsi");)
    return new NoeudInstSiRiche(conditions,sequences);
}

Noeud* Interpreteur::instRepeter() {
    //<instRepeter> ::= repeter <seqInst> jusqua (<expression>)
    Noeud* condition;
    Noeud* sequence;
    TRY(testerEtAvancer("repeter");)
    sequence = seqInst(); // On mémorise la séquence d'instruction
    TRY(testerEtAvancer("jusqua");)
    TRY(testerEtAvancer("(");)
    TRY(condition = expression();)
    TRY(testerEtAvancer(")");)
    return new NoeudInstRepeter(condition,sequence);
}

Noeud* Interpreteur::instPour() {
    //<instPour> ::= pour ( [ <affectation ] ; <expression> ; [ <affectation> ] ) <seqInst> finpour
    Noeud* affectation1 = nullptr;
    Noeud* affectation2 = nullptr;
    Noeud* condition;
    Noeud* sequence;
    TRY(testerEtAvancer("pour");)
    TRY(testerEtAvancer("(");)
    if (m_lecteur.getSymbole() != ";") {
//        TRY(affectation1 = affectation();)
        try{
            affectation1 = affectation();
        }catch(SyntaxeException e){
            cout << e.what() <<endl;m_comptErr++;
            m_lecteur.avancer();
        }
    }
    TRY(testerEtAvancer(";");)
        try{
            condition = expression();
        }catch(SyntaxeException e){
            cout << e.what() <<endl;m_comptErr++;
            m_lecteur.avancer();
        }
    TRY(testerEtAvancer(";");)
    if (m_lecteur.getSymbole() != ")") {
        try{
            affectation2 = affectation();
        }catch(SyntaxeException e){
            cout << e.what() <<endl;m_comptErr++;
            m_lecteur.avancer();
        }
    }
    TRY(testerEtAvancer(")");)
    sequence = seqInst();
    TRY(testerEtAvancer("finpour");)    
    return new NoeudInstPour(condition,sequence,affectation1,affectation2);
}

Noeud* Interpreteur::instEcrire() {
    //<instEcrire> ::= ecrire ( <expression> | <chaine> { , <expression> | <chaine> } )
    
    vector<Noeud*> elements;
    
    TRY(testerEtAvancer("ecrire");)
    TRY(testerEtAvancer("(");)
    do{
        if (m_lecteur.getSymbole() == ",") {
            m_lecteur.avancer();
        }
        if(m_lecteur.getSymbole() == "<CHAINE>"){
            elements.push_back(m_table[m_procActuelle].chercheAjoute(m_lecteur.getSymbole()));
            m_lecteur.avancer();
        }else if (m_lecteur.getSymbole() == "<VARIABLE>"){
            try{
                elements.push_back(expression());
            }catch(SyntaxeException e){
                cout << e.what() <<endl;m_comptErr++;
                m_lecteur.avancer();
            }
        }else{
           TRY(erreur("Pas de variable");)
        }
    }while(m_lecteur.getSymbole() == ",");
    TRY(testerEtAvancer(")");)
    return new NoeudInstEcrire(elements);
}

Noeud* Interpreteur::instLire() {
  //<instLire> ::= lire(<variable>{,<variable>})
    vector<Noeud*> variables;
    TRY(testerEtAvancer("lire");)
    TRY(testerEtAvancer("(");)
    do{
       if (m_lecteur.getSymbole() == ",") {
            m_lecteur.avancer();
        } 
       if(m_lecteur.getSymbole() == "<VARIABLE>"){
           TRY(variables.push_back(expression());)
       }
       else{
           TRY(erreur("Pas de variable");)
       }
    }while(m_lecteur.getSymbole() == ",");
    TRY(testerEtAvancer(")");)  
    return new NoeudInstLire(variables);
}
Noeud* Interpreteur::instProcedure() {
  //<instProcedure> ::= procedure  <chaine>(<variable>{,<variable>}) <seqInst> finproc
    vector<Noeud*> procedure;
    Noeud* sequence;
    string nomProcedure;
    testerEtAvancer("procedure");
    if (m_lecteur.getSymbole() != "principale") {
        nomProcedure = m_lecteur.getSymbole().getChaine();
        m_procActuelle = nomProcedure;
        m_lecteur.avancer();
        testerEtAvancer("(");
        while(m_lecteur.getSymbole() == "<VARIABLE>"){
            TRY(procedure.push_back(expression());)
            if(m_lecteur.getSymbole().getChaine() == ",") {
                    m_lecteur.avancer();
            }
        }
        testerEtAvancer(")");
        sequence = seqInst();
        procedure.push_back(sequence);
        testerEtAvancer("finproc");
        if(m_comptErr > 0){
            cout << "Nombre d'erreur trouvé : "<< m_comptErr << endl;
        }
        else {
            m_tableProcedure[nomProcedure] = procedure;
        }
        return sequence;
    }
    else return nullptr;
}

Noeud* Interpreteur::instAppelProcedure() {
  //<instAppelProcedure> ::= appel <chaine>(<variable>{,<variable>})
    TRY(testerEtAvancer("appel");)
    for(auto nom : m_tableProcedure){
        if (nom.first == m_lecteur.getSymbole().getChaine()) {
            string nomProc = m_procActuelle;
            vector<Noeud*> variables;
            vector<string> oldVariables;
            Noeud* sequence;
            
            setProcActuelle(nom.first);
            m_lecteur.avancer();
            
            testerEtAvancer("(");
            int i = 0;
            for(auto elem : nom.second){
                
                if(m_lecteur.getSymbole().getChaine() == ",") {
                    m_lecteur.avancer();
                }
            
                if(m_lecteur.getSymbole() == "<ENTIER>"){
                    int val = stoi(m_lecteur.getSymbole().getChaine());
                    oldVariables.push_back(m_lecteur.getSymbole().getChaine());
                    Noeud* var1 = m_tableProcedure[m_procActuelle][i];
                    setProcActuelle(nomProc);
                    Noeud* exp = expression();
                    variables.push_back(new NoeudAffectation(var1,exp));
                    setProcActuelle(nom.first);
                }
            
                else if(m_lecteur.getSymbole() == "<VARIABLE>"){
                    //affichage php
                    oldVariables.push_back(("$"+m_lecteur.getSymbole().getChaine()));
                    //on recupere la variable
                    Noeud* var1 = m_tableProcedure[m_procActuelle][i];
                    setProcActuelle(nomProc);
                    Noeud* exp = expression();
                    variables.push_back(new NoeudAffectation(var1,exp));
                    setProcActuelle(nom.first);
                }
                
                else sequence = elem;
                i++;
            }
            testerEtAvancer(")");
            
            setProcActuelle(nomProc);
            return new NoeudInstAppelProcedure(variables,oldVariables,sequence,nom.first);
        }
    }
}

Noeud* Interpreteur::instFonction() {
  //<instProcedure> ::= procedure  <chaine>(<variable>{,<variable>}) <seqInst> finproc
    vector<Noeud*> procedure;
    Noeud* sequence;
    string nomProcedure;
    testerEtAvancer("fonction");
    if (m_lecteur.getSymbole() != "principale") {
        nomProcedure = m_lecteur.getSymbole().getChaine();
        m_procActuelle = nomProcedure;
        m_lecteur.avancer();
        testerEtAvancer("(");
        while(m_lecteur.getSymbole() == "<VARIABLE>"){
            TRY(procedure.push_back(expression());)
            if(m_lecteur.getSymbole().getChaine() == ",") {
                    m_lecteur.avancer();
            }
        }
        testerEtAvancer(")");
        sequence = seqInst();
        procedure.push_back(sequence);
        //return
        TRY(testerEtAvancer("return");)
        Noeud* varReturn = expression();
        TRY(testerEtAvancer(";");)
        testerEtAvancer("finproc");
        if(m_comptErr > 0){
            cout << "Nombre d'erreur trouvé : "<< m_comptErr << endl;
        }
        else {
            m_tableProcedure[nomProcedure] = procedure;
            m_tableProcReturn[nomProcedure] = varReturn;
        }
        return sequence;
    }
    else return nullptr;
}



Noeud* Interpreteur::instAppelFonction() {
  //<instAppelProcedure> ::= appel <chaine>(<variable>{,<variable>})
    TRY(testerEtAvancer("appel");)
    for(auto nom : m_tableProcedure){
        if (nom.first == m_lecteur.getSymbole().getChaine()) {
            string nomProc = m_procActuelle;
            vector<Noeud*> variables;
            vector<string> oldVariables;
            Noeud* sequence;
            
            setProcActuelle(nom.first);
            m_lecteur.avancer();
            
            testerEtAvancer("(");
            int i = 0;
            for(auto elem : nom.second){
                
                if(m_lecteur.getSymbole().getChaine() == ",") {
                    m_lecteur.avancer();
                }
            
                if(m_lecteur.getSymbole() == "<ENTIER>"){
                    int val = stoi(m_lecteur.getSymbole().getChaine());
                    oldVariables.push_back(m_lecteur.getSymbole().getChaine());
                    Noeud* var1 = m_tableProcedure[m_procActuelle][i];
                    setProcActuelle(nomProc);
                    Noeud* exp = expression();
                    variables.push_back(new NoeudAffectation(var1,exp));
                    setProcActuelle(nom.first);
                }
            
                else if(m_lecteur.getSymbole() == "<VARIABLE>"){
                    //affichage php
                    oldVariables.push_back(("$"+m_lecteur.getSymbole().getChaine()));
                    //on recupere la variable
                    Noeud* var1 = m_tableProcedure[m_procActuelle][i];
                    setProcActuelle(nomProc);
                    Noeud* exp = expression();
                    variables.push_back(new NoeudAffectation(var1,exp));
                    setProcActuelle(nom.first);
                }
                
                else sequence = elem;
                i++;
            }
            testerEtAvancer(")");
            
            Noeud* varReturn = m_tableProcReturn[m_procActuelle];
            setProcActuelle(nomProc);
            return new NoeudInstAppelFonction(variables,oldVariables,sequence,varReturn,nom.first);
        }
    }
}


void Interpreteur::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    cout << setw(4*indentation) << "" << "<?php" << "\n"; //debut du programme php
    if(getArbreproc().size() > 0)
    cout << "//Declaration des fonctions et procédures\n";
    for(auto proc : getArbreproc()){
            cout << setw(indentation+2) << "" << "function " << proc.first << "(";
            vector<Noeud*> variables = getTableProcedure()[proc.first];
            int i = variables.size();
            for(auto vars : variables){
                if(i > 1){
                    cout << "$" << ((SymboleValue*)vars)->getChaine();
                    if (i > 2) {
                        cout << ", ";
                    }
                    i--;
                }
            }
            cout << "){\n";
            proc.second->traduitEnPHP(cout,indentation+4);
            cout << setw(indentation+2) << "" << "}\n\n";
        
    }   
    cout << "//Début Procedure principale\n";
    getArbre()->traduitEnPHP(cout,indentation+1);//lance l'operation traduitEnPHP sur la racine
    cout << "//Fin Procedure principale\n";
    cout << setw(4*(indentation+1)) << "?>" << "\n";
}




