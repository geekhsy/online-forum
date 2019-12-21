#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <usermanager.h>
#include <QDialog>
#include <QLabel>
#include <registerdlg.h>
#include <QCheckBox>
#include <QDebug>
#include "Socket.h"
#include "forum.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::showLogin()
{
    this->show();
}

void LoginDlg::on_loginBtn_clicked()
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    QString username = ui->usrLineEdit->text();
    QString password = ui->pwdLineEdit->text();
    bool isAnonymous = ui->checkBox->isChecked();
    qDebug() << "isAnonymous = " << isAnonymous << endl;
    if(username.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the username!"),
                              QMessageBox::Yes);
    }
    else if(password.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the password!"),
                              QMessageBox::Yes);
    }
    else
    {  
        int type = UserManager::getInstance()->logIn(username,password,ui->checkBox->isChecked());
        if(type == 1){

               emit log_in_accepted(this);
        }
        else if(type == -1){
            QMessageBox::warning(this, tr("Waring"),
                                  tr("the user is already online!"),
                                  QMessageBox::Yes);
            ui->usrLineEdit->setFocus();
        }
        else{
            QMessageBox::warning(this, tr("Waring"),
                                  tr("username or password error!"),
                                  QMessageBox::Yes);
            ui->usrLineEdit->setFocus();
        }
    }
}

void LoginDlg::on_registerBtn_clicked()//点击注册
{
    RegisterDlg* dlg = new RegisterDlg();
    dlg->show();
}

void LoginDlg::closeEvent(QCloseEvent *){
    delete Forum::getInstance();//退出时释放全局变量的内存空间
    accept();
}
