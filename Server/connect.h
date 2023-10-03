#ifndef CONNECT_H
#define CONNECT_H

#include <QWidget>
#include "Database.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace Ui {
class connect;
}

class connect : public QWidget
{
    Q_OBJECT

public:
    explicit connect(QWidget *parent = nullptr);
    ~connect();

signals:


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::connect *ui;
};

#endif // CONNECT_H
