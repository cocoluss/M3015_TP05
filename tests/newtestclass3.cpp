/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass3.cpp
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 1:59:07 PM
 */

#include "newtestclass3.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass3);

newtestclass3::newtestclass3() {
}

newtestclass3::~newtestclass3() {
}

void newtestclass3::setUp() {
}

void newtestclass3::tearDown() {
}

void newtestclass3::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass3::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

