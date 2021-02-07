//
// Created by student on 04.06.2020.
//

#ifndef CINEMAPROJECT_VECTORREPOSITORY_H
#define CINEMAPROJECT_VECTORREPOSITORY_H


#include <vector>
#include <string>
#include "exceptions/RepoExceptions.h"
#include "Repository.h"



template<class T>
class VectorRepository : public Repository<T> {
protected:
    std::vector<T> data;
public:
    VectorRepository();
    virtual ~VectorRepository();

    void add(T object) override;
    T get(int index) override;
    int size() const override;
    void remove(T &object) override;
    virtual std::string report() const = 0;
    int getIndex(const T &object);

};

template<class T>
void VectorRepository<T>::add(T object) {
    if (object == nullptr) throw RepoExceptions("This object doesn't exist so it can't be added.");
    else data.push_back(object);

}

template<class T>
VectorRepository<T>::VectorRepository() {}

template<class T>
VectorRepository<T>::~VectorRepository() {

}

template<class T>
T VectorRepository<T>::get(int index) {
    if (index > data.size()) throw RepoExceptions("This object isn't in repository!");
    else return data[index];
}

template<class T>
int VectorRepository<T>::size() const {
    return data.size();
}

template<class T>
void VectorRepository<T>::remove(T &object) {
    if (object == nullptr) throw RepoExceptions("This object doesn't exist so it can't be removed.");
    else
        for (int i = 0; i < size(); i++) {
            if (object == data[i]) {
                data.erase(data.begin() + i);
            }
        }
}

template<class T>
int VectorRepository<T>::getIndex(const T &object) {
    if (object == nullptr) throw RepoExceptions("This object doesn't exist.");
    for(int i=0; i<size(); i++)
    {
        if(object == data[i]) return i;
    }
    throw RepoExceptions("This object isn't in repository!");
}




#endif //CINEMAPROJECT_VECTORREPOSITORY_H
