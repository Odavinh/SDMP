#include "person.h"



Person::Person()
{

}

Person::Person(const int &id,
               const QString &firstName,
               const QString &surname,
               const QString &lastName,
               const QString &gender,
               const QString &born,
               const QString &number1,
               const QString &number2,
               const QString &email,
               const QString &address,
               const QString &webSite,
               const QString &detail)
{
    this->id = std::make_shared<int>(id);
    this->firstName = std::make_shared<QString>(firstName);
    this->surname = std::make_shared<QString>(surname);
    this->lastName = std::make_shared<QString>(lastName);
    this->gender = std::make_shared<QString>(gender);
    this->born = std::make_shared<QString>(born);
    this->number1 = std::make_shared<QString>(number1);
    this->number2 = std::make_shared<QString>(number2);
    this->email = std::make_shared<QString>(email);
    this->address = std::make_shared<QString>(address);
    this->webSite = std::make_shared<QString>(webSite);
    this->detail = std::make_shared<QString>(detail);
}

QString Person::HederColunString()
{
    return QString("First Name, Surname, Last Name, Gender, Born, Number1, Number2, Email, Address, Web-site, Detail");
}

QString Person::fullLineString()
{
    return QString(*this->firstName.get()+", "+
                   this->surname.get()+", "+
                   this->lastName.get()+", "+
                   this->gender.get()+", "+
                   this->born.get()+", "+
                   this->number1.get()+", "+
                   this->number2.get()+", "+
                   this->email.get()+", "+
                   this->address.get()+", "+
                   this->webSite.get()+", "+
                   this->detail.get());
}


QString Person::getFirstName() const
{
    return *firstName.get();
}

QString Person::getSurname() const
{
    return *surname.get();
}

QString Person::getLastName() const
{
    return *lastName.get();
}

QString Person::getGender() const
{
    return *gender.get();
}

QString Person::getBorn() const
{
    return *born.get();
}

QString Person::getNumber1() const
{
    return *number1.get();
}

QString Person::getNumber2() const
{
    return *number2.get();
}

QString Person::getEmail() const
{
    return *email.get();
}

QString Person::getAddress() const
{
    return *address.get();
}

QString Person::getWebSite() const
{
    return *webSite.get();
}

QString Person::getDetail() const
{
    return *detail.get();
}

int Person::getId() const
{
    return *id.get();
}
