#include <boost/test/unit_test.hpp>
#include "model/Movie.h"

BOOST_AUTO_TEST_SUITE(TestSuiteMovie)

    BOOST_AUTO_TEST_CASE(MovieConstrutorTest) {
        Movie m = Movie("Titanic", 25);
        BOOST_TEST(m.getTitle() == "Titanic");
        BOOST_TEST(m.getBasePrice() == 25);
    }
    BOOST_AUTO_TEST_CASE(SetBasePriceTest) {
        Movie m = Movie("Titanic", 25);
        m.setBasePrice(20);
        BOOST_TEST(m.getBasePrice() == 20);
    }
BOOST_AUTO_TEST_SUITE_END()