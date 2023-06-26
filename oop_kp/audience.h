#ifndef AUDIENCE_H
#define AUDIENCE_H

#include "human.h"
#include "QList"
#include "QString"

class Audience : public Human
{
public:
    Audience();
    //сеттер и геттер для хранимого данного
    int getId() const;
    void setId(int newId);

    int getSit() const;
    void setSit(int newSit);

    const QString &getNameshow() const;
    void setNameshow(const QString &newNameshow);
private:
    int id;
    int sit;
    QString show;
};

#endif // AUDIENCE_H
