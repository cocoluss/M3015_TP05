/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass6.h
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 2:53:26 PM
 */

#ifndef NEWTESTCLASS6_H
#define NEWTESTCLASS6_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass6 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass6);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass6();
    virtual ~newtestclass6();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* NEWTESTCLASS6_H */

