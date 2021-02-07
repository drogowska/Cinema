#include <boost/test/unit_test.hpp>
#include "repositories/MoviesRepository.h"
#include "repositories/VisitorsRepository.h"
#include "repositories/HallsRepository.h"
#include "repositories/SeancesRepository.h"
#include "repositories/ReservationsRepository.h"
#include "model/Movie.h"
#include "model/Hall.h"
#include "model/Visitor.h"
#include "model/Seance.h"
#include "model/Reservation.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteRepoFixture {
    pt::ptime testDateAndTime = pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00));
    SeanceType testSeanceType3D = threeD;
    SeanceType testSeanceType2D = twoD;
    MoviePtr testMovie = std::make_shared<Movie>("Titanic", 25);
    HallPtr testHall = std::make_shared<Hall>("A01", 35,15);
    VisitorPtr testVisitor = std::make_shared<Visitor>("John","Smith","aaa@com.com","1234","123456789",Default, false);
    SeancePtr testSeance = std::make_shared<Seance>(testDateAndTime, threeD, testMovie, testHall);
    int testRow = 12;
    int testSeat = 12;


};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepository, TestSuiteRepoFixture)

    BOOST_AUTO_TEST_CASE(AddPositiveTestAndSizeTest) {
        MoviesRepository repo;
        BOOST_TEST_CHECK(repo.size() == 0);
        repo.add(testMovie);
        BOOST_TEST_CHECK(repo.size() == 1);
    }

    BOOST_AUTO_TEST_CASE(GetPositiveTest){
        MoviesRepository repo;
        repo.add(testMovie);
        MoviePtr get = repo.get(0);
        BOOST_TEST_CHECK(get == testMovie);
    }

    BOOST_AUTO_TEST_CASE(RemovePositiveTest){
        MoviesRepository repo;
        repo.add(testMovie);
        BOOST_TEST_CHECK(repo.size() == 1);
        repo.remove(testMovie);
        BOOST_TEST_CHECK(repo.size() == 0);
    }
    BOOST_AUTO_TEST_CASE(MoviesRepositoryReportTest){
        MoviesRepository repo;
        repo.add(testMovie);
        BOOST_TEST_CHECK(repo.report() == testMovie->getMovieInfo());
    }
    BOOST_AUTO_TEST_CASE(HallsRepositoryReportTest){
        HallsRepository repo;
        repo.add(testHall);
        BOOST_TEST_CHECK(repo.report() == testHall->getHallInfo());
    }
    BOOST_AUTO_TEST_CASE(VisitorsRepositoryReportTest){
        VisitorsRepository repo;
        repo.add(testVisitor);
        BOOST_TEST_CHECK(repo.report() == testVisitor->getVisitorInfo());
    }
    BOOST_AUTO_TEST_CASE(SeancesRepositoryReportTest){
        SeancesRepository repo;
        repo.add(testSeance);
        BOOST_TEST_CHECK(repo.report() == testSeance->getSeanceInfo());
    }
    BOOST_AUTO_TEST_CASE(ReservationsRepositoryReportTest){
        ReservationsRepository repo;
        ReservationPtr r = std::make_shared<Reservation>(testVisitor,testSeance,testRow, testSeat);
        repo.add(r);
        BOOST_TEST_CHECK(repo.report() == r->getReservationInfo());
    }
BOOST_AUTO_TEST_SUITE_END()
