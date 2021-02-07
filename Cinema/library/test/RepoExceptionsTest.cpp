#include <boost/test/unit_test.hpp>
#include "repositories/VisitorsRepository.h"
#include "model/Visitor.h"
#include "model/typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteRepoExceptions)


    BOOST_AUTO_TEST_CASE(AddIncorrectObject) {
        VisitorsRepository repo;
        VisitorPtr v = nullptr;
        BOOST_CHECK_THROW(repo.add(v), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(GetObjectWithWrongIndex) {
        VisitorsRepository repo;
        BOOST_CHECK_THROW(repo.get(2), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(RemoveIncorrectObject) {
        VisitorsRepository repo;
        VisitorPtr v = nullptr;
        BOOST_CHECK_THROW(repo.remove(v), std::logic_error);
    }
BOOST_AUTO_TEST_SUITE_END()
