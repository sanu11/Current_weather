#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QApplication>
#include<QDebug>
#include<QMessageBox>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QUrl>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonDocument>
#include<QJsonArray>
double MainWindow::b;
double::MainWindow::c;
double MainWindow::d;
QString MainWindow::place;
QString MainWindow::str;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(getcity()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getcity()
{
   ui->label_4->clear();
   ui->label_5->clear();
   ui->label_8->clear();
   ui->label_10->clear();
   place=ui->lineEdit->text();
   this->setCursor(Qt::WaitCursor);
   if(place==NULL)
       QMessageBox ::information(this,"Error","Enter proper city",QMessageBox::Ok);
    else
       city();
     ui->lineEdit->clear();
}
void MainWindow::set()
{
    this->setCursor(Qt::ArrowCursor);
    qDebug()<<ui->lineEdit->text();
    ui->label_10->setText(place);
    ui->label_4->setText(QString::number(b));
    ui->label_5->setText(QString::number(c));
    ui->label_8->setText(QString::number(d));
   }
void MainWindow::city()
{
     QString str1="http://api.openweathermap.org/data/2.5/weather?q=";
     QString str2="&APPID=04c2a4b8f8e7c2d142d053b79416ebe3";
     str=str1+place+str2;
     qDebug()<<str;
     send();
}
void MainWindow:: send()
{
    QEventLoop l;
    QNetworkAccessManager m;
    QObject::connect(&m, SIGNAL(finished(QNetworkReply*)),&l,SLOT(quit()));
    QNetworkReply *reply = m.get(QNetworkRequest(QUrl(QString(str))));
    l.exec();
    if(reply->error()==QNetworkReply::NoError)
    {
       QByteArray arr = reply->readAll();
       QJsonDocument  jsonDoc = QJsonDocument::fromJson(arr);
       QJsonObject obj=jsonDoc.object();
       if(obj.contains("message"))
          QMessageBox::information(this,"Sorry","City not found",QMessageBox::Ok);
       else
       {
       QJsonObject main = obj.value("main").toObject();
       b=main.value("temp_min").toDouble()-273.15;
       c=main.value("temp_max").toDouble()-273.15;
       d=main.value("humidity").toDouble();
       qDebug()<<"Today's Minimum temperature is"<<b<<"degree";
       qDebug()<<"Today's Maximum temperature is"<<c<<"degree";
       qDebug()<<"Humidity is"<<d<<"percent";
       set();
       }
    }
       else
    {
        qDebug() << "Failure" <<reply->errorString();
        QString err=reply->errorString();
        char *error;
        error=new char[err.length()+1];
        strcpy(error, err.toStdString().c_str());
        if(strstr(error,"Host")!=NULL)
            QMessageBox::critical(this,"Error","Check your network",QMessageBox::Ok);
        else
        QMessageBox::information(this,"Sorry","City not found ",QMessageBox::Ok);
    }
    delete reply;
}


