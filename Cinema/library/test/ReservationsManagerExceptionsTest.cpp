#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "model/Reservation.h"
#include "model/Visitor.h"
#include "model/Hall.h"
#include "model/Movie.h"
#include "model/Seance.h"
#include "managers/ReservationsManager.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteReservationManagerExceptionsFixture{
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);
    VisitorPtr testVisitor = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Default,false);
    SeancePtr testSeance = std::make_shared<Seance>(testDateAndTime, threeD, testMovie, testHall);
    int testRow = 12;
    int testSeat = 12;
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteReservationsManagerExceptions, TestSuiteReservationManagerExceptionsFixture)

    BOOST_AUTO_TEST_CASE(AddReservationWithInvaildVisitor) {
        ReservationsManager manager;
        BOOST_CHECK_THROW(  manager.addReservation(nullptr, testSeance, testRow, testSeat), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddReservationWithInvaildSeance) {
        ReservationsManager manager;
        BOOST_CHECK_THROW(  manager.addReservation(testVisitor, nullptr, testRow, testSeat), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(RemoveIncorrectReservation) {
        ReservationsManager manager;
        ReservationPtr object = nullptr;
        BOOST_CHECK_THROW(manager.removeReservation(object), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(FindIncorrectReservation) {
        ReservationsManager manager;
        //manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        ReservationPredicate p = [](ReservationPtr ptr)->bool{
            return( ptr->getRow() == 25);
        };
        BOOST_CHECK_THROW(manager.find(p), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetReservationWithNegativeIndex) {
        ReservationsManager manager;
        BOOST_CHECK_THROW(manager.getReservation(-5), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetIndexFromEmptyObject) {
        ReservationsManager manager;
        ReservationPtr reservation = nullptr;
        BOOST_CHECK_THROW(manager.getIndex(reservation), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(AddReservationOnReservedPlace) {
        ReservationsManager manager;
        manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        BOOST_CHECK_THROW( manager.addReservation(testVisitor, testSeance, testRow, testSeat), std::logic_error);
    }
BOOST_AUTO_TEST_SUITE_END()
