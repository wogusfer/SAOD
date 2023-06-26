#ifndef SHOW_H
#define SHOW_H

#include "audience.h"
#include "troupe.h"
#include "QString"
#include "QList"

class Show
{
public:
    Show();
    ~Show();

    //сеттеры и геттеры для хранимых данных
    int nuzhno(QString Building);

    int getId() const;
    void setId(int newId);

    int getNumSits() const;
    void setNumSits(int newNumSits);

    const QString &getNameshow() const;
    void setNameshow(const QString &newNameshow);

    const QString &getDateTime() const;
    void setDateTime(const QString &newDateTime);

    const QString &getType() const;
    void setType(const QString &newType);

    const QString &getBuilding() const;
    void setBuilding(const QString &newBuilding);

    Troupe *getTroupe(int n);
    void setTroupes(Troupe *&newTroupes);

    Audience *getAudience(int n) const;
    void setAudience(Audience *&newAudience);

    const QList<Troupe *> &getTroupes() const;
    const QList<Audience *> &getAudiences() const;

    int getNumOfTroupe();

    int getNumOfAudience();

    bool hasTroupe();

    bool hasAudience();

    void delTroupeId(int id);

    void delAudienceSit(int sit);

private:
    int id;
    int NumSits;
    QString nameshow;
    QString DateTime;
    QString Building;
    QString Type;
    QList<Troupe*> troupes;
    QList<Audience*> audiences;
};

#endif // SHOW_H
