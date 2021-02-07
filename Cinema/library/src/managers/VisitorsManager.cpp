//
// Created by student on 11.06.2020.
//

#include "managers/VisitorsManager.h"
#include "model/typedefs.h"
#include "exceptions/ManagersExceptions.h"
#include <memory>

VisitorPtr VisitorsManager::addVisitor(const std::string &firstName, const std::string &lastName, const std::string &email,
                                       const std::string password, const std::string &phoneNumber, DiscountType discountType, bool worker) {
    VisitorPredicate p=[email](VisitorPtr ptr)->bool
    {
        return (email==ptr->getEmail());
    };
    std::vector<VisitorPtr> visitors = findAll(p);
    if(!visitors.empty()) {
        throw ManagersExceptions("Visitor with this email already exists!");
    }

    if(firstName.empty()) throw ManagersExceptions("The first name cannot be empty");
    if(lastName.empty()) throw ManagersExceptions("The last name cannot be empty");
    if(email.find("@") == std::string::npos) throw ManagersExceptions("The email have to contain sign @.");
    if(phoneNumber.size() != 9) throw ManagersExceptions("Given new phone number is too short or too long.");
    if(password.size() < 4) throw ManagersExceptions("The password must contain at least 4 characters!");


    VisitorPtr ptr = std::make_shared<Visitor>(firstName, lastName, email, password, phoneNumber, discountType, worker);
    visitorsRepository.add(ptr);
    return ptr;
}

bool VisitorsManager::removeVisitor(VisitorPtr &ptr) {
    if(ptr == nullptr) throw ManagersExceptions("Cannot remove this object!");
    visitorsRepository.remove(ptr);
    return true;
}

VisitorPtr VisitorsManager::find(const VisitorPredicate &predicate) {
    for(int i=0; i<visitorsRepository.size(); i++)
    {
        VisitorPtr ptr = visitorsRepository.get(i);
        if(predicate(ptr)) return ptr;
    }
    throw ManagersExceptions("Visitor was not found in the repository!");
}

std::vector<VisitorPtr> VisitorsManager::findAll(const VisitorPredicate &predicate) {
    std::vector<VisitorPtr> result;
    for(int i=0; i<visitorsRepository.size(); i++)
    {
        VisitorPtr ptr = visitorsRepository.get(i);
        if(predicate(ptr)) result.push_back(ptr);
    }
    return result;
}

VisitorPtr VisitorsManager::getVisitor(boost::uuids::uuid &id) {
    VisitorPredicate p=[id](VisitorPtr ptr)->bool
    {
        return (id==ptr->getId());
    };
    return find(p);
}

VisitorsManager::VisitorsManager() {}

VisitorsManager::~VisitorsManager() {

}

VisitorPtr VisitorsManager::getVisitor(int index) {
    if(index <0) throw ManagersExceptions("This index must be positive!");
    return visitorsRepository.get(index);
}

int VisitorsManager::size() {
    return visitorsRepository.size();
}

int VisitorsManager::getIndex(const VisitorPtr &ptr){
    if(ptr == nullptr) throw ManagersExceptions("This object doesn't exist!");
    return visitorsRepository.getIndex(ptr);
}
