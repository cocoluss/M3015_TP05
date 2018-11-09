/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass3.h
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 1:59:07 PM
 */

#ifndef NEWTESTCLASS3_H
#define NEWTESTCLASS3_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass3 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass3);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass3();
    virtual ~newtestclass3();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* NEWTESTCLASS3_H */

