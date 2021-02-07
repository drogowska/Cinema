#include "model/Visitor.h"
#include "exceptions/VisitorExceptions.h"
#include <sstream>
#include <iostream>

using namespace std;

Visitor::Visitor(const string &firstName, const string &lastName, const string &email, const string password,
                 const string &phoneNumber, DiscountType discountType, bool worker) : firstName(firstName), lastName(lastName), email(email),
                                                                        password(password), phoneNumber(phoneNumber), discountType(discountType), worker(worker) {

    boost :: uuids :: random_generator gen;
    id = gen();
    if(email.find("@") == string::npos) throw VisitorExceptions("The email have to contain sign @.");
    if(phoneNumber.size() != 9) throw VisitorExceptions("Given new phone number is too short or too long.");
    if(password.size() < 4) throw VisitorExceptions("The password must contain at least 4 characters!");

}

Visitor::~Visitor() {

}

string Visitor::getVisitorInfo() const {
    ostringstream sout;
    int margin = 30;
    sout << "_________________________________________________" <<endl;
    sout << "Visitor Info:"<<endl;
    sout.width(margin); sout << left << "Name: ";
    sout<< getFirstName() << " "<< getLastName()<<endl;
    sout.width(margin); sout << left << "Disount Type: ";
    sout<< getDiscountTypeName() <<endl;
    sout.width(margin); sout << left << "ID: ";
    sout << to_string(getId()) <<endl;
    sout.width(margin); sout << left << "Email: ";
    sout<< getEmail()<<endl;
    sout.width(margin); sout << left << "PhoneNumber: ";
    sout<< getPhoneNumber() << endl;

    return sout.str();
}

const boost::uuids::uuid &Visitor::getId() const {
    return id;
}

const string &Visitor::getFirstName() const {
    return firstName;
}

const string &Visitor::getLastName() const {
    return lastName;
}

const string &Visitor::getEmail() const {
    return email;
}

const string &Visitor::getPhoneNumber() const {
    return phoneNumber;
}

void Visitor::setEmail(const string &Email) {
    if(Email.find("@") == string::npos) throw VisitorExceptions("The new email have to contain sign @.");
    else email = Email;
}

void Visitor::setPhoneNumber(const string &PhoneNumber) {
    if(PhoneNumber.size() != 9) throw VisitorExceptions("Given new phone number is too short or too long!");
    else phoneNumber = PhoneNumber;
}

DiscountType Visitor::getDiscountType() const {
    return discountType;
}

std::string Visitor::getDiscountTypeName() const {

    switch(discountType) {
        case -40: {
            return "Student";
            break;
        }
        case -30: {
            return "Senior";
            break;
        }
        case -50:{
            return "Kid";
            break;
        }
        default:{
            return "Default";
            break;
        }
    }
}

const string &Visitor::getPassword() const {
    return password;
}

void Visitor::setPassword(const string &newPassword) {
    if(newPassword.size() < 4) throw VisitorExceptions("The new password must contain at least 4 characters!");
    if(password == newPassword) throw VisitorExceptions("The new password must be different");
    password = newPassword;
}

bool Visitor::isWorker() const {
    return worker;
}

void Visitor::setFirstName(const string &firstName) {
    if(firstName.empty()) throw VisitorExceptions("The first name cannot be empty");
    Visitor::firstName = firstName;
}

void Visitor::setLastName(const string &lastName) {
    if(lastName.empty()) throw VisitorExceptions("The last name cannot be empty");
    Visitor::lastName = lastName;
}

void Visitor::setWorker(bool worker) {
    Visitor::worker = worker;
}

void print(const Visitor &visitor, ostream &out) {
    out << visitor.getVisitorInfo() << endl;
}

DiscountType convertDiscountTypeFromString(const std::string &str){
    if(str=="Kid") return Kid;
    if(str=="Senior") return Senior;
    if(str=="Student") return Student;
    return Default;
}