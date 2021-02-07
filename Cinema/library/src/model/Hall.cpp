#include "model/Hall.h"
#include "exceptions/HallExceptions.h"
#include <sstream>
using namespace std;

Hall::Hall(std::string hallNumber,unsigned int numberOfRows,unsigned int numberOfSeatsInRow)  :
                            numberOfRows(numberOfRows), numberOfSeatsInRow(numberOfSeatsInRow) {

    if(hallNumber.empty()) throw HallExceptions("Cannot create hall with empty hall number!");
    else this->hallNumber=hallNumber;
}

Hall::~Hall() {

}
unsigned int Hall::getNumberOfSeatInRow() const {
    return numberOfSeatsInRow;
}

unsigned int Hall::getNumberOfRows() const {
    return numberOfRows;
}

std::string Hall::getHallNumber() const {
    return hallNumber;
}

void Hall::setHallNumber(const std::string &hallNumber) {
    if(hallNumber.empty()) throw HallExceptions("Cannot change hall's name - name cannot be epmty!");
    Hall::hallNumber = hallNumber;
}

std::string Hall::getHallInfo() const {
    ostringstream sout;
    int margin = 30;
    //sout << "_________________________________________________" <<endl;
    sout << "Hall Info:"<<endl;
    sout.width(margin); sout << left << "Hall number: ";
    sout<< getHallNumber()<<endl;
    sout.width(margin); sout << left << "Number of rows: ";
    sout << to_string(getNumberOfRows()) <<endl;
    sout.width(margin); sout << left << "Number of seats in row: ";
    sout<< to_string(getNumberOfSeatInRow())<<endl;

    return sout.str();
}
void print(const Hall &hall, ostream &out) {
    out << hall.getHallInfo() << endl;
}