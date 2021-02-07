#include <boost/test/unit_test.hpp>
#include "managers/SeancesManager.h"
#include "model/Seance.h"
#include "model/Movie.h"
#include "model/Hall.h"


namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteSeancesManagerFixture {
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
    SeanceType testSeanceType = threeD;
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);


};


BOOST_FIXTURE_TEST_SUITE(TestSuiteSeancesManager, TestSuiteSeancesManagerFixture)

    BOOST_AUTO_TEST_CASE(AddSeancePositiveTest) {
        SeancesManager manager;
        SeancePtr seance1 = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        SeancePtr seance = std::make_shared<Seance>(testDateAndTime, testSeanceType, testMovie, testHall);
        BOOST_TEST(seance1, seance);
    }

    BOOST_AUTO_TEST_CASE(RemoveSeancePositiveTest){
        SeancesManager manager;
        SeancePtr seance = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        BOOST_TEST( manager.removeSeance(seance), true);
    }
    BOOST_AUTO_TEST_CASE(GetSeancePositiveTest) {
        SeancesManager manager;
        SeancePtr seance = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        boost::uuids::uuid id = seance->getId();
        BOOST_TEST(manager.getSeance(id), seance);
    }
    BOOST_AUTO_TEST_CASE(FindSeanceTest) {
        SeancesManager manager;
        SeancePtr seance = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        SeancePredicate p = [](SeancePtr ptr)->bool{
            return( ptr->getSeanceType() == threeD);
        };
        BOOST_TEST(manager.find(p), seance);
    }
    BOOST_AUTO_TEST_CASE(FindAllSeancesTest) {
        SeancesManager manager;
        SeancePtr seance1 = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        SeancePtr seance2= manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        SeancePredicate p = [](SeancePtr ptr)->bool{
            return( ptr->getSeanceType() == threeD);
        };
        std::vector<SeancePtr> result = manager.findAll(p);
        std::vector<SeancePtr> m;
        m.push_back(seance1);
        m.push_back(seance2);
        BOOST_CHECK(result == m);
    }
    BOOST_AUTO_TEST_CASE(GetSeanceFromIndexTest) {
        SeancesManager manager;
        SeancePtr seance = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        BOOST_TEST(manager.getSeance(0), seance);
    }
    BOOST_AUTO_TEST_CASE(SizeTest) {
        SeancesManager manager;
        SeancePtr seance = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        BOOST_TEST(manager.size(), 1);
    }
    BOOST_AUTO_TEST_CASE(GetIndexTest) {
        SeancesManager manager;
        SeancePtr seance = manager.addSeance(testDateAndTime, testSeanceType, testMovie, testHall);
        BOOST_CHECK_EQUAL(manager.getIndex(seance), 0);
    }

BOOST_AUTO_TEST_SUITE_END()
