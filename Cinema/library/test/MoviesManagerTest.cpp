#include <boost/test/unit_test.hpp>
#include "managers/MoviesManager.h"
#include "model/Movie.h"

BOOST_AUTO_TEST_SUITE(TestSuiteMoviesManager)

    BOOST_AUTO_TEST_CASE(AddPositiveTest) {
        MoviesManager manager;
        manager.addMovie("Titanic",25);
        MoviePtr movie = std::make_shared<Movie>("Titanic",25);
        BOOST_TEST(manager.addMovie("Titanic",25), movie);
    }

    BOOST_AUTO_TEST_CASE(RemoveMoviePositiveTest){
        MoviesManager manager;
        MoviePtr movie = manager.addMovie("Titanic",25);
        BOOST_TEST( manager.removeMovie(movie), true);
    }
    BOOST_AUTO_TEST_CASE(GetPositiveTest) {
        MoviesManager manager;
        MoviePtr movie = manager.addMovie("Titanic",25);
        //MoviePtr movie = std::make_shared<Movie>("Titanic",25);
        BOOST_TEST(manager.getMovie("Titanic"), movie);
    }
    BOOST_AUTO_TEST_CASE(FindObjetTest) {
        MoviesManager manager;
        MoviePtr movie = manager.addMovie("Titanic",25);
        MoviePredicate p = [](MoviePtr ptr)->bool{
            return( ptr->getTitle() == "Titanic");
        };
        BOOST_TEST(manager.find(p), movie);
    }
    BOOST_AUTO_TEST_CASE(FindAllTest) {
        MoviesManager manager;
        MoviePtr movie1 = manager.addMovie("Titanic",25);
        MoviePtr movie2 = manager.addMovie("Inception",25);
        MoviePredicate p = [](MoviePtr ptr)->bool{
            return( ptr->getBasePrice() == 25);
        };
        std::vector<MoviePtr> result = manager.findAll(p);
        std::vector<MoviePtr> m;
        m.push_back(movie1);
        m.push_back(movie2);
        BOOST_CHECK(result == m);
    }
    BOOST_AUTO_TEST_CASE(GetMovieFromIndexTest) {
        MoviesManager manager;
        MoviePtr movie = manager.addMovie("Titanic",25);
        BOOST_TEST(manager.getMovie(0), movie);
    }
    BOOST_AUTO_TEST_CASE(SizeTest) {
        MoviesManager manager;
        MoviePtr movie = manager.addMovie("Titanic",25);
        BOOST_TEST(manager.size(), 1);
    }
    BOOST_AUTO_TEST_CASE(GetIndexTest) {
        MoviesManager manager;
        MoviePtr movie = manager.addMovie("Titanic",25);
        BOOST_CHECK_EQUAL(manager.getIndex(movie), 0);
    }
BOOST_AUTO_TEST_SUITE_END()
