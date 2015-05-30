#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
static double a,b,c,d;
static QString place,str;
void get(double,double,double);
void set();
void send();
void city();
private slots:
void getcity();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
