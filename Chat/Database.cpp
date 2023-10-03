#include "Database.h"

bool createConnection()//сооединение с базой
{   db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("postgres");

    if(!db.open())
    {
        QMessageBox::warning(0,"Ошибка подключения.", db.lastError().text());
        return false;
    }
    else
    {
        QMessageBox::information(0,"Успешно", "Соединение с БД установлено!");
         return true;
    }
};




int addUser(std::string email)
{
    int j=0;//нет @
    for (int i = 0; i < email.length(); i++)
    {
        if (email[i] == '@') { j=1; }
    };

    QString Qemail = QString::fromStdString(email);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT email FROM registration_data WHERE (email=\'"+Qemail+"\')");

    if (model->rowCount() >0) { j=2; }

    return j;

}

int checkPassword(std::string email, std::string password)
{
    int j=0;//0 - email не верный
    QString Qemail = QString::fromStdString(email);
    QString Qpassword = QString::fromStdString(password);
    QString id_user;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {    j=1;
        QModelIndex index = model->index(0, 0); // индекс первой ячейки
        id_user = model->data(index).toString(); // получение значения ячейки в виде строки
        model->setQuery("SELECT * FROM authorization_data WHERE (id_user=\'"+id_user+"\') AND (password=\'"+Qpassword+"\') ");
        if (model->rowCount() > 0)
        {
            j=2;
        }
    }
    return j;
}

void addChatMessage(std::string email, std::string message)
{
    QSqlQuery query;
    QString Qemail = QString::fromStdString(email);
    QString Qmessage = QString::fromStdString(message);
    QString id_user;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {
        QModelIndex index = model->index(0, 0); // индекс первой ячейки
        id_user = model->data(index).toString(); // получение значения ячейки в виде строки
    query.prepare("INSERT INTO history_data (id_sender, message) VALUES (:id_sender,:message)");
    query.bindValue(":id_sender", id_user);
    query.bindValue(":message", Qmessage);
    query.exec();};
}

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

void addPrivateMessage(std::string email,std::string email_receiver, std::string message)
{    QSqlQuery query;

    QString id_user_sender;
    QString id_user_receiver;
    QString Qemail = QString::fromStdString(email);
     QString Qemail_receiver = QString::fromStdString(email_receiver);
    QString Qmessage = QString::fromStdString(message);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {        QModelIndex index = model->index(0, 0); // индекс первой ячейки
        id_user_sender = model->data(index).toString(); // получение значения ячейки в виде строки
        model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail_receiver+"\')");

        if (model->rowCount() > 0){
        index = model->index(0, 0); // индекс первой ячейки
        id_user_receiver = model->data(index).toString(); // получение значения ячейки в виде строки
        query.prepare("INSERT INTO history_private_data (id_sender,id_receiver, message) VALUES (:id_sender,:id_receiver, :message)");
        query.bindValue(":id_sender", id_user_sender);
        query.bindValue(":id_receiver", id_user_receiver);
        query.bindValue(":message", Qmessage);

        query.exec();};
        }
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
