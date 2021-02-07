#include <boost/test/unit_test.hpp>
#include "model/Hall.h"

BOOST_AUTO_TEST_SUITE(TestSuiteHallExceptions)

    BOOST_AUTO_TEST_CASE(CreateHallWithEmptyHallNumber) {
        BOOST_CHECK_THROW(Hall("", 35,15);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(SetHallNameEmpty) {
        Hall h = Hall("A01", 35,15);
        BOOST_CHECK_THROW(h.setHallNumber(""), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()