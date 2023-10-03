#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <memory>
#include <Database.h>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
signals:
    void RegistrationRequested();
    void accepted(int userId,QString Qemail);
    void rejected();// если отклонено
private slots:
    void on_RegistrationButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::LoginForm *ui;

};

#endif // LOGINFORM_H
