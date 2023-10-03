#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Database.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static int kInstanceCount;//Cancel не будет приводить к закрытию программы
    void updateChats();

private slots:
    void on_Choose_userButton_clicked();

    void on_BanButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
