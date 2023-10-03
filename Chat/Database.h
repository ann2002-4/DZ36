#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <vector>
#include <QMessageBox>
#include <QWidget>
#include <memory>

inline QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");


bool createConnection();



int addUser(std::string email);//общая проверка
int checkPassword(std::string email,std::string password);
void addChatMessage(std::string email,std::string message);
void addPrivateMessage(std::string email,std::string email_receiver, std::string message);
QString getid(QString Qemail);
QString getQemail(QString Qid);


std::vector<std::string> getUserList();


#endif // DATABASE_H
