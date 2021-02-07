#include <boost/test/unit_test.hpp>
#include "managers/HallsManager.h"
#include "model/Hall.h"


BOOST_AUTO_TEST_SUITE(TestSuiteHallsManager)

    BOOST_AUTO_TEST_CASE(AddHallPositiveTest) {
        HallsManager manager;
        manager.addHall( "A01", 20, 20);
        HallPtr hall = std::make_shared<Hall>("A01",20,20);
        BOOST_TEST(manager.addHall("A01",20,20), hall);
    }

    BOOST_AUTO_TEST_CASE(RemoveHallPositiveTest){
        HallsManager manager;
        manager.addHall("A01",20,20);
        HallPtr hall = std::make_shared<Hall>("A01",20,20);
        BOOST_TEST(manager.addHall("A01",20,20), hall);
        BOOST_TEST( manager.removeHall(hall), true);
    }
    BOOST_AUTO_TEST_CASE(GetHallPositiveTest) {
        HallsManager manager;
        manager.addHall("A01",20,20);
        HallPtr hall = std::make_shared<Hall>("A01",20,20);
        BOOST_TEST(manager.getHall("A01"), hall);
    }
    BOOST_AUTO_TEST_CASE(FindHallTest) {
        HallsManager manager;
        HallPtr hall = manager.addHall("A01",20,20);
        HallPredicate p = [](HallPtr ptr)->bool{
            return( ptr->getHallNumber() == "A01");
        };
        BOOST_TEST(manager.find(p), hall);
    }
    BOOST_AUTO_TEST_CASE(FindAllHallsTest) {
        HallsManager manager;
        HallPtr hall = manager.addHall("A01",20,20);
        HallPtr hall1 = manager.addHall("B02",20,10);
        HallPredicate p = [](HallPtr ptr)->bool{
            return( ptr->getNumberOfRows() == 20);
        };
        std::vector<HallPtr> result = manager.findAll(p);
        std::vector<HallPtr> r;
        r.push_back(hall);
        r.push_back(hall1);
        BOOST_CHECK(result == r);
    }
    BOOST_AUTO_TEST_CASE(GetHallFromIndexTest) {
        HallsManager manager;
        HallPtr hall = manager.addHall("A01",20,20);
        BOOST_TEST(manager.getHall(0), hall);
    }
    BOOST_AUTO_TEST_CASE(SizeTest) {
        HallsManager manager;
        HallPtr hall = manager.addHall("A01",20,20);
        BOOST_TEST(manager.size(), 1);
    }
    BOOST_AUTO_TEST_CASE(GetIndexTest) {
        HallsManager manager;
        HallPtr hall = manager.addHall("A01",20,20);
        BOOST_CHECK_EQUAL(manager.getIndex(hall), 0);
    }
BOOST_AUTO_TEST_SUITE_END()
