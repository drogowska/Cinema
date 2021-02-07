#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "model/Reservation.h"
#include "model/Visitor.h"
#include "model/Hall.h"
#include "model/Movie.h"
#include "model/Seance.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteReservationFixture{
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);
    VisitorPtr testVisitorStudent = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Student,false);
    VisitorPtr testVisitorDefault = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Default,false);
    VisitorPtr testVisitorKid = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Kid,false);
    VisitorPtr testVisitorSenior = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Senior,false);
    SeancePtr testSeance = std::make_shared<Seance>(testDateAndTime, threeD, testMovie, testHall);
    int testRow = 12;
    int testSeat = 12;
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteReservation, TestSuiteReservationFixture)

    BOOST_AUTO_TEST_CASE(ReservationConstrutorTest) {
        Reservation r = Reservation(testVisitorStudent, testSeance, testRow, testSeat);
        BOOST_TEST(r.getVisitor() == testVisitorStudent);
        BOOST_TEST(r.getSeance() == testSeance);
        BOOST_TEST(r.getRow() == testRow);
        BOOST_TEST(r.getSeat() == testSeat);
    }
    
    BOOST_AUTO_TEST_CASE(getActualPricerTestForStudentVisitor, *boost::unit_test::tolerance(0.0001)) {
        Reservation r = Reservation(testVisitorStudent, testSeance, testRow, testSeat);
        BOOST_CHECK_CLOSE(r.getActualPrice(), 16.80, 0.001);
    }
    BOOST_AUTO_TEST_CASE(getActualPricerTestForKidVisitor, *boost::unit_test::tolerance(0.0001)) {
        Reservation r = Reservation(testVisitorKid, testSeance, testRow, testSeat);
        BOOST_CHECK_CLOSE(r.getActualPrice(), 14.00, 0.001);
    }
    BOOST_AUTO_TEST_CASE(getActualPricerTestForSeniorVisitor, *boost::unit_test::tolerance(0.0001)) {
        Reservation r = Reservation(testVisitorSenior, testSeance, testRow, testSeat);
        BOOST_CHECK_CLOSE(r.getActualPrice(), 19.60, 0.001);
    }
    BOOST_AUTO_TEST_CASE(getActualPricerTestForDefaultVisitor, *boost::unit_test::tolerance(0.0001)) {
        Reservation r = Reservation(testVisitorDefault, testSeance, testRow, testSeat);
        BOOST_CHECK_CLOSE(r.getActualPrice(), 28.00, 0.001);
    }

BOOST_AUTO_TEST_SUITE_END()