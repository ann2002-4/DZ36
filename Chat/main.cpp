#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include "connect.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //createConnection();
    connect window;//запускаем класс соединения с базой
    window.show();
    return a.exec();

}

