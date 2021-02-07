#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "model/Movie.h"
#include "model/Seance.h"
#include "model/Hall.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
struct TestSuiteMovieExceptionsFixture {
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
    SeanceType testSeanceType= threeD;
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);

};
BOOST_FIXTURE_TEST_SUITE(TestSuiteSeanceExeptions,TestSuiteMovieExceptionsFixture)

    BOOST_AUTO_TEST_CASE(CreateSeanceWithoutDateAndTime) {
        BOOST_CHECK_THROW(Seance(pt::not_a_date_time, testSeanceType, testMovie, testHall), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateSeanceWithoutHall) {
        BOOST_CHECK_THROW(Seance(testDateAndTime, testSeanceType, testMovie, nullptr), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateSeanceWithoutMovie) {
        BOOST_CHECK_THROW(Seance(testDateAndTime, testSeanceType,nullptr, testHall), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()