#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);
    setWindowTitle("Вход в систему");
    ui->login->setPlaceholderText("Введите логин");
    ui->password->setPlaceholderText("Введите пароль");
    ui->login->setClearButtonEnabled(true);
    ui->password->setClearButtonEnabled(true);
    ui->password->setEchoMode(QLineEdit::Password);
}

Authorization::~Authorization()
{
    delete dbData;
    delete ui;
}
bool Authorization::checkInput(QString& login, QString& password){
    if (login.isEmpty() || password.isEmpty()) { // Проверка на пустые поля
        QMessageBox::warning(this, "Некорректный ввод", "Пожалуйста, заполните все поля.");
        return false;
    }
    else if (login.length() > 20 || password.length() > 20) { // Проверка на длину не больше 20 символов
        QMessageBox::warning(this, "Некорректный ввод", "Длина логина и пароля должна быть не больше 20 символов.");
        return false;
    }
    else {
        return true;
    }
}
void Authorization::on_authorization_clicked()
{

    if (dbData != nullptr){
        delete dbData;  // Удаление существующего объекта dbData
    }
    dbData = new DatabaseWork();
    QString username = ui->login->text().left(22);
    QString password = ui->password->text().left(22);
    if (checkInput(username, password)) {
        QString responce = dbData->authorization(username, password);
        if (responce == "Вы авторизовались"){
            responce = dbData->fillTable();

            hide();//this->close();
            MainWindow* mwin = new MainWindow(dbData, this);
            mwin->show();
        }
        else{
            QMessageBox::about(this, "Возникли проблемы", responce);
        }
    }
    ui->login->clear();
    ui->password->clear();
}


void Authorization::on_registration_clicked()
{
    if (dbData != nullptr){
        delete dbData;  // Удаление существующего объекта dbData
    }
    dbData = new DatabaseWork();
    QString username = ui->login->text().left(22);
    QString password = ui->password->text().left(22);
    if (checkInput(username, password)) {
        QString responce = dbData->registration(username, password);
        if (responce == "Данные добавлены"){
            responce = dbData->fillTable();//можно потом сюда обработку поставить
            ui->login->clear();
            ui->password->clear();
            hide();//this->close();
            MainWindow* mwin = new MainWindow(dbData, this);
            mwin->show();
        }
        else{
            QMessageBox::about(this, "connect", responce);
        }
    }
}

void Authorization::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information(this,tr("Выход из приложения"),tr("Вы уверены, что хотите выйти из программы?"),tr("OK"), tr("Отменить"),0,1))
    {
    case 0:
        event->accept();
        qApp->quit();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}


