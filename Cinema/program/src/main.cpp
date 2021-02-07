/*#include <iostream>
#include <boost/date_time.hpp>
#include "model/Visitor.h"
#include "model/Movie.h"
#include "model/Reservation.h"
#include "model/Seance.h"
#include "model/Hall.h"
#include <boost/uuid/uuid_generators.hpp> //generator
#include <boost/uuid/uuid_io.hpp>
#include "repositories/MoviesRepository.h"
#include "repositories/HallsRepository.h"
using namespace std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
int main() {
    Visitor v= Visitor("John","Smith","aaa@com.com","123456789", Student);
    v.setEmail("AS@SA");
    v.setPhoneNumber("568231111");

    print(v,cout);
    Hall* hall = new Hall("A01", 35,15);
    Movie* movie = new Movie("Titanic", 25);
    Seance s (pt::ptime(gr::date(2020,4,28),pt::hours(18)+pt::minutes(00)),threeD,movie, hall);
    print(s,cout);
    MoviesRepository repo;
    MoviePtr m = std::make_shared<Movie>("title",25);


    return 0;
}*/

#include "model/Cinema.h"
#include "model/Movie.h"
#include "model/typedefs.h"
#include <iostream>
#include "model/Arguments.h"
#include "model/TextView.h"

using namespace std;

int main(int argc, char *argv[])
{
    ArgumentsPtr args = parse(argc, argv);
    if(args){
        try{
            CinemaPtr cinema = initialize(args);
            TextView textView(cinema);
            textView.mainPage();
            finalize(cinema, args);
        }
        catch(exception &e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
    return 0;
}