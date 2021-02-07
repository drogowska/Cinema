#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "model/Seance.h"
#include "model/Hall.h"
#include "model/Movie.h"
#include "managers/SeancesManager.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteSeanceFixture {
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
    SeanceType testSeanceType3D = threeD;
    SeanceType testSeanceType2D = twoD;
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteSeancesManagerExceptions, TestSuiteSeanceFixture)

    BOOST_AUTO_TEST_CASE(AddObjetWithInvaidMovie) {
        SeancesManager manager;
        BOOST_CHECK_THROW(manager.addSeance(testDateAndTime, testSeanceType3D, nullptr, testHall), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjetWithInvaidHall) {
        SeancesManager manager;
        BOOST_CHECK_THROW(manager.addSeance(testDateAndTime, testSeanceType3D, testMovie, nullptr), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(RemoveIncorrectObject) {
        SeancesManager manager;
        SeancePtr object = nullptr;
        BOOST_CHECK_THROW(manager.removeSeance(object), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(FindIncorrectObject) {
        SeancesManager manager;
        manager.addSeance(testDateAndTime, testSeanceType3D, testMovie, testHall);
        SeancePredicate p = [](SeancePtr ptr)->bool{
            return( ptr->getSeanceType() == twoD);
        };
        BOOST_CHECK_THROW(manager.find(p), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddSeanceWithoutDateAndTime) {
        SeancesManager manager;
        BOOST_CHECK_THROW(manager.addSeance(pt::not_a_date_time, threeD, testMovie, testHall), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetSeanceWithNegativeIndex) {
        SeancesManager manager;
        BOOST_CHECK_THROW(manager.getSeance(-5), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetIndexFromEmptyObject) {
        SeancesManager manager;
        SeancePtr seance = nullptr;
        BOOST_CHECK_THROW(manager.getIndex(seance), std::logic_error);
    }
BOOST_AUTO_TEST_SUITE_END()
