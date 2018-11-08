/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass2.h
 * Author: lussouc
 *
 * Created on Nov 8, 2018, 6:06:21 PM
 */

#ifndef NEWTESTCLASS2_H
#define NEWTESTCLASS2_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass2 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass2);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass2();
    virtual ~newtestclass2();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* NEWTESTCLASS2_H */

