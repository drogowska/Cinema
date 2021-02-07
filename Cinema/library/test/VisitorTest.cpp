#include <boost/test/unit_test.hpp>
#include "model/Visitor.h"

BOOST_AUTO_TEST_SUITE(TestSuiteVistor)

    BOOST_AUTO_TEST_CASE(VisitorConstrutorTest) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_TEST("John" == v.getFirstName());
        BOOST_TEST("Smith" == v.getLastName());
        BOOST_TEST("123456789" == v.getPhoneNumber());
        BOOST_TEST(Student == v.getDiscountType());
        BOOST_TEST(false == v.isWorker());
        BOOST_TEST("1234" == v.getPassword());
        BOOST_TEST("aaa@com.com" == v.getEmail());
    }

    BOOST_AUTO_TEST_CASE(setEmailPositiveTest) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        v.setEmail("bbb@com.pl");
        BOOST_TEST(v.getEmail() == "bbb@com.pl");
    }
    BOOST_AUTO_TEST_CASE(setPhoneNumberPositiveTest) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        v.setPhoneNumber("111111111");
        BOOST_TEST(v.getPhoneNumber() == "111111111");
    }
    BOOST_AUTO_TEST_CASE(setPasswordPositiveTest) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        v.setPassword("qazwsx");
        BOOST_TEST(v.getPassword() == "qazwsx");
    }
    BOOST_AUTO_TEST_CASE(setWorkerTest) {
        Visitor v= Visitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        v.setWorker(true);
        BOOST_TEST(v.isWorker() == true);
    }

BOOST_AUTO_TEST_SUITE_END()
