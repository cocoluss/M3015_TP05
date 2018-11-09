/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass7.cpp
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 5:17:18 PM
 */

#include "newtestclass7.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass7);

newtestclass7::newtestclass7() {
}

newtestclass7::~newtestclass7() {
}

void newtestclass7::setUp() {
}

void newtestclass7::tearDown() {
}

void newtestclass7::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass7::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

