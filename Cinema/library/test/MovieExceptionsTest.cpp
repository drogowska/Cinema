#include <boost/test/unit_test.hpp>
#include "model/Movie.h"

BOOST_AUTO_TEST_SUITE(TestSuiteMovieExceptions)

    BOOST_AUTO_TEST_CASE(CreateMovieWithEmptyTitle) {
        BOOST_CHECK_THROW(Movie("",10), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()
