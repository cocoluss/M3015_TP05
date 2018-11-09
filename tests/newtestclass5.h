/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass5.h
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 2:37:14 PM
 */

#ifndef NEWTESTCLASS5_H
#define NEWTESTCLASS5_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass5 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass5);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass5();
    virtual ~newtestclass5();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* NEWTESTCLASS5_H */

