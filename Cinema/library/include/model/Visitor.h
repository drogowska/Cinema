#ifndef CINEMA_PROJECT_VISITOR_H
#define CINEMA_PROJECT_VISITOR_H

#include <string>
#include <boost/uuid/uuid_generators.hpp> //generator
#include <boost/uuid/uuid_io.hpp>

enum DiscountType{
    Kid =-50, //-50% ceny
    Senior = -30,
    Student = -40,
    Default = 0,
};

DiscountType convertDiscountTypeFromString(const std::string &str);

class Visitor {
private:
    boost::uuids::uuid id;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::string phoneNumber;
    DiscountType discountType;
    bool worker;
public:
    Visitor(const std::string &firstName, const std::string &lastName, const std::string &email, const std::string password,
            const std::string &phoneNumber, DiscountType discountType, bool worker);

    virtual ~Visitor();
    std::string getVisitorInfo() const;
    const boost::uuids::uuid &getId() const;
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getEmail() const;
    const std::string &getPhoneNumber() const;
    DiscountType getDiscountType() const;
    bool isWorker() const;
    const std::string &getPassword() const;
    void setPassword(const std::string &newPassword);

    std::string getDiscountTypeName() const;

    void setEmail(const std::string &Email);

    void setPhoneNumber(const std::string &PhoneNumber);

    void setFirstName(const std::string &firstName);

    void setLastName(const std::string &lastName);

    void setWorker(bool worker);
};
void print(const Visitor &visitor, std::ostream &out);
DiscountType convertDiscountTypeFromString(const std::string &str);
#endif //CINEMA_PROJECT_VISITOR_H
