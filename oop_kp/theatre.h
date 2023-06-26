#ifndef THEATRE_H
#define THEATRE_H

#include "troupe.h"
#include "show.h"
#include "QList"
class theatre
{
public:
    static theatre*  gettheatre();

    bool hasTroupe();

    bool hasShow();
    bool hasAudience();
    ~theatre();

    //геттеры и сеттеры для хранимых данных
    const QString &getAddress() const;
    void setAddress(const QString &newAddress);

    const QString &getName() const;
    void setName(const QString &newName);

    Troupe *getTroupe(int n) ;
    const QList<Troupe *> &getListOfTroupe() const;
    void setTroupe(Troupe *&newTroupe);

    Audience *getAudience(int n) ;
    const QList<Audience *> &getListOfAudience() const;
    void setAudience(Audience *&newAudience);

    Show * getShow(int n) ;
    const QList<Show *> &getListOfShow() const;
    void setShow(Show * &newListOfShow);

    int getCurrentId() const;
    void setCurrentId(int newCurrentId);

    int getNumOfTroupe();
    int getNumOfAudience();


    void delTroupe(int n);

    bool findNameTroupe(QString name);

    int getNumOfShow();

    void delShow(int n);

    bool findNameShow(QString name);

    QString NameOfShow(Troupe *p);

    void getShowAndPut(QString str, Troupe *p);

    Troupe *getTroupeByName(QString strname);

    Show *getShowByName(QString strname);

    Show *getShowById(int id);

    Audience *getAudienceById(int id);

    Audience *getAudinceTicket(QString tic);

    void delAudience(int n);

    bool ShowhasAudience(Show *d);

    Audience* getAudienceBySit(Show* s,int n);

    QList<Troupe*>ShowhasTroupe(Show *d);

    void delTroupfromShow(int id);
private:
    theatre();
    static theatre* Theatre;

    int currentId;
    QString address;
    QString name;
    QList <Troupe*> ListOfTroupe;
    QList <Show*> ListOfShow;
    QList <Audience*> ListOfAudience;
};

#endif // THEATRE_H
