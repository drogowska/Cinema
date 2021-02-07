#include <boost/test/unit_test.hpp>
#include "managers/MoviesManager.h"
#include "model/Movie.h"

BOOST_AUTO_TEST_SUITE(TestSuiteMoviesManagersExceptions)

    BOOST_AUTO_TEST_CASE(AddObjectWithEmptyTitle) {
        MoviesManager manager;
        BOOST_CHECK_THROW(manager.addMovie("", 25);, std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(RemoveIncorrectObject) {
        MoviesManager manager;
        MoviePtr object = nullptr;
        manager.addMovie("Titanic", 25);
        BOOST_CHECK_THROW(manager.removeMovie(object), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(FindIncorrectObject) {
        MoviesManager manager;
        manager.addMovie("Titanic", 25);
        MoviePredicate p = [](MoviePtr ptr)->bool{
            return( ptr->getTitle() == "titile");
        };
        BOOST_CHECK_THROW(manager.find(p), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetObjectWithEmptyTitle) {
        MoviesManager manager;
        manager.addMovie("Titanic", 25);
        BOOST_CHECK_THROW(manager.getMovie(""), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetMovieWithNegativeIndex) {
        MoviesManager manager;
        BOOST_CHECK_THROW(manager.getMovie(-5), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetIndexFromEmptyObject) {
        MoviesManager manager;
        MoviePtr movie = nullptr;
        BOOST_CHECK_THROW(manager.getIndex(movie), std::logic_error);
    }
BOOST_AUTO_TEST_SUITE_END()