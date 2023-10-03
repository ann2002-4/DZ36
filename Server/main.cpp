#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include "Database.h"
#include "connect.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connect window;//запускаем класс соединения с базой
    window.show();
    return a.exec();
}
