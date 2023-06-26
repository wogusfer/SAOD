#ifndef TROUPE_H
#define TROUPE_H

#include"QString"
#include"QList"

#include"human.h"

class Troupe: public Human
{
public:
    Troupe();
    ~Troupe();

    //сеттеры и геттеры для хранимых данных

    int getId() const;
    void setId(int newId);

    int getNumOfShow();

    bool hasShow();


private:
    int id;
};

#endif // TROUPE_H
