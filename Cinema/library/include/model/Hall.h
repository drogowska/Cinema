#ifndef CINEMAPROJECT_HALL_H
#define CINEMAPROJECT_HALL_H

#include <string>

class Hall {
private:
    std::string hallNumber;
    unsigned int numberOfSeatsInRow;
    unsigned int numberOfRows;
public:
    Hall(std::string hallNumber, unsigned int numberOfRows, unsigned int numberOfSeatsInRow);
    virtual ~Hall();

    std::string getHallNumber() const;
    unsigned int getNumberOfSeatInRow() const;
    unsigned int getNumberOfRows() const;
    std::string getHallInfo() const;

    void setHallNumber(const std::string &hallNumber);

};
void print(const Hall &hall, std::ostream &out);

#endif //CINEMAPROJECT_HALL_H
