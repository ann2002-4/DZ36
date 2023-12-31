#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTimer>

int MainWindow::kInstanceCount=0;

MainWindow::MainWindow(int userId,QString Qemail,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userId (userId),
     m_Qemail(Qemail)
{
    ui->setupUi(this);
    kInstanceCount++;
    auto timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateChats);
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    kInstanceCount--;
    if(kInstanceCount<=0){qApp->exit(0);};
}

MainWindow *MainWindow::createClient()
{
    StartScreen s;
    auto result=s.exec();
    if(result==QDialog::Rejected)
    {return nullptr;};
    auto w= new MainWindow(s.user_id(),s.getQemail());
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{
  addChatMessage(m_Qemail.toStdString(),ui->messageLineEdit->text().toStdString());
}


void MainWindow::on_privateMessageButton_clicked()
{
  QDialog dial(this);
  dial.setModal(true);
  auto l=new QVBoxLayout();
  dial.setLayout(l);
  auto userListWgt=new QListWidget(&dial);   
  l->addWidget(userListWgt);
  auto buttonBox=new QDialogButtonBox(QDialogButtonBox::Ok |QDialogButtonBox::Cancel,&dial);
  l->addWidget(buttonBox);

  connect(buttonBox,&QDialogButtonBox::accepted, &dial,&QDialog::accept);
  connect(buttonBox,&QDialogButtonBox::rejected, &dial,&QDialog::reject);

  auto userList=getUserList();
  for(auto user:userList)
  {userListWgt->addItem(QString::fromStdString(user));};

  userListWgt->setCurrentRow(0);

  auto result= dial.exec();
  auto email_receiver = userListWgt->currentItem()->text().toStdString();
  if(result==QDialog::Accepted && userListWgt->currentItem())
  {
      addPrivateMessage(m_Qemail.toStdString(),
                                 email_receiver,
                                 ui->messageLineEdit->text().toStdString());
  }

}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient();
    if(w)
    w->show();
}


void MainWindow::on_actionCloseThisClient_triggered()
{
    this->close();
}

void MainWindow::updateChats()
{
    QSqlQueryModel model;
    model.setQuery("SELECT rd.email AS sender_name, hd.message "
                  "FROM registration_data rd "
                  "JOIN history_data hd ON rd.id_user = hd.id_sender");

    QString chat;
    for (int row = 0; row < model.rowCount(); ++row) {
     QString email = model.record(row).value("sender_name").toString();
    QString message = model.record(row).value("message").toString();
    auto resultString =  email + ": " + message + "\n";
    chat.append(resultString+ "\n");
    }
    if(ui->commonChatBrowser->toPlainText()!=chat)
    ui->commonChatBrowser->setText(chat);
    chat.clear();



    

    model.setQuery("SELECT id_sender,id_receiver,message "
                   "FROM history_private_data "
                   " WHERE (id_sender=\'"+getid(m_Qemail)+"\') OR(id_receiver=\'"+getid(m_Qemail)+"\') ");

    // Выводим результаты запроса
    for (int row = 0; row < model.rowCount(); ++row) {
    QString Qid = model.record(row).value("id_sender").toString();
    QString Qemail=getQemail(Qid);
    QString message = model.record(row).value("message").toString();

    chat.append(Qemail + ":" + message + "\n");
    }

    auto current = ui->privateChatBrowser->toPlainText();
    if(ui->privateChatBrowser->toPlainText()!=chat)
    ui->privateChatBrowser->setText(chat);
};


