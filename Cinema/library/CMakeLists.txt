cmake_minimum_required(VERSION 3.15)
project(Library)

set(SOURCE_FILES
        src/model/Visitor.cpp include/model/Visitor.h
        src/exceptions/VisitorExceptions.cpp include/exceptions/VisitorExceptions.h
        src/model/Reservation.cpp include/model/Reservation.h
        src/model/Seance.cpp include/model/Seance.h
        src/model/Movie.cpp include/model/Movie.h
        src/model/Hall.cpp include/model/Hall.h
        src/exceptions/MovieExceptions.cpp include/exceptions/MovieExceptions.h
        src/exceptions/ReservationExceptions.cpp include/exceptions/ReservationExceptions.h
        include/model/typedefs.h
        include/repositories/Repository.h
        include/repositories/VectorRepository.h
        src/repositories/HallsRepository.cpp include/repositories/HallsRepository.h
        src/repositories/MoviesRepository.cpp include/repositories/Repository.h
        src/repositories/ReservationsRepository.cpp include/repositories/ReservationsRepository.h
        src/repositories/VisitorsRepository.cpp include/repositories/VisitorsRepository.h
        src/repositories/SeancesRepository.cpp include/repositories/SeancesRepository.h
        src/managers/HallsManager.cpp include/managers/HallsManager.h
        src/managers/MoviesManager.cpp include/managers/MoviesManager.h
        src/managers/ReservationsManager.cpp include/managers/ReservationsManager.h
        src/managers/SeancesManager.cpp include/managers/SeancesManager.h
        src/managers/VisitorsManager.cpp include/managers/VisitorsManager.h
        src/exceptions/RepoExceptions.cpp include/exceptions/RepoExceptions.h
        src/exceptions/SeanceExceptions.cpp include/exceptions/SeanceExceptions.h
        src/exceptions/HallExceptions.cpp include/exceptions/HallExceptions.h
        src/exceptions/ManagersExceptions.cpp include/exceptions/ManagersExceptions.h
        src/model/Arguments.cpp include/model/Arguments.h
        src/model/Cinema.cpp include/model/Cinema.h src/exceptions/CinemaExceptions.cpp include/exceptions/CinemaExceptions.h src/model/TextView.cpp include/model/TextView.h)

#utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_link_libraries(Program Library
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY})



enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/VisitorTest.cpp
        test/VisitorExceptionsTest.cpp
        test/HallTest.cpp
        test/MovieTest.cpp
        test/ReservationTest.cpp
        test/SeanceTest.cpp
        test/MovieExceptionsTest.cpp
        test/ReservationExceptionsTest.cpp test/HallsManagerTest.cpp test/RepositoriesTest.cpp test/HallExceptionTest.cpp test/HallsManagerExceptionsTest.cpp test/VisitorsManagerExceptionsTest.cpp test/MoviesManagerExceptionsTest.cpp test/SeancesManagerExceptionsTest.cpp test/ReservationsManagerExceptionsTest.cpp test/VisitorsManagerTest.cpp test/MoviesManagerTest.cpp test/SeancesManagerTest.cpp test/ReservationsManagerTest.cpp test/SeanceExceptionTest.cpp)

add_executable (LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTest Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
