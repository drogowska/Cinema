#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "model/Seance.h"
#include "model/Hall.h"
#include "model/Movie.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteSeanceFixture {
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
    SeanceType testSeanceType3D = threeD;
    SeanceType testSeanceType2D = twoD;
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);


};

BOOST_FIXTURE_TEST_SUITE(TestSuiteSeance, TestSuiteSeanceFixture)

    BOOST_AUTO_TEST_CASE(SeanceConstrutorTest) {
        Seance s = Seance(testDateAndTime, testSeanceType3D, testMovie, testHall);
        BOOST_TEST(s.getHall() == testHall);
        BOOST_TEST(s.getMovie() == testMovie);
        BOOST_TEST(s.getSeanceType() == testSeanceType3D);
        BOOST_TEST(s.getDateAndTime() == testDateAndTime);

    }
    BOOST_AUTO_TEST_CASE(getExtraPayment3DTest) {
        Seance s = Seance(testDateAndTime, testSeanceType3D, testMovie, testHall);
        BOOST_TEST(s.getExtraPayment() == 3.0);

    }
    BOOST_AUTO_TEST_CASE(getExtraPayment2DTest) {
        Seance s = Seance(testDateAndTime, testSeanceType2D, testMovie, testHall);
        BOOST_TEST(s.getExtraPayment() == 0);
    }

BOOST_AUTO_TEST_SUITE_END()