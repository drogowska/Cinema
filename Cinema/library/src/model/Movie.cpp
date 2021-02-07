#include "model/Movie.h"
#include <sstream>
#include "exceptions/MovieExceptions.h"
using namespace std;

Movie::Movie(const std::string &title, unsigned int basePrice) : title(title), basePrice(basePrice) {

    if(title.empty()) throw MovieExceptions("The title cannot be empty!");
}

Movie::~Movie() {

}

std::string Movie::getMovieInfo() const {
    ostringstream sout;
    int margin = 30;
    //sout << "_________________________________________________" <<endl;
    sout << "Movie Info:"<<endl;
    sout.width(margin); sout << left << "Title: ";
    sout<< getTitle()<<endl;
    sout.width(margin); sout << left << "Base price: ";
    sout << to_string(getBasePrice())<<endl;

    return sout.str();
}

const std::string &Movie::getTitle() const {
    return title;
}

unsigned int Movie::getBasePrice() const {
    return basePrice;
}

void Movie::setBasePrice(unsigned int basePrice) {
    Movie::basePrice = basePrice;
}
void print(const Movie &movie, ostream &out) {
    out << movie.getMovieInfo() << endl;
}
