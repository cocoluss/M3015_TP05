/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: first_uno
 *
 * Created on November 8, 2018, 12:00 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Interpreteur.h"

/*
 * Simple C++ Test Suite
 */

void testInterpreteur() {
    ifstream& fichier;
    Interpreteur interpreteur(fichier);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testInterpreteur (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testInterpreteur (newsimpletest)" << std::endl;
    testInterpreteur();
    std::cout << "%TEST_FINISHED% time=0 testInterpreteur (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

