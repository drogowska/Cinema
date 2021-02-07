#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "model/Reservation.h"
#include "model/Visitor.h"
#include "model/Hall.h"
#include "model/Movie.h"
#include "model/Seance.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteReservationExceptionsFixture{
    int testRow = 12;
    int testSeat = 12;
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 37,15);
    VisitorPtr testVisitor = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Default,false);
    SeancePtr testSeance = std::make_shared<Seance>(testDateAndTime, threeD, testMovie, testHall);
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteReservationExceptions, TestSuiteReservationExceptionsFixture)

    BOOST_AUTO_TEST_CASE(CreateReservationWithWrongVisitor) {
        BOOST_CHECK_THROW(  Reservation(nullptr, testSeance, testRow, 45), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateReservationWithWrongSeance) {
        BOOST_CHECK_THROW(  Reservation(testVisitor, nullptr, testRow, 45), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateReservationWithWrongRow) {
        BOOST_CHECK_THROW(  Reservation(testVisitor, testSeance, 44, testSeat), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(CreateReservationWithWrongSeat) {
        BOOST_CHECK_THROW(  Reservation(testVisitor, testSeance, testRow, 45), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()
