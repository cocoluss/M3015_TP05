/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass2.cpp
 * Author: lussouc
 *
 * Created on Nov 8, 2018, 6:06:21 PM
 */

#include "newtestclass2.h"
#include <iostream>
#include <string>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass2);

newtestclass2::newtestclass2() {
    ifstream fichier("CPPUNIT.txt");
    Interpreteur interpreteur(fichier);
    interpreteur.analyseproc();
    interpreteur.analyse();
    TableSymboles tablesymboles = interpreteur.getTable()["principale"]; 
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("test j = 4", tablesymboles.chercheAjoute(Symbole("j"))->executer() == 4);
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("test o = 8", tablesymboles.chercheAjoute(Symbole("o"))->executer() == 8);
    
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("test k = j+o", tablesymboles.chercheAjoute(Symbole("k"))->executer() == 12);
    
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("test repeter i = 200", tablesymboles.chercheAjoute(Symbole("i"))->executer() == 200);
    
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("test si d = 1", tablesymboles.chercheAjoute(Symbole("d"))->executer() == 1);
      
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("test tantque b = 11", tablesymboles.chercheAjoute(Symbole("b"))->executer() == 11);
    
    ifstream fichier2("test_Erreur.txt");
    Interpreteur interpreteur2(fichier2);
    interpreteur2.analyseproc();

    CPPUNIT_ASSERT_THROW_MESSAGE("test erreur", interpreteur2.analyse(), char*);
    
}

newtestclass2::~newtestclass2() {
}

void newtestclass2::setUp() {
}

void newtestclass2::tearDown() {
}

void newtestclass2::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass2::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}


