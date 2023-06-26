#ifndef PLAYBILL_DIALOG_H
#define PLAYBILL_DIALOG_H

#include "theatre.h"

#include <QDialog>

namespace Ui { class playbill_dialog; }

class playbill_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit playbill_dialog(QWidget *parent = nullptr);
    ~playbill_dialog();

private slots:

    void on_back_clicked();

    void on_AddShow_clicked();

    void showtable();

    void showShowsT(Show *S, int a, int n);

    void on_DeleteShow_clicked();

    void recieveData(theatre *Ho);

    void on_ShowTroupe_clicked();
    void showtableTroupe(QList<Troupe*> lst);

private:
    int NumOfSh = 0;
    theatre *T;
    Ui::playbill_dialog *ui;
};

#endif // PLAYBILL_DIALOG_H
