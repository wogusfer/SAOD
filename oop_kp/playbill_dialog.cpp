#include "playbill_dialog.h"
#include "ui_playbill_dialog.h"
#include "theatre.h"
#include "show.h"

playbill_dialog::playbill_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playbill_dialog)
{
    ui->setupUi(this);
}

playbill_dialog::~playbill_dialog()
{
    delete ui;
}

void playbill_dialog::recieveData(theatre *Ho)
{
    this->T = Ho;//копируем бд
    ui->tablePlaybill->setRowCount(0);
    showtable();
    ui->tablePlaybill->resizeColumnsToContents();
}

void playbill_dialog::on_back_clicked()
{
    close();
    ui->InputDateTime->clear();
    ui->InputNameshow->clear();
    ui->tablePlaybill->setRowCount(0);
    ui->NumToDelete->clear();
    ui->NumToSearch->clear();
    ui->tableTroupe->setRowCount(0);
}

void playbill_dialog::on_AddShow_clicked()
{
    QString nameshow = ui->InputNameshow->text();
    QString DateTime = ui->InputDateTime->text();
    QString building = ui->DropDownBuilding->currentText();
    QString Type = ui->DropDownType->currentText();
    Show* s = new Show();
    s->setNameshow(nameshow);
    s->setDateTime(DateTime);
    s->setBuilding(building);
    s->setType(Type);
    s->setNumSits(s->nuzhno(s->getBuilding()));
    T->setShow(s);
    NumOfSh++;
    showtable();
}

void playbill_dialog::showtable(){
if(T->hasShow()){
    int n (0);
    n = T->getNumOfShow();
    NumOfSh=n;
    if(n>0){
       QStringList lst;
       ui->tablePlaybill->setRowCount(n);
       for(int i=1;i<=n;i++)
           lst<< QString::number(i);
       ui->tablePlaybill->setVerticalHeaderLabels(lst);

       int  i(0),m(0);
       m=T->getNumOfShow();
       foreach(Show* s,T->getListOfShow()){
               showShowsT(s, i, m);
               i++;
           }
       }
    }
    else
        ui->tablePlaybill->setRowCount(0);
    ui->tablePlaybill->resizeColumnsToContents();
}

void playbill_dialog::on_DeleteShow_clicked()
{
    int n = ui->NumToDelete->text().toInt();
    n--;
    if(n>=0 && n<NumOfSh){
         QTableWidgetItem* q = ui->tablePlaybill->item(n,1);
         QString nam;
              if(q!=NULL)
               nam = q->text();
          Show* s = T->getShowByName(nam);
          if(s!=nullptr){
              if(!T->ShowhasAudience(s)){
                  T->delShow(n);
                  NumOfSh--;
                  showtable();
              }
          }
    }
}

void playbill_dialog::showShowsT(Show* S, int a, int n){

    QTableWidgetItem* ptwi = 0;
    int j=0;

    for (int i =0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(S->getDateTime());
     ui->tablePlaybill->setItem(k, j, ptwi);
    }

    j++;
    for (int i = 0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(S->getNameshow());
     ui->tablePlaybill->setItem(k, j, ptwi);
    }

    j++;
    for (int i = 0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(S->getType());
     ui->tablePlaybill->setItem(k, j, ptwi);
    }

    j++;
    for (int i = 0, k=a; i < n; ++i,++k) {
     ptwi = new QTableWidgetItem(S->getBuilding());
     ui->tablePlaybill->setItem(k, j, ptwi);
    }
}

void playbill_dialog::on_ShowTroupe_clicked()
{
    int n = ui->NumToSearch->text().toInt();
    n--;
    if(n>=0 && n<NumOfSh){
         QTableWidgetItem* q = ui->tablePlaybill->item(n,1);
         QString nam;
              if(q!=NULL)
               nam = q->text();
          Show* s = T->getShowByName(nam);
          if(s!=nullptr){
              QList<Troupe*> list = T->ShowhasTroupe(s);
              if(!list.isEmpty()){
                  showtableTroupe(list);
                  }
          }
    }
}

void playbill_dialog::showtableTroupe(QList<Troupe*> list){
    QStringList lst;
    int n = list.count();

    ui->tableTroupe->setRowCount(n);
    for(int i=1;i<=n;i++)
        lst<< QString::number(i);
    ui->tableTroupe->setVerticalHeaderLabels(lst);

    QTableWidgetItem* ptwi = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
     ptwi = new QTableWidgetItem(list.at(i)->getSurname()
                                 +" "+list.at(i)->getName()
                                 +" "+list.at(i)->getPatronymic());
     ui->tableTroupe->setItem(i, j, ptwi);
    }

    ui->tableTroupe->resizeColumnsToContents();
}
