#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "persistentattribute.h"
#include "QString"
#include "livre.h"
#include <QtSql>
#include "handler.h"

int main(int argc, char *argv[])
{
    //std::cout<<QDir::currentPath().toStdString()<<std::endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}
