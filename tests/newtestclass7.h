/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass7.h
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 5:17:18 PM
 */

#ifndef NEWTESTCLASS7_H
#define NEWTESTCLASS7_H

#include </Downloads/cppunit-1.12.1/include/cppunit/extensions/HelperMacros.h>

class newtestclass7 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass7);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass7();
    virtual ~newtestclass7();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* NEWTESTCLASS7_H */

