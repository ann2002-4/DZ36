#include "connect.h"
#include "ui_connect.h"

connect::connect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connect)
{
    ui->setupUi(this);
}

connect::~connect()
{
    delete ui;
}

void connect::on_buttonBox_accepted()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(ui->DatabaseEdit->text());
    db.setHostName(ui->HostNameEdit->text());
    db.setDatabaseName(ui->DatabaseNameEdit->text());
    db.setUserName(ui->UserNameEdit->text());
    db.setPassword(ui->PasswordEdit->text());
  if (!db.open()) {
        QMessageBox::warning(0, "Ошибка подключения.", db.lastError().text());
        return; 
    }

    QMessageBox::information(0, "Успешно", "Соединение с БД установлено!");
    auto w= new MainWindow();
    w->show();
    this->close();
     this->setAttribute(Qt::WA_DeleteOnClose);
}

void connect::on_buttonBox_rejected()
{
    close();
}

