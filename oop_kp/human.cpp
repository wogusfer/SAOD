#include "human.h"

Human::Human()
{

}

void Human::setName(const QString &newName)
{
    Name = newName;
}

void Human::setSurname(const QString &newSurname)
{
    Surname = newSurname;
}

void Human::setPatronymic(const QString &newPatronymic)
{
    Patronymic = newPatronymic;
}

const QString &Human::getName() const
{
    return Name;
}

const QString &Human::getSurname() const
{
    return Surname;
}

const QString &Human::getPatronymic() const
{
    return Patronymic;
}
