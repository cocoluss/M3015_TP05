#include <stdlib.h>
#include <typeinfo>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : m_instructions() {
}

int NoeudSeqInst::executer() {
  for (unsigned int i = 0; i < m_instructions.size(); i++)
    m_instructions[i]->executer(); // on exécute chaque instruction de la séquence
  return 0; // La valeur renvoyée ne représente rien !
}

void NoeudSeqInst::ajoute(Noeud* instruction) {
  if (instruction!=nullptr) m_instructions.push_back(instruction);
}

void NoeudSeqInst::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    for (unsigned int i = 0; i < m_instructions.size(); i++){
        m_instructions[i]->traduitEnPHP(cout,indentation+1);
        if(typeid(*m_instructions[i]) != typeid(NoeudInstTantQue)){    
            cout << ";" << endl;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

int NoeudAffectation::executer() {
  int valeur = m_expression->executer(); // On exécute (évalue) l'expression
  ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
  return 0; // La valeur renvoyée ne représente rien !
}

void NoeudAffectation::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    cout<< setw(2*indentation) << "$" << ((SymboleValue*)m_variable)->getChaine() << " = " ;
    m_expression->traduitEnPHP(cout,0);
//    cout << ";" << endl;
}


////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit)
: m_operateur(operateur), m_operandeGauche(operandeGauche), m_operandeDroit(operandeDroit) {
}

int NoeudOperateurBinaire::executer() {
  int og, od, valeur;
  if (m_operandeGauche != nullptr) og = m_operandeGauche->executer(); // On évalue l'opérande gauche
  if (m_operandeDroit != nullptr) od = m_operandeDroit->executer(); // On évalue l'opérande droit
  // Et on combine les deux opérandes en fonctions de l'opérateur
  if (this->m_operateur == "+") valeur = (og + od);
  else if (this->m_operateur == "-") valeur = (og - od);
  else if (this->m_operateur == "*") valeur = (og * od);
  else if (this->m_operateur == "==") valeur = (og == od);
  else if (this->m_operateur == "!=") valeur = (og != od);
  else if (this->m_operateur == "<") valeur = (og < od);
  else if (this->m_operateur == ">") valeur = (og > od);
  else if (this->m_operateur == "<=") valeur = (og <= od);
  else if (this->m_operateur == ">=") valeur = (og >= od);
  else if (this->m_operateur == "et") valeur = (og && od);
  else if (this->m_operateur == "ou") valeur = (og || od);
  else if (this->m_operateur == "non") valeur = (!og);
  else if (this->m_operateur == "/") {
    if (od == 0) throw DivParZeroException();
    valeur = og / od;
  }
  return valeur; // On retourne la valeur calculée
}

void NoeudOperateurBinaire::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    string op1 = "";
    string op2 = "";
    string oper;
    //operante gauche
    if(*((SymboleValue*)m_operandeGauche) == "<VARIABLE>"){
        op1 = "$" ;
        ((SymboleValue*)m_operandeGauche)->traduitEnPHP(cout,0);
    }else if(*((SymboleValue*)m_operandeGauche) == "<CHAINE>"){
        op1 = ((SymboleValue*)m_operandeGauche)->getChaine();
        op1.erase(op1.size()-1,1);
        op1.erase(0,1);
        op1 = "$" + op1;
    }else if(*((SymboleValue*)m_operandeGauche) == "<ENTIER>"){
        op1 = ((SymboleValue*)m_operandeGauche)->getChaine();
    }else if(((SymboleValue*)m_operandeGauche) == nullptr){
        op1 = "";
    }else{
        ((SymboleValue*)m_operandeGauche)->traduitEnPHP(cout,0);
    }
    cout << op1;
    //operateur
    if (this->m_operateur == "et") oper = "&&";
    else if (this->m_operateur == "ou") oper = "||";
    else if (this->m_operateur == "non") oper = "!";
    else oper = this->m_operateur.getChaine();
    cout << oper;
    //operante droite
    if(*((SymboleValue*)m_operandeDroit) == "<VARIABLE>"){
        op2 = "$" + ((SymboleValue*)m_operandeDroit)->getChaine();
    }else if(*((SymboleValue*)m_operandeDroit) == "<CHAINE>"){
        op2 = ((SymboleValue*)m_operandeDroit)->getChaine();
        op2.erase(op2.size()-1,1);
        op2.erase(0,1);
        op2 = "$" + op2;
    }else if(*((SymboleValue*)m_operandeDroit) == "<ENTIER>"){
        op2 = ((SymboleValue*)m_operandeDroit)->getChaine();
    }else if(((SymboleValue*)m_operandeDroit) == nullptr){
        op2 = "";
    }else{
        ((SymboleValue*)m_operandeDroit)->traduitEnPHP(cout,0);
    }
    cout << op2;
    
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSi::NoeudInstSi(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}



int NoeudInstSi::executer() {
  if (m_condition->executer()) m_sequence->executer();
  return 0; // La valeur renvoyée ne représente rien !
}



////////////////////////////////////////////////////////////////////////////////
// NoeudInstTantQue
////////////////////////////////////////////////////////////////////////////////

NoeudInstTantQue::NoeudInstTantQue(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstTantQue::executer() {
    while(m_condition->executer()){
        m_sequence->executer();
    }
    return 0;
}

void NoeudInstTantQue::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    cout << setw(2*indentation) << "" << "while(";
    m_condition->traduitEnPHP(cout, 0);
    cout << setw(2*indentation) << ") {"<<endl;
    m_sequence->traduitEnPHP(cout, indentation+1);
    cout << setw(2*indentation) << "" << "}" << endl;
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstSiRiche
////////////////////////////////////////////////////////////////////////////////

NoeudInstSiRiche::NoeudInstSiRiche(vector<Noeud*> conditions, vector<Noeud*> sequences)
: m_conditions(conditions), m_sequences(sequences) {
}

int NoeudInstSiRiche::executer() {
    bool checkExe = false;
    for(int i = 0; i < m_conditions.size(); i++){
        if(m_conditions[i]->executer() && !checkExe){
            checkExe = true;
            m_sequences[i]->executer();
        }
    }
    if(m_conditions.size() != m_sequences.size() && !checkExe){ 
        m_sequences[m_sequences.size()-1]->executer();
    }
}

void NoeudInstSiRiche::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    cout << setw(2*indentation) << "" << "if(";
    m_conditions[0]->traduitEnPHP(cout, 0);
    cout << "){" << endl;
    m_sequences[0]->traduitEnPHP(cout, indentation+1);
    cout << setw(2*indentation) << "" << "}" << endl;
    for(int i = 1; i < m_conditions.size(); i++){
        cout << setw(2*indentation) << "" << "else if(";
        m_conditions[i]->traduitEnPHP(cout, 0);
        cout << "){" << endl;
        m_sequences[i]->traduitEnPHP(cout, indentation+1);
        cout << setw(2*indentation) << "" << "}" << endl;
    }
    if(m_conditions.size() != m_sequences.size()){ 
        cout << setw(2*indentation) << "" << "else{" << endl;
        m_sequences[m_sequences.size()-1]->traduitEnPHP(cout, indentation+1);
        cout << setw(2*indentation) << "" << "}" << endl;
    }
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstRepeter
////////////////////////////////////////////////////////////////////////////////

NoeudInstRepeter::NoeudInstRepeter(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence){
}

int NoeudInstRepeter::executer() {
    do {
        m_sequence->executer();
    } while (m_condition->executer());
}

void NoeudInstRepeter::traduitEnPHP(ostream& cout, unsigned int indentation) const {
    cout << setw(2*indentation) << "" << "do{";
    m_sequence->traduitEnPHP(cout, indentation+1);
    cout << setw(2*indentation) << "" << "}while(";
    m_condition->traduitEnPHP(cout, 0);
    cout << setw(2*indentation) << ")" << endl;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstPour
////////////////////////////////////////////////////////////////////////////////

NoeudInstPour::NoeudInstPour(Noeud* condition, Noeud* sequence, Noeud* affection1, Noeud* affection2)
: m_condition(condition), m_sequence(sequence), m_affectation1(affection1), m_affectation2(affection2){
}

int NoeudInstPour::executer() {
    if (m_affectation1 == nullptr && m_affectation2 == nullptr) {
        for(;m_condition->executer();){
            m_sequence->executer();
        }
    }
    else if (m_affectation1 != nullptr && m_affectation2 == nullptr) {
        for(m_affectation1->executer(); m_condition->executer();){
            m_sequence->executer();
        }
    }
    
    else if (m_affectation1 == nullptr && m_affectation2 != nullptr) {
        for(;m_condition->executer(); ){
            m_sequence->executer();
            m_affectation2->executer();
        }
    }
    else {
        for(m_affectation1->executer(); m_condition->executer();){
            m_sequence->executer();
            m_affectation2->executer();
        }
    }
    
}

void NoeudInstPour::traduitEnPHP(ostream& cout, unsigned int indentation) const {
        
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstEcrire
////////////////////////////////////////////////////////////////////////////////

NoeudInstEcrire::NoeudInstEcrire(vector<Noeud*> elements) 
: m_elems(elements){
}

int NoeudInstEcrire::executer() {
    Noeud* e;
    string s;
    for(auto e : m_elems){
        if(typeid(*e)==typeid(SymboleValue) && *((SymboleValue*)e)== "<CHAINE>"){
            s = ((SymboleValue*)e)->getChaine();
            s.erase(s.size()-1,1);
            s.erase(0,1);
            cout << s;
        }
        else{
            cout << e->executer();
        }
    }
    cout << endl;
}

void NoeudInstEcrire::traduitEnPHP(ostream& cout, unsigned int indentation) const {

}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstLire
////////////////////////////////////////////////////////////////////////////////

NoeudInstLire::NoeudInstLire(vector<Noeud*> variables)
: m_vars(variables){
}

int NoeudInstLire::executer() {
    Noeud* var;
    int n;
    for(auto var : m_vars){
        cin >> n;
        ((SymboleValue*)var)->setValeur(n);
    }
    
}

void NoeudInstLire::traduitEnPHP(ostream& cout, unsigned int indentation) const {

}

void NoeudInstSi::traduitEnPHP(ostream& cout, unsigned int indentation) const {

}






