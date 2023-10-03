#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include <QVBoxLayout>//вертикальное выравнивание
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTimer>//таймер

int MainWindow::kInstanceCount=0;

MainWindow::MainWindow(int userId,QString Qemail,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userId (userId),
     m_Qemail(Qemail)
{
    ui->setupUi(this);
    kInstanceCount++;
    auto timer=new QTimer(this);//завели новый таймер, будет периодически обновлять поля с сообщениями
    connect(timer,&QTimer::timeout,this,&MainWindow::updateChats);//каждый раз как срабатывает таймер,обновляется чат(информация из БД)
    timer->start(10);//таймер срабатывает раз в 10 миллисекунд
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
    if(result==QDialog::Rejected)//QDialog::Rejected = 0
    {return nullptr;};//мы ничего не создали
    auto w= new MainWindow(s.user_id(),s.getQemail());
    w->setAttribute(Qt::WA_DeleteOnClose);//удаляет виджет при закрытии и попадаем в деструктор
    return w;
}



void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();//при нажатии в поле Enter, будет отправляться для всех
}


void MainWindow::on_sendMessageButton_clicked()
{
  addChatMessage(m_Qemail.toStdString(),ui->messageLineEdit->text().toStdString());
}


void MainWindow::on_privateMessageButton_clicked()
{
  QDialog dial(this);//создаем отдельное окно
  dial.setModal(true);//прерывает работу программы, пока не закроем диалог
  auto l=new QVBoxLayout();//auto-QVBoxLayout, new QVBoxLayout - удаляется автоматически для освобождения памяти
  dial.setLayout(l);//устанавливаем QVBoxLayout l
  auto userListWgt=new QListWidget(&dial);   //auto-QListWidget
  l->addWidget(userListWgt);
  auto buttonBox=new QDialogButtonBox(QDialogButtonBox::Ok |QDialogButtonBox::Cancel,&dial);//auto - QDialogButtonBox
  l->addWidget(buttonBox);

  connect(buttonBox,&QDialogButtonBox::accepted, &dial,&QDialog::accept);
  connect(buttonBox,&QDialogButtonBox::rejected, &dial,&QDialog::reject);

  auto userList=getUserList();//создает список
  for(auto user:userList)//заполняет имеющимися юзерами
  {userListWgt->addItem(QString::fromStdString(user));};

  userListWgt->setCurrentRow(0);//всегда будет выбран в начале 1-ый юзер в списке, подразумевается, что в чате зарегистрирован хотя бы 1

  auto result= dial.exec();
  auto email_receiver = userListWgt->currentItem()->text().toStdString();
  if(result==QDialog::Accepted && userListWgt->currentItem())// положительный исход, при отрицательном Диалог удалится && существует хотя бы 1 возможный получатель
  {
      addPrivateMessage(m_Qemail.toStdString(),
                                 email_receiver,
                                 ui->messageLineEdit->text().toStdString());//сообщение
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
    // Выводим результаты запроса
    for (int row = 0; row < model.rowCount(); ++row) {
     QString email = model.record(row).value("sender_name").toString();
    QString message = model.record(row).value("message").toString();
    auto resultString =  email + ": " + message + "\n";
    chat.append(resultString+ "\n");
    }
    if(ui->commonChatBrowser->toPlainText()!=chat)
    ui->commonChatBrowser->setText(chat);
    // Устанавливаем текст в QTextBrowser
    chat.clear();//очищяем переменную



    

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
    if(ui->privateChatBrowser->toPlainText()!=chat)//если появилось новое сообщение
    ui->privateChatBrowser->setText(chat);//на этом заказнчивается реализация приватного чата
};


