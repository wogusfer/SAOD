#ifndef TROUPE_DIALOG_H
#define TROUPE_DIALOG_H

#include <QDialog>
#include "theatre.h"
namespace Ui {
class troupe_dialog;
}

class troupe_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit troupe_dialog(QWidget *parent = nullptr);
    ~troupe_dialog();

private slots:
    void on_back_clicked();

    void showtableTroupe(Show* s);

    void showTroupe(Troupe *s, int a, int n);

    void showtableShow();

    void showShow(Show *s, int a, int n);

    void on_ButtonToAdd_clicked();

    void on_ButtonToDelete_clicked();

    void recieveData(theatre *H);//получить данные и скопировать

private:
    theatre *T;//копия бд
    int NumOfA;
    QList<Audience*> ListOfA;
    Ui::troupe_dialog *ui;
};

#endif // TROUPE_DIALOG_H
