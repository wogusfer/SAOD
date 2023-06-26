#ifndef HUMAN_H
#define HUMAN_H

#include "QString"
class Human
{
public:
    Human();
    //сеттеры и геттеры для хранимых данных
    void setName(const QString &newName);

    void setSurname(const QString &newSurname);

    void setPatronymic(const QString &newPatronymic);

    const QString &getName() const;

    const QString &getSurname() const;

    const QString &getPatronymic() const;

protected:
    QString Name;   
    QString Surname;
    QString Patronymic;
};

#endif // HUMAN_H
