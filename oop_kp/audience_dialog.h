#ifndef AUDIENCE_DIALOG_H
#define AUDIENCE_DIALOG_H

#include <QDialog>
#include "theatre.h"
namespace Ui {
class audience_dialog;
}

class audience_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit audience_dialog(QWidget *parent = nullptr);
    ~audience_dialog();

private slots:
    void on_back_clicked();

    void showtableAudience();

    void showAudience(Audience *s, int a, int n);

    void showtableShow();

    void showShow(Show *s, int a, int n);

    void on_ButtonToAdd_clicked();

    void on_ButtonToDelete_clicked();

    void recieveData(theatre *H);//получить данные и скопировать

private:
    theatre *T;//копия бд
    int NumOfA;
    QList<Audience*> ListOfA;
    Ui::audience_dialog *ui;
};

#endif // AUDIENCE_DIALOG_H
