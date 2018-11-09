/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass5.cpp
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 2:37:14 PM
 */

#include "newtestclass5.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass5);

newtestclass5::newtestclass5() {
}

newtestclass5::~newtestclass5() {
}

void newtestclass5::setUp() {
}

void newtestclass5::tearDown() {
}

void newtestclass5::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass5::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

