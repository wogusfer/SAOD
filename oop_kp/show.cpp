#include "show.h"

Show::Show()
{
    qDeleteAll(troupes);
    qDeleteAll(audiences);
}

Show::~Show()
{
    qDeleteAll(troupes);
    qDeleteAll(audiences);
}

int Show::getId() const
{
    return id;
}

void Show::setId(int newId)
{
    id = newId;
}

int Show::getNumSits() const
{
    return NumSits;
}

void Show::setNumSits(int newNumSits)
{
    NumSits = newNumSits;
}

const QString &Show::getNameshow() const
{
    return nameshow;
}

int Show::nuzhno(QString Building)
{
    if(Building=="Мариинский театр")
            return 1625;
        else if(Building=="Мариинский 2")
            return 1830;
        else if(Building=="Концертный зал")
            return 1110;
}

void Show::setNameshow(const QString &newNameshow)
{
    nameshow = newNameshow;
}

const QString &Show::getDateTime() const
{
    return DateTime;
}

void Show::setDateTime(const QString &newDateTime)
{
    DateTime = newDateTime;
}

const QString &Show::getType() const
{
    return Type;
}

void Show::setType(const QString &newType)
{
    Type = newType;
}

const QString &Show::getBuilding() const
{
    return Building;
}

void Show::setBuilding(const QString &newBuilding)
{
    Building = newBuilding;
}

Troupe * Show::getTroupe(int n)
{
    return troupes.at(n);
}

void Show::setTroupes(Troupe * &newTroupes)
{
    troupes.append(newTroupes);
}

Audience * Show::getAudience(int n) const
{
    return audiences.at(n);
}

void Show::setAudience(Audience *&newAudience)
{
    audiences.append(newAudience);
}

int Show::getNumOfTroupe()
{
    return troupes.count();
}

int Show::getNumOfAudience()
{
    return audiences.count();
}

bool Show::hasTroupe()
{
    if(troupes.empty())
            return false;
        else
            return true;
}

bool Show::hasAudience()
{
    if(audiences.empty())
            return false;
        else
        return true;
}

void Show::delTroupeId(int id)
{
    int i(0);
    foreach(Troupe* p, troupes){
       if(p->getId()==id){
           troupes.takeAt(i);
       }
         i++;
    }
}

void Show::delAudienceSit(int sit){
    int i(0);
    foreach(Audience* d, audiences){
       if(d->getSit()==sit){
           audiences.takeAt(i);
       }
         i++;
    }
}

const QList<Audience *> &Show::getAudiences() const
{
    return audiences;
}

const QList<Troupe *> &Show::getTroupes() const
{
    return troupes;
}
