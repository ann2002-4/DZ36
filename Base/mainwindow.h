#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <vector>
#include <QMessageBox>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void create_base();


private:

    Ui::MainWindow *ui;
private slots:
    void on_buttonBox_accepted();//Ok\ Cancel если принято

    void on_buttonBox_rejected();//Ok\ Cancel если отклонено


};
#endif // MAINWINDOW_H
