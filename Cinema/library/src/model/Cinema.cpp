//
// Created by student on 12.06.2020.
//

#include "model/Cinema.h"
#include "model/typedefs.h"
#include "model/Movie.h"
#include "model/Hall.h"
#include "model/Visitor.h"
#include "model/Seance.h"
#include "model/Reservation.h"
#include <boost/tokenizer.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "exceptions/CinemaExceptions.h"
using namespace std;

Cinema::Cinema() {
}

Cinema::~Cinema() {

}

std::istream &fromStream(std::istream &in, CinemaPtr &cinema) {
    string line;
    vector<string> result;
    while (in.good()) {
        getline(in, line);
        if (line.empty()) {
            if (in.eof()) {
                break;
            }
            throw CinemaExceptions("There is an empty line in the input file!");
        }
        result = split(line);
        if (result[0].compare("Visitor") == 0) {
            if (result.size() != 8) throw CinemaExceptions("Wrong number of Visitor arguments!");
            cinema->visitorsManager.addVisitor(result[1], result[2], result[3], result[4],result[5],
                                              convertDiscountTypeFromString(result[6]), stoi(result[7]));
        } else if (result[0].compare("Movie") == 0) {
            if (result.size() != 3) throw CinemaExceptions("Wrong number of Movie arguments!");
            cinema->moviesManager.addMovie(result[1], stoi(result[2]));
        } else if (result[0].compare("Hall") == 0) {
            if (result.size() != 4) throw CinemaExceptions("Wrong number of Hall arguments!");
            cinema->hallsManager.addHall(result[1], stoi(result[2]), stoi(result[3]));
        } else if (result[0].compare("Seance") == 0) {
            if (result.size() != 9) throw CinemaExceptions("Wrong number of Seance arguments!");
            tm pt_tm;
            pt_tm.tm_year=stoi(result[1]);
            pt_tm.tm_mon=stoi(result[2]);
            pt_tm.tm_mday=stoi(result[3]);
            pt_tm.tm_hour=stoi(result[4]);
            pt_tm.tm_min=stoi(result[5]);
            pt_tm.tm_sec=0;
            boost::posix_time::ptime dateAndTime = boost::posix_time::ptime_from_tm(pt_tm);
            MoviePtr movie=cinema->moviesManager.getMovie(stoi(result[7]));
            HallPtr hall=cinema->hallsManager.getHall(stoi(result[8]));
            cinema->seancesManager.addSeance(dateAndTime, convertSeanceTypeFromString(result[6]), movie, hall);
        } else if (result[0].compare("Reservation") == 0) {
            if (result.size() != 5) throw CinemaExceptions("Wrong number of Reservation arguments!");;
            VisitorPtr visitor=cinema->visitorsManager.getVisitor(stoi(result[1]));
            SeancePtr seance=cinema->seancesManager.getSeance(stoi(result[2]));
            cinema->reservationsManager.addReservation(visitor,seance,stoi(result[3]),stoi(result[4]));
        } else throw CinemaExceptions("Wrong name of the class in the input file!");
    }
    return in;
}

std::ostream &toStream(std::ostream &out, CinemaPtr &cinema) {
    for (unsigned int i = 0; i < cinema->visitorsManager.size(); i++) {
        VisitorPtr visitor = cinema->visitorsManager.getVisitor(i);
        out << "Visitor,\"" << visitor->getFirstName() << "\",\"" << visitor->getLastName() << "\",\"";
        out << visitor->getEmail() << "\",\"" << visitor->getPassword() << "\",\"";
        out << visitor->getPhoneNumber() << "\",\"" << visitor->getDiscountTypeName() << "\",";
        out << visitor->isWorker() << endl;
    }
    for (unsigned int i = 0; i < cinema->moviesManager.size(); i++) {
        MoviePtr movie = cinema->moviesManager.getMovie(i);
        out << "Movie,\"" << movie->getTitle() << "\"," << movie->getBasePrice() << endl;
    }
    for (unsigned int i = 0; i < cinema->hallsManager.size(); i++) {
        HallPtr hall = cinema->hallsManager.getHall(i);
        out << "Hall,\"" << hall->getHallNumber() << "\"," << hall->getNumberOfRows() << ","<<hall->getNumberOfSeatInRow()
            << endl;
    }
    for (unsigned int i = 0; i < cinema->seancesManager.size(); i++) {
        SeancePtr seance = cinema->seancesManager.getSeance(i);
        boost::posix_time::ptime dateTime=seance->getDateAndTime();
        tm pt_tm=to_tm(dateTime);

        out << "Seance," <<pt_tm.tm_year<< ","<<pt_tm.tm_mon<<","<<pt_tm.tm_mday<<","<<pt_tm.tm_hour<<","<< pt_tm.tm_min;
        out << ",\"" << seance->getSeanceTypeName() << "\"";
        out << "," << cinema->moviesManager.getIndex(seance->getMovie());
        out << "," << cinema->hallsManager.getIndex(seance->getHall()) << endl;
    }
    for (unsigned int i = 0; i < cinema->reservationsManager.size(); i++) {
        ReservationPtr reservation = cinema->reservationsManager.getReservation(i);

        out << "Reservation," << cinema->visitorsManager.getIndex(reservation->getVisitor()) << ",";
        out << cinema->seancesManager.getIndex(reservation->getSeance()) << ",";
        out << reservation->getRow() << "," << reservation->getSeat() << endl;
    }
    return out;
}

void Cinema::fullRemoveMovie(MoviePtr &movie) {
    SeancePredicate p = [movie](SeancePtr ptr)->bool{
        return(ptr->getMovie()==movie);
    };
    vector<SeancePtr> seances = seancesManager.findAll(p);
    for(SeancePtr ptr: seances){
        fullRemoveSeance(ptr);
    }
    moviesManager.removeMovie(movie);
}

void Cinema::fullRemoveSeance(SeancePtr &seance) {

    ReservationPredicate p = [seance](ReservationPtr ptr)->bool{
        return(ptr->getSeance()==seance);
    };
    vector<ReservationPtr> reservations = reservationsManager.findAll(p);
    for(ReservationPtr ptr: reservations){
        reservationsManager.removeReservation(ptr);
    }
    seancesManager.removeSeance(seance);
}

void Cinema::fullRemoveVisitor(VisitorPtr &visitor) {
    ReservationPredicate p = [visitor](ReservationPtr ptr)->bool{
        return(ptr->getVisitor()==visitor);
    };
    vector<ReservationPtr> reservations = reservationsManager.findAll(p);
    for(ReservationPtr ptr: reservations){
        reservationsManager.removeReservation(ptr);
    }
    visitorsManager.removeVisitor(visitor);
}

void Cinema::fullRemoveHall(HallPtr &hall) {
    SeancePredicate p = [hall](SeancePtr ptr)->bool{
        return(ptr->getHall()==hall);
    };
    vector<SeancePtr> seances = seancesManager.findAll(p);
    for(SeancePtr ptr: seances){
        fullRemoveSeance(ptr);
    }
    hallsManager.removeHall(hall);
}

std::vector<std::string> split(const std::string &line) {
    vector<string> result;
    boost::tokenizer<boost::escaped_list_separator<char>>
            tokenizer(line, boost::escaped_list_separator<char>('\\', ',', '\"'));
    for (boost::tokenizer<boost::escaped_list_separator<char>>::iterator it = tokenizer.begin(); it != tokenizer.end();
         ++it) {
        result.push_back(*it);
    }
    return result;
}
