/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass6.cpp
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 2:53:26 PM
 */

#include "newtestclass6.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass6);

newtestclass6::newtestclass6() {
}

newtestclass6::~newtestclass6() {
}

void newtestclass6::setUp() {
}

void newtestclass6::tearDown() {
}

void newtestclass6::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass6::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

