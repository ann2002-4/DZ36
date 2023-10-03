#include "Database.h"


std::vector<std::string> getUserList()
{    std::vector<std::string> userList;
    std::vector<QString> QuserList;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT email FROM registration_data where status = 'active'");

    for (int row = 0; row < model->rowCount(); ++row) {
         auto email = model->data(model->index(row, 0)).toString();
         QuserList.push_back(email);
    };
    for (const auto &qstr : QuserList) {
         userList.push_back(qstr.toStdString());
    }
    return userList;
}

QString getid(QString Qemail)
{
    QString id_user_sender;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {        QModelIndex index = model->index(0, 0); // индекс первой ячейки
         id_user_sender = model->data(index).toString();
    }; // получение значения ячейки в виде строки
    return id_user_sender;

}

QString getQemail(QString Qid)
{
    QString Qmale;
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery("SELECT email FROM registration_data WHERE (id_user=\'"+Qid+"\')");
    if (model->rowCount() > 0)
    {        QModelIndex index = model->index(0, 0); // индекс первой ячейки
         Qmale = model->data(index).toString();
    }; // получение значения ячейки в виде строки
    return Qmale;

}
