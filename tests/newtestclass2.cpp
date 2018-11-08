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


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass2);

newtestclass2::newtestclass2() {
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


