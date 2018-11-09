/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass4.cpp
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 2:33:26 PM
 */

#include "newtestclass4.h"
#include "Interpreteur.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass4);

newtestclass4::newtestclass4() {
}

newtestclass4::~newtestclass4() {
}

void newtestclass4::setUp() {
}

void newtestclass4::tearDown() {
}

void newtestclass4::testInterpreteur() {
    ifstream& fichier;
    Interpreteur interpreteur(fichier);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

