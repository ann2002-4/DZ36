#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include "connect.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connect window;
    window.show();
    return a.exec();

}

