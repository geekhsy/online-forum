#include "infodlg.h"
#include "ui_infodlg.h"
#include "usermanager.h"

InfoDlg::InfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("查看信息");
    ui->titleLabel->setText("个人信息");
    int type = UserManager::getInstance()->getCurrentUser()->getType();
    if(type == 1){
        ui->typeLabel->setText("type：普通会员");
    }
    else if(type == 2){
        ui->typeLabel->setText("type：版主");
    }
    else if(type == 3){
        ui->typeLabel->setText("type：管理员");
    }
    else if(type == 4){
        ui->typeLabel->setText("type：匿名用户");
    }
    ui->idLabel->setText("id：" + UserManager::getInstance()->getCurrentUser()->getId());
    ui->nameLabel->setText("name：" + UserManager::getInstance()->getCurrentUser()->getUsername());

}

InfoDlg::~InfoDlg()
{
    delete ui;
}

