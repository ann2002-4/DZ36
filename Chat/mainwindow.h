#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "Database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int userId,QString Qemail,QWidget *parent = nullptr);//конструктор
    ~MainWindow();
    static MainWindow* createClient();// тестовая функция для переключения в StartScreen, через кнопку another client
    static int kInstanceCount;//Cancel не будет приводить к закрытию программы

private slots:

    void on_messageLineEdit_returnPressed();//messageLineEdit

    void on_sendMessageButton_clicked();//Send to all

    void on_privateMessageButton_clicked();//Send private

    void on_actionOpen_another_client_triggered();//actionOpen_another_client

    void on_actionCloseThisClient_triggered();//actionCloseThisClient

    void updateChats();

private:
    Ui::MainWindow *ui;
    int m_userId;
    QString m_Qemail;


};

#endif // MAINWINDOW_H
