#include <boost/test/unit_test.hpp>
#include "managers/VisitorsManager.h"

BOOST_AUTO_TEST_SUITE(TestSuiteVisitorsManagerExceptions)

    BOOST_AUTO_TEST_CASE(AddObjectWithEmptyFirstName) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.addVisitor("","Smith","aaa@com.com","1234","123456789",Student,false);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithEmptyPassword) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.addVisitor("John","Smith","aaa@com.com","","123456789",Student,false);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithToShortPassword) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.addVisitor("John","Smith","aaa@com.com","12","123456789",Student,false);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithEmptyLastName) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.addVisitor("John","","aaa@com.com","1234","123456789",Student,false);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithIncorrcetEmail) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.addVisitor("John","Smith","aaacom.com","1234","123456789",Student,false);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithIncorrcetPhoneNumber) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.addVisitor("John","Smith","aaa@com.com","1234","12345678",Student,false);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddObjectWithSameEmail) {
        VisitorsManager manager;
        manager.addVisitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW(  manager.addVisitor("John","Smith","aaa@com.com","1234","123456789",Student,false), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(RemoveIncorrectObject) {
        VisitorsManager manager;
        VisitorPtr object = nullptr;
        manager.addVisitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        BOOST_CHECK_THROW(manager.removeVisitor(object), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(FindIncorrectObject) {
        VisitorsManager manager;
        manager.addVisitor("John","Smith","aaa@com.com","1234","123456789",Student,false);
        VisitorPredicate p = [](VisitorPtr ptr)->bool{
            return( ptr->getFirstName() == "a");
        };
        BOOST_CHECK_THROW(manager.find(p), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetVisitorWithNegativeIndex) {
        VisitorsManager manager;
        BOOST_CHECK_THROW(manager.getVisitor(-5), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetIndexFromEmptyObject) {
        VisitorsManager manager;
        VisitorPtr visitor = nullptr;
        BOOST_CHECK_THROW(manager.getIndex(visitor), std::logic_error);
    }
BOOST_AUTO_TEST_SUITE_END()