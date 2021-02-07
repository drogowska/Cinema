//
// Created by student on 11.06.2020.
//

#ifndef CINEMAPROJECT_VISITORSMANAGER_H
#define CINEMAPROJECT_VISITORSMANAGER_H

#include "repositories/VisitorsRepository.h"
#include <boost/uuid/uuid_io.hpp>
#include "model/Visitor.h"
#include <vector>

class VisitorsManager {
private:
    VisitorsRepository visitorsRepository;
public:
    VisitorsManager();

    virtual ~VisitorsManager();

    VisitorPtr addVisitor(const std::string &firstName, const std::string &lastName, const std::string &email, const std::string password,
                          const std::string &phoneNumber, DiscountType discountType, bool worker);
    bool removeVisitor(VisitorPtr &ptr);
    VisitorPtr find(const VisitorPredicate &predicate);
    std::vector<VisitorPtr> findAll(const VisitorPredicate &predicate);
    VisitorPtr getVisitor(boost::uuids::uuid &id);
    VisitorPtr getVisitor(int index);
    int size();
    int getIndex(const VisitorPtr &ptr);
};


#endif //CINEMAPROJECT_VISITORSMANAGER_H
