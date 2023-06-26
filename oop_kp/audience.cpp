#include "audience.h"

Audience::Audience()
{

}

int Audience::getSit() const
{
    return sit;
}

void Audience::setSit(int newSit)
{
    sit = newSit;
}

const QString &Audience::getNameshow() const
{
    return show;
}

void Audience::setNameshow(const QString &newNameshow)
{
    show = newNameshow;
}

int Audience::getId() const
{
    return id;
}

void Audience::setId(int newId)
{
    id = newId;
}
