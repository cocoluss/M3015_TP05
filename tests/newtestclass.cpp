/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.cpp
 * Author: bohrerl
 *
 * Created on Nov 8, 2018, 2:19:18 PM
 */

#include "newtestclass.h"
#include "Interpreteur.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testInterpreteur() {
    ifstream& fichier;
    Interpreteur interpreteur(fichier);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

