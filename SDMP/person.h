#ifndef PERSON_H
#define PERSON_H

#include<QString>
#include<QImage>
#include<memory>

class Person
{
public:
    Person();
    explicit Person(const int &id,
                    const QString &firstName,
                    const QString &surname,
                    const QString &lastName = nullptr,
                    const QString &gender = nullptr,
                    const QString &born = nullptr,
                    const QString &number1 = nullptr,
                    const QString &number2 = nullptr,
                    const QString &email = nullptr,
                    const QString &address = nullptr,
                    const QString &webSite = nullptr,
                    const QString &detail = nullptr);

    static QString HederColunString();
    QString fullLineString();

    QString getFirstName() const;

    QString getSurname() const;

    QString getLastName() const;

    QString getGender() const;

    QString getBorn() const;

    QString getNumber1() const;

    QString getNumber2() const;

    QString getEmail() const;

    QString getAddress() const;

    QString getWebSite() const;

    QString getDetail() const;

    int getId() const;

private:
    std::shared_ptr<int> id;
    std::shared_ptr<QString> firstName;
    std::shared_ptr<QString> surname;
    std::shared_ptr<QString> lastName;
    std::shared_ptr<QString> gender;
    std::shared_ptr<QString> born;
    std::shared_ptr<QString> number1;
    std::shared_ptr<QString> number2;
    std::shared_ptr<QString> email;
    std::shared_ptr<QString> address;
    std::shared_ptr<QString> webSite;
    std::shared_ptr<QString> detail;

};

#endif // PERSON_H
