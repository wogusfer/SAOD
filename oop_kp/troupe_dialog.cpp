#include "troupe_dialog.h"
#include "ui_troupe_dialog.h"
#include "theatre.h"
#include "show.h"

troupe_dialog::troupe_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::troupe_dialog)
{
    ui->setupUi(this);
}

troupe_dialog::~troupe_dialog()
{
    delete ui;
}

void troupe_dialog::recieveData(theatre *Ho)
{
    this->T = Ho;//копируем бд
    ui->tableTroupe->setRowCount(0);
    ui->tableShow->setRowCount(0);

    ui->InputName->clear();
    ui->InputNumToDelete->clear();
    ui->InputNumofShow->clear();
    ui->InputPatronimyc->clear();
    ui->InputSurname->clear();

    showtableShow();
}

void troupe_dialog::on_back_clicked()
{
    close();//закрываем окно
    ui->InputName->clear();
    ui->InputNumToDelete->clear();
    ui->InputNumofShow->clear();
    ui->InputPatronimyc->clear();
    ui->InputSurname->clear();
    ui->tableTroupe->setRowCount(0);
    ui->tableShow->setRowCount(0);
}

void troupe_dialog::showtableTroupe(Show* s){
    if(s->hasTroupe()){
        int n (0);
        n = s->getNumOfTroupe();
        if(n>0){
           QStringList lst;
           ui->tableTroupe->setRowCount(n);
           for(int i=1;i<=n;i++)
               lst<< QString::number(i);
           ui->tableTroupe->setVerticalHeaderLabels(lst);

           int  i(0),m(0);
           m=s->getNumOfTroupe();
           foreach(Troupe* s,s->getTroupes()){
                   showTroupe(s, i, m);
                   i++;
               }
           }
        }
        else
            ui->tableTroupe->setRowCount(0);
        ui->tableTroupe->resizeColumnsToContents();
}

void troupe_dialog::showTroupe(Troupe* D, int a, int n){

    QTableWidgetItem* ptwi = 0;
    int j=0;
    for (int i =0, k=a; i < n; ++i,++k) {
        ptwi = new QTableWidgetItem(D->getSurname()
                                    +" "+D->getName()
                                    +" "+D->getPatronymic());
     ui->tableTroupe->setItem(k, j, ptwi);
     ui->tableTroupe->resizeColumnsToContents();
    }
}

void troupe_dialog::showtableShow(){
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

void troupe_dialog::showShow(Show* S, int a, int n){
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

void troupe_dialog::on_ButtonToAdd_clicked()
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
            Troupe* p = new Troupe();
            p->setId(T->getListOfAudience().last()->getId()+1);
            p->setName(name);
            p->setPatronymic(pat);
            p->setSurname(surname);
            T->setTroupe(p);
            s->setTroupes(p);
            NumOfA++;
            showtableTroupe(s);
}
}

void troupe_dialog::on_ButtonToDelete_clicked()
{
    int n = ui->InputNumToDelete->text().toInt();
    n--;
    if(n>=0){
         QTableWidgetItem* q = ui->tableShow->item(n,1);
         QString nam;
              if(q!=NULL)
               nam = q->text();
          Show* s = T->getShowByName(nam);
          showtableTroupe(s);
    }
}
