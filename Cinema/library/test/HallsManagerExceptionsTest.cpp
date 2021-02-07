#include <boost/test/unit_test.hpp>
#include "managers/HallsManager.h"
#include "model/Hall.h"

BOOST_AUTO_TEST_SUITE(TestSuiteHallsManagersExceptions)

    BOOST_AUTO_TEST_CASE(RemoveIncorrectObject) {
        HallsManager manager;
        HallPtr object = nullptr;
        manager.addHall("A01",10,10);
        BOOST_CHECK_THROW(manager.removeHall(object), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(FindIncorrectObject) {
        HallsManager manager;
        manager.addHall("A01",10,10);
        HallPredicate p = [](HallPtr ptr)->bool{
               return( ptr->getHallNumber() == "a");
        };
        BOOST_CHECK_THROW(manager.find(p), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithEmptyObject) {
        HallsManager manager;
        BOOST_CHECK_THROW(manager.addHall("", 10,10), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetObjectWithEmptyHallName) {
        HallsManager manager;
        manager.addHall("A01",10,10);
        BOOST_CHECK_THROW(manager.getHall(""), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetHallWithNegativeIndex) {
        HallsManager manager;
        BOOST_CHECK_THROW(manager.getHall(-5), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetIndexFromEmptyObject) {
        HallsManager manager;
        HallPtr hall = nullptr;
        BOOST_CHECK_THROW(manager.getIndex(hall), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()
