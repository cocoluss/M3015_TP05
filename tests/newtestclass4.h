/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass4.h
 * Author: first_uno
 *
 * Created on Nov 8, 2018, 2:33:26 PM
 */

#ifndef NEWTESTCLASS4_H
#define NEWTESTCLASS4_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass4 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass4);

    CPPUNIT_TEST(testInterpreteur);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass4();
    virtual ~newtestclass4();
    void setUp();
    void tearDown();

private:
    void testInterpreteur();

};

#endif /* NEWTESTCLASS4_H */

