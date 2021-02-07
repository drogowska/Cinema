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

struct TestSuiteReservationManagerFixture{
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);
    VisitorPtr testVisitor = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Default,false);
    SeancePtr testSeance = std::make_shared<Seance>(testDateAndTime, threeD, testMovie, testHall);
    int testRow = 12;
    int testSeat = 12;
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));

};



BOOST_FIXTURE_TEST_SUITE(TestSuiteReservationsManager, TestSuiteReservationManagerFixture)

    BOOST_AUTO_TEST_CASE(AddReservationPositiveTest) {
        ReservationsManager manager;
        ReservationPtr reservation1 = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        ReservationPtr reservation = std::make_shared<Reservation>(testVisitor, testSeance, testRow, testSeat);
        BOOST_TEST(reservation1, reservation);
    }

    BOOST_AUTO_TEST_CASE(RemoveReservationPositiveTest){
        ReservationsManager manager;
        ReservationPtr reservation = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        BOOST_TEST( manager.removeReservation(reservation), true);
    }
    BOOST_AUTO_TEST_CASE(GetReservationPositiveTest) {
        ReservationsManager manager;
        ReservationPtr reservation = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        boost::uuids::uuid id = reservation->getReservationNumber();
        BOOST_TEST(manager.getReservation(id), reservation);
    }
    BOOST_AUTO_TEST_CASE(FindReservationTest) {
        ReservationsManager manager;
        ReservationPtr reservation = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        ReservationPredicate p = [](ReservationPtr ptr)->bool{
            return( ptr->getRow() == 12);
        };
        BOOST_TEST(manager.find(p), reservation);
    }
    BOOST_AUTO_TEST_CASE(FindAllReservationsTest) {
        ReservationsManager manager;
        ReservationPtr reservation1 = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        ReservationPtr reservation2 = manager.addReservation(testVisitor, testSeance, 12, 10);;
        ReservationPredicate p = [](ReservationPtr ptr)->bool{
            return( ptr->getRow() == 12 );
        };
        std::vector<ReservationPtr> result = manager.findAll(p);
        std::vector<ReservationPtr> m;
        m.push_back(reservation1);
        m.push_back(reservation2);
        BOOST_CHECK(result == m);
    }
    BOOST_AUTO_TEST_CASE(GetReservationFromIndexTest) {
        ReservationsManager manager;
        ReservationPtr reservation = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        BOOST_TEST(manager.getReservation(0), reservation);
    }
    BOOST_AUTO_TEST_CASE(SizeTest) {
        ReservationsManager manager;
        ReservationPtr reservation = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        BOOST_TEST(manager.size(), 1);
    }
    BOOST_AUTO_TEST_CASE(GetIndexTest) {
        ReservationsManager manager;
        ReservationPtr reservation = manager.addReservation(testVisitor, testSeance, testRow, testSeat);
        BOOST_CHECK_EQUAL(manager.getIndex(reservation), 0);
    }

BOOST_AUTO_TEST_SUITE_END()
