#ifndef CINEMAPROJECT_MOVIE_H
#define CINEMAPROJECT_MOVIE_H

#include <string>


class Movie {
private:
    std::string title;
    unsigned int basePrice;
public:
    Movie(const std::string &title, unsigned int basePrice);
    virtual ~Movie();

    std::string getMovieInfo() const;
    const std::string &getTitle() const;
    unsigned int getBasePrice() const;

    void setBasePrice(unsigned int basePrice);
};
void print(const Movie &movie, std::ostream &out);


#endif //CINEMAPROJECT_MOVIE_H
