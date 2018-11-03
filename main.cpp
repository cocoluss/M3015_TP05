#include <iostream>
using namespace std;
#include "Interpreteur.h"
#include "Exceptions.h"

int main(int argc, char* argv[]) {
  string nomFich;
  map<string,TableSymboles> table;
  if (argc != 2) {
    cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl;
    cout << "Entrez le nom du fichier que voulez-vous interpréter : ";
    getline(cin, nomFich);
  } else
    nomFich = argv[1];
  ifstream fichier(nomFich.c_str());
  try {
    Interpreteur interpreteur(fichier);
    interpreteur.analyseproc();
    interpreteur.analyse();
    // Si pas d'exception levée, l'analyse syntaxique a réussi
    cout << endl << "================ Syntaxe Correcte" << endl;
    // On affiche le contenu de la table des symboles avant d'exécuter le programme
    cout << endl << "================ Table des symboles des procédures avant exécution : \n";
    table = interpreteur.getTable();
    for(auto proc : table){
        cout << endl << "================ Table des symboles procédure " << proc.first << " avant exécution : " << proc.second;
    }
    cout << endl << "================ Execution de l'arbre" << endl;
    // On exécute le programme si l'arbre n'est pas vide
    if (interpreteur.getArbre()!=nullptr) interpreteur.getArbre()->executer();
    // Et on vérifie qu'il a fonctionné en regardant comment il a modifié la table des symboles
    table = interpreteur.getTable();
    cout << endl << "================ Table des symboles apres exécution : " << table["principale"];
    cout << endl << "================ Traduction en PHP :" << endl;
    interpreteur.traduitEnPHP(cout,0);
  } catch (InterpreteurException & e) {
    cout << e.what() << endl;
  }
  cout << flush;
  return 0;
}
