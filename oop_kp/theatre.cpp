#include "theatre.h"
#include "troupe.h"
#include "show.h"

theatre::theatre()
{
    // база данных
    Audience* a1 = new Audience;
    a1->setId(1);
    a1->setName("Демидова");
    a1->setSurname("Анастасия");
    a1->setPatronymic("Дмитриевна");
    a1->setNameshow("Щелкунчик");
    a1->setSit(1);

    Audience* a2 = new Audience;
    a2->setId(2);
    a2->setName("Шишкина");
    a2->setSurname("Елизавета");
    a2->setPatronymic("Алексеевна");
    a2->setNameshow("Щелкунчик");
    a2->setSit(2);

    Audience* a3 = new Audience;
    a3->setId(3);
    a3->setName("Кайбышева");
    a3->setSurname("Елена");
    a3->setPatronymic("Рамильевна");
    a3->setNameshow("Лебединное озеро");
    a3->setSit(1);

    Troupe* t1 = new Troupe;
    t1->setId(1);
    t1->setSurname("Касаткина");
    t1->setName("Алёна");
    t1->setPatronymic("Леонидовна");

    Troupe* t2 = new Troupe;
    t2->setId(2);
    t2->setSurname("Окунева");
    t2->setName("Полина");
    t2->setPatronymic("Алексеевна");

    Show* s1 = new Show;
    s1->setId(1);
    s1->setDateTime("24.12.2021 18:00");
    s1->setNameshow("Щелкунчик");
    s1->setBuilding("Мариинский театр");
    s1->setType("Балет");

    Show* s2 = new Show;
    s2->setId(2);
    s2->setDateTime("30.12.2021 16:00");
    s2->setNameshow("Лебединное озеро");
    s2->setBuilding("Мариинский 2");
    s2->setType("Балет");

    setShow(s1);
    setShow(s2);
    setAudience(a1);
    setAudience(a2);
    setAudience(a3);

    s1->setAudience(a1);
    s1->setAudience(a2);
    s2->setAudience(a3);
    s1->setTroupes(t1);
    s2->setTroupes(t2);
}

theatre* theatre::Theatre = 0;
theatre* theatre::gettheatre()
{
    if(Theatre==nullptr){
       Theatre = new theatre();
    }
    return Theatre;
}

bool theatre::hasTroupe()
{
    if(ListOfTroupe.empty())
            return false;
        else
            return true;
}

bool theatre::hasShow()
{
    if(ListOfShow.empty())
            return false;
        else
            return true;
}

bool theatre::hasAudience()
{
    if(ListOfAudience.empty())
            return false;
        else
            return true;
}

int theatre::getCurrentId() const
{
    return currentId;
}

void theatre::setCurrentId(int newCurrentId)
{
    currentId = newCurrentId;
}

const QList<Show *> &theatre::getListOfShow() const
{
    return ListOfShow;
}

const QList<Troupe *> &theatre::getListOfTroupe() const
{
    return ListOfTroupe;
}

Show * theatre::getShow(int n)
{
    return ListOfShow.at(n);
}

Show* theatre::getShowByName(QString strname)
{
    int i(0);
    foreach(Show* s, ListOfShow){
        if(s->getNameshow()==strname){
            return ListOfShow.at(i);
        }
        i++;
    }
    return nullptr;
}

Audience* theatre::getAudienceBySit(Show* s,int n)
{
    int i(0);
    foreach(Audience* a, s->getAudiences()){
        if(a->getSit()==n){
            return s->getAudiences().at(i);
        }
        i++;
    }
    return nullptr;
}

Show* theatre::getShowById(int id)
{
    int i(0);
    foreach(Show* s, ListOfShow){
        if(s->getId()==id){
            return ListOfShow.at(i);
        }
        i++;
    }
    return nullptr;
}

Audience* theatre::getAudienceById(int id)
{
    int i(0);
    foreach(Audience* s, ListOfAudience){
        if(s->getId()==id){
            return ListOfAudience.at(i);
        }
        i++;
    }
    return nullptr;
}

void theatre::setShow(Show * &newShow)
{
    ListOfShow.append( newShow);
}

int theatre::getNumOfTroupe()
{
    return ListOfTroupe.count();
}

int theatre::getNumOfAudience()
{
    return ListOfAudience.count();
}

int theatre::getNumOfShow()
{
    return ListOfShow.count();
}

Troupe * theatre::getTroupe(int n)
{
    return ListOfTroupe.at(n);
}

void theatre::setTroupe(Troupe * &newTroupe)
{
    ListOfTroupe.append(newTroupe);
}

Audience * theatre::getAudience(int n)
{
    return ListOfAudience.at(n);
}

void theatre::setAudience(Audience *&newAudience)
{
    ListOfAudience.append(newAudience);
}


const QList<Audience *> &theatre::getListOfAudience() const
{
    return ListOfAudience;
}

void theatre::delAudience(int n)
{
    ListOfAudience.takeAt(n);
}

void theatre::delShow(int n)
{
    ListOfShow.takeAt(n);
}

bool theatre::ShowhasAudience(Show *d){
    foreach(Show* s,ListOfShow){
        foreach(Audience* a,s->getAudiences()){
            if(a->getNameshow()==d->getNameshow())
                return 1;
        }
    }
    return 0;
}

QList<Troupe*>theatre::ShowhasTroupe(Show *d){
        QList<Troupe*> list;
            foreach(Troupe* p,d->getTroupes()){
                    list.append(p);
        }
        return list;
}

theatre::~theatre()
{
    qDeleteAll(ListOfAudience);
    qDeleteAll(ListOfShow);
    qDeleteAll(ListOfTroupe);
}
