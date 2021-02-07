#include <boost/test/unit_test.hpp>
#include "model/Visitor.h"


BOOST_AUTO_TEST_SUITE(TestSuiteVisitorExeptions)

    BOOST_AUTO_TEST_CASE(CreateVisitorWithInvalidEmail){
        BOOST_CHECK_THROW( Visitor("John","Smith","aaaom.com","1234","123456789",Student,false), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateVisitorWithEmptyPassword){
        BOOST_CHECK_THROW( Visitor("John","Smith","aaaom.com","","123456789",Student,false), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateVisitorWithToShortPassword){
        BOOST_CHECK_THROW( Visitor("John","Smith","aaaom.com","123","123456789",Student,false), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateVisitorWithInvalidPhoneNumber){
        BOOST_CHECK_THROW( Visitor("John","Smith","aaa@com.com","1234","1234516789",Student,false), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(SetInvalidEmail) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW( v.setEmail("aaa"), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(SetInvalidPhoneNumber) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW( v.setPhoneNumber("1"), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(setToShortPassword) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW( v.setPassword("123"), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(setEmptyPassworrd) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW( v.setPhoneNumber(""), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(setTheSamePassword) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW( v.setPassword("1234"), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()