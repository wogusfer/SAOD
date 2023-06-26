#include "audience_dialog.h"
#include "ui_audience_dialog.h"
#include "theatre.h"
#include "show.h"

audience_dialog::audience_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::audience_dialog)
{
    ui->setupUi(this);
}

audience_dialog::~audience_dialog()
{
    delete ui;
}

void audience_dialog::recieveData(theatre *Ho)
{
    this->T = Ho;//копируем бд
    ui->tableAudience->setRowCount(0);
    ui->tableShow->setRowCount(0);

    ui->InputName->clear();
    ui->InputNumToDelete->clear();
    ui->InputNumofShow->clear();
    ui->InputPatronimyc->clear();
    ui->InputSurname->clear();

    showtableAudience();
    showtableShow();
}

void audience_dialog::on_back_clicked()
{
    close();//закрываем окно
    ui->InputName->clear();
    ui->InputNumToDelete->clear();
    ui->InputNumofShow->clear();
    ui->InputPatronimyc->clear();
    ui->InputSurname->clear();
    ui->tableAudience->setRowCount(0);
    ui->tableShow->setRowCount(0);
}

void audience_dialog::showtableAudience(){
    if(T->hasAudience()){
        int n (0);
        n = T->getNumOfAudience();
        if(n>0){
           QStringList lst;
           ui->tableAudience->setRowCount(n);
           for(int i=1;i<=n;i++)
               lst<< QString::number(i);
           ui->tableAudience->setVerticalHeaderLabels(lst);

           int  i(0),m(0);
           m=T->getNumOfAudience();
           foreach(Audience* s,T->getListOfAudience()){
                   showAudience(s, i, m);
                   i++;
               }
           }
        }
        else
            ui->tableAudience->setRowCount(0);
        ui->tableAudience->resizeColumnsToContents();
}

void audience_dialog::showAudience(Audience* D, int a, int n){

    QTableWidgetItem* ptwi = 0;
    int j=0;
    for (int i =0, k=a; i < n; ++i,++k) {
        ptwi = new QTableWidgetItem(D->getSurname()
                                    +" "+D->getName()
                                    +" "+D->getPatronymic());
     ui->tableAudience->setItem(k, j, ptwi);
    }

    j++;
    for (int i = 0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(D->getNameshow());
     ui->tableAudience->setItem(k, j, ptwi);
    }

    j++;
    for (int i = 0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(QString::number(D->getSit()));
     ui->tableAudience->setItem(k, j, ptwi);
    }
}

void audience_dialog::showtableShow(){
if(T->hasShow()){
    int n (0);
    n = T->getNumOfShow();
    if(n>0 && n<NumOfA){
       QStringList lst;
       ui->tableShow->setRowCount(n);
       for(int i=1;i<=n;i++)
           lst<< QString::number(i);
       ui->tableShow->setVerticalHeaderLabels(lst);

       int  i(0),m(0);
       m=T->getNumOfShow();
       foreach(Show* s,T->getListOfShow()){
               showShow(s, i, m);
               i++;
           }
       }
    }
    else
        ui->tableShow->setRowCount(0);
    ui->tableShow->resizeColumnsToContents();
}

void audience_dialog::showShow(Show* S, int a, int n){
    QTableWidgetItem* ptwi = 0;
    int j=0;

    for (int i =0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(S->getDateTime());
     ui->tableShow->setItem(k, j, ptwi);
    }

    j++;
    for (int i = 0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(S->getNameshow());
         ui->tableShow->setItem(k, j, ptwi);
        }

        j++;
        for (int i = 0, k=a; i < n; ++i,++k) {
         ptwi = new QTableWidgetItem(S->getType());
         ui->tableShow->setItem(k, j, ptwi);
        }

        j++;
        for (int i = 0, k=a; i < n; ++i,++k) {
         ptwi = new QTableWidgetItem(S->getBuilding());
         ui->tableShow->setItem(k, j, ptwi);
        }
    }

void audience_dialog::on_ButtonToAdd_clicked()
{
    QString name = ui->InputName->text();
    QString surname = ui->InputSurname->text();
    QString pat = ui->InputPatronimyc->text();
    int n = ui->InputNumofShow->text().toInt();
    n--;
    if(n>=0){
         QTableWidgetItem* q = ui->tableShow->item(n,1);
         QString nam;
              if(q!=NULL)
               nam = q->text();
          Show* s = T->getShowByName(nam);
            Audience* p = new Audience();
            p->setId(T->getListOfAudience().last()->getId()+1);
            p->setName(name);
            p->setPatronymic(pat);
            p->setSurname(surname);
            p->setNameshow(s->getNameshow());
            p->setSit(s->getAudiences().last()->getSit()+1);
            T->setAudience(p);
            s->setAudience(p);
            NumOfA++;
            showtableAudience();
}
}

void audience_dialog::on_ButtonToDelete_clicked()
{
    int n = ui->InputNumToDelete->text().toInt();
    n--;
    if(n>=0 && n<NumOfA){
         QTableWidgetItem* w = ui->tableAudience->item(n,1);
         QString nam;
              if(w!=NULL)
               nam = w->text();
          Show* s = T->getShowByName(nam);
          QTableWidgetItem* z = ui->tableAudience->item(n,2);
          Audience* a = T->getAudienceBySit(s, z->text().toInt());
          if(a!=nullptr){
                  T->delAudience(n);
                  NumOfA--;

                   s->delAudienceSit(a->getSit());
                  showtableAudience();

          }
    }
}
