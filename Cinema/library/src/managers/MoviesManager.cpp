//
// Created by student on 11.06.2020.
//

#include "managers/MoviesManager.h"
#include "model/typedefs.h"
#include "model/Movie.h"
#include "exceptions/ManagersExceptions.h"
#include <memory>

MoviePtr MoviesManager::addMovie(const std::string &title, unsigned int basePrice) {
    if(title.empty()) throw ManagersExceptions("The title cannot be empty");
    MoviePtr ptr = std::make_shared<Movie>(title, basePrice);
    moviesRepository.add(ptr);
    return ptr;
}

bool MoviesManager::removeMovie(MoviePtr &ptr) {
    if(ptr == nullptr) throw ManagersExceptions("Cannot remove this object!");
    moviesRepository.remove(ptr);
    return true;
}

MoviePtr MoviesManager::find(const MoviePredicate &predicate) {
    for(int i=0; i<moviesRepository.size(); i++)
    {
        MoviePtr ptr = moviesRepository.get(i);
        if(predicate(ptr)) return ptr;
    }
    throw ManagersExceptions("Movie was not found in the repository!");
}

std::vector<MoviePtr> MoviesManager::findAll(const MoviePredicate &predicate) {
    std::vector<MoviePtr> result;
    for(int i=0; i<moviesRepository.size(); i++)
    {
        MoviePtr ptr = moviesRepository.get(i);
        if(predicate(ptr)) result.push_back(ptr);
    }
    return result;
}

MoviePtr MoviesManager::getMovie(std::string title) {
    if(title.empty()) throw ManagersExceptions("The title cannot be empty");
    MoviePredicate p=[title](MoviePtr ptr)->bool
    {
        return (title==ptr->getTitle());
    };
    return find(p);
}

MoviesManager::MoviesManager()  {}

MoviesManager::~MoviesManager() {

}

MoviePtr MoviesManager::getMovie(int index) {
    if(index <0) throw ManagersExceptions("This index must be positive!");
    return moviesRepository.get(index);
}

int MoviesManager::size() {
    return moviesRepository.size();
}

int MoviesManager::getIndex(const MoviePtr &ptr){
    if(ptr == nullptr) throw ManagersExceptions("This object doesn't exist!");
    return moviesRepository.getIndex(ptr);
}
