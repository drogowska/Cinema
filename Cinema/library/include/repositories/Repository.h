//
// Created by student on 04.06.2020.
//

#ifndef CINEMAPROJECT_REPOSITORY_H
#define CINEMAPROJECT_REPOSITORY_H

#include <string>


template<class T>
class Repository {
public:

    virtual void add(T object) = 0;
    virtual T get(int index) = 0;
    virtual int size() const = 0;
    virtual void remove(T &object) = 0;

};


#endif //CINEMAPROJECT_REPOSITORY_H
