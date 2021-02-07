//
// Created by student on 11.06.2020.
//

#ifndef CINEMAPROJECT_MOVIESMANAGER_H
#define CINEMAPROJECT_MOVIESMANAGER_H

#include "repositories/MoviesRepository.h"
#include <vector>

class MoviesManager {
private:
    MoviesRepository moviesRepository;
public:
    MoviesManager();

    virtual ~MoviesManager();

    MoviePtr addMovie(const std::string &title, unsigned int basePrice);
    bool removeMovie(MoviePtr &ptr);
    MoviePtr find(const MoviePredicate &predicate);
    std::vector<MoviePtr> findAll(const MoviePredicate &predicate);
    MoviePtr getMovie(std::string title);
    MoviePtr getMovie(int index);
    int size();
    int getIndex(const MoviePtr &ptr);
};


#endif //CINEMAPROJECT_MOVIESMANAGER_H
