#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "theatre.h"
#include "playbill_dialog.h"
#include "audience_dialog.h"
#include "troupe_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendData(theatre* H);//сигнал который отправляет данные

private slots:
    void on_Playbill_clicked(); // кнопка для открытия окна с афишей и передачи в новый класс данных

    void on_Troupe_clicked(); // кнопка для открытия окна с труппой и передачи в новый класс данных

    void on_Audience_clicked(); // кнопка для открытия окна с посетителями и передачи в новый класс данных

private:
    Ui::MainWindow *ui;
    audience_dialog *ad; // диалоговое окно меню для посетителей
    playbill_dialog *pd; // диалоговое окно меню для афиши
    troupe_dialog *td; // диалоговое окно меню для труппы

    theatre* Theatre = theatre::gettheatre(); // объект класса театр
};
#endif // MAINWINDOW_H
