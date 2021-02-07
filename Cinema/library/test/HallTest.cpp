#include <boost/test/unit_test.hpp>
#include "model/Hall.h"

BOOST_AUTO_TEST_SUITE(TestSuiteHall)

    BOOST_AUTO_TEST_CASE(HallConstrutorTest) {
        Hall h = Hall("A01", 35,15);
        BOOST_TEST(h.getHallNumber() == "A01");
        BOOST_TEST(h.getNumberOfSeatInRow() == 15);
        BOOST_TEST(h.getNumberOfRows() == 35);
    }
    BOOST_AUTO_TEST_CASE(SetHallNamePositiveTest) {
        Hall h = Hall("A01", 35,15);
        h.setHallNumber("a01");
        BOOST_TEST(h.getHallNumber() == "a01");

    }
    
BOOST_AUTO_TEST_SUITE_END()