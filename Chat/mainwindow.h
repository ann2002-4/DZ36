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
    explicit MainWindow(int userId,QString Qemail,QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* createClient();
    static int kInstanceCount;

private slots:

    void on_messageLineEdit_returnPressed();

    void on_sendMessageButton_clicked();

    void on_privateMessageButton_clicked();

    void on_actionOpen_another_client_triggered();

    void on_actionCloseThisClient_triggered();

    void updateChats();

private:
    Ui::MainWindow *ui;
    int m_userId;
    QString m_Qemail;


};

#endif // MAINWINDOW_H
