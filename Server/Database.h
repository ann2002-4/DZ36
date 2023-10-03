#ifndef DATABASE_H
#define DATABASE_H


#include <QWidget>
#include <memory>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <vector>
#include <QMessageBox>
#include <QWidget>


bool createConnection();

std::vector<std::string> getUserList();
QString getid(QString Qemail);
QString getQemail(QString Qid);


#endif // DATABASE_H
