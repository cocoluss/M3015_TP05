/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass1.cpp
 * Author: lussouc
 *
 * Created on Nov 8, 2018, 6:05:43 PM
 */

#include "newtestclass1.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass1);

newtestclass1::newtestclass1() {
}

newtestclass1::~newtestclass1() {
}

void newtestclass1::setUp() {
}

void newtestclass1::tearDown() {
}

void newtestclass1::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass1::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

