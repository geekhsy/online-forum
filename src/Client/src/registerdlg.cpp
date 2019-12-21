#include "registerdlg.h"
#include "ui_registerdlg.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <usermanager.h>

RegisterDlg::RegisterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("注册"));
    ui->nameEdit->setPlaceholderText("请输入用户名");
    ui->pwdEdit->setPlaceholderText("请输入密码");
    ui->rePwdEdit->setPlaceholderText("请再次输入密码");
}

RegisterDlg::~RegisterDlg()
{
    delete ui;
}

void RegisterDlg::on_pushButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString password = ui->pwdEdit->text();
    QString repassword = ui->rePwdEdit->text();
    bool state1 = ui->manCheck->checkState();
    bool state2 = ui->womanCheck->checkState();
    if(state1 && state2){
        QMessageBox::warning(this, tr("Error"),
                              tr("please just choose one sex!"),
                              QMessageBox::Yes);
    }
    else if(!state1 && !state2){
        QMessageBox::warning(this, tr("Error"),
                              tr("please choose a sex!"),
                              QMessageBox::Yes);
    }
    else if(name.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the username!"),
                              QMessageBox::Yes);
    }
    else if(password.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the password!"),
                              QMessageBox::Yes);
    }
    else if(password != repassword){
        QMessageBox::warning(this, tr("Error"),
                              tr("前后两次输入密码不一样!"),
                              QMessageBox::Yes);
    }
    else if(name.contains('*')){
        QMessageBox::warning(this, tr("Error"),
                              tr("the * can not in your username!"),
                              QMessageBox::Yes);
    }
    else if(UserManager::getInstance()->Register(name,password))
    {
        QMessageBox::information(this,tr("Ok"),
                                 tr("you have registered successfully!"),
                                 QMessageBox::Yes);
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("the username has been registered!"),
                             QMessageBox::Yes);
        ui->nameEdit->setFocus();
    }
}
