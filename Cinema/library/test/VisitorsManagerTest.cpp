#include <boost/test/unit_test.hpp>
#include "managers/VisitorsManager.h"
#include "model/Visitor.h"

#include <boost/uuid/uuid_io.hpp>


BOOST_AUTO_TEST_SUITE(TestSuiteVisitorsManager)

    BOOST_AUTO_TEST_CASE(AddVisitorPositiveTest) {
        VisitorsManager manager;
        VisitorPtr visitor1 =manager.addVisitor("John","Smith","bbb@com","1234","123456789",Default,false);
        VisitorPtr visitor = std::make_shared<Visitor>("John","Smith","bbb@com","1234","123456789",Default,false);
        BOOST_TEST(visitor1, visitor);
    }

    BOOST_AUTO_TEST_CASE(RemoveVisitorPositiveTest){
        VisitorsManager manager;
        VisitorPtr visitor1 =manager.addVisitor("John","Smith","bbb@com","1234","123456789",Default,false);
        VisitorPtr visitor = std::make_shared<Visitor>("John","Smith","bbb@com","1234","123456789",Default,false);
        BOOST_TEST(visitor1, visitor);
        BOOST_TEST( manager.removeVisitor(visitor), true);
    }
    BOOST_AUTO_TEST_CASE(GetVisitorPositiveTest) {
        VisitorsManager manager;
        VisitorPtr v = manager.addVisitor("John","Smith","aaa@com","1234","123456789",Default,false);
        VisitorPtr visitor = std::make_shared<Visitor>("John","Smith","aaa@com","1234","123456789",Default,false);
        boost :: uuids ::uuid id = v->getId();
        BOOST_TEST(manager.getVisitor(id), visitor);
    }
    BOOST_AUTO_TEST_CASE(FindVisitorTest) {
        VisitorsManager manager;
        VisitorPtr visitor = manager.addVisitor("John","Smith","aaa@com","1234","123456789",Default,false);
        VisitorPredicate p = [](VisitorPtr ptr)->bool{
            return( ptr->getFirstName() == "John");
        };
        BOOST_TEST(manager.find(p), visitor);
    }
    BOOST_AUTO_TEST_CASE(FindAllVisitorsTest) {
        VisitorsManager manager;
        VisitorPtr visitor1 = manager.addVisitor("John","Smith","aaa@com","1234","123456789",Default,false);
        VisitorPtr visitor2 = manager.addVisitor("Bob","Smith","bbb@com","1234","987564321",Default,false);
        VisitorPredicate p = [](VisitorPtr ptr)->bool{
            return( ptr->getLastName() == "Smith");
        };
        std::vector<VisitorPtr> result = manager.findAll(p);
        std::vector<VisitorPtr> v;
        v.push_back(visitor1);
        v.push_back(visitor2);
        BOOST_CHECK(result == v);
    }
    BOOST_AUTO_TEST_CASE(GetReservationFromIndexTest) {
        VisitorsManager manager;
        VisitorPtr visitor = manager.addVisitor("John","Smith","aaa@com","1234","123456789",Default,false);
        BOOST_TEST(manager.getVisitor(0), visitor);
    }
    BOOST_AUTO_TEST_CASE(SizeTest) {
        VisitorsManager manager;
        VisitorPtr visitor = manager.addVisitor("John","Smith","aaa@com","1234","123456789",Default,false);
        BOOST_TEST(manager.size(), 1);
    }
    BOOST_AUTO_TEST_CASE(GetIndexTest) {
        VisitorsManager manager;
        VisitorPtr visitor = manager.addVisitor("John","Smith","aaa@com","1234","123456789",Default,false);
        BOOST_CHECK_EQUAL(manager.getIndex(visitor), 0);
    }
BOOST_AUTO_TEST_SUITE_END()
