#include "chooseboarddlg.h"
#include "ui_chooseboarddlg.h"
#include "forum.h"
#include "usermanager.h"
#include <QMessageBox>

ChooseBoardDlg::ChooseBoardDlg(QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseBoardDlg)
{
    ui->setupUi(this);
    this->id = id;
    this->setWindowTitle("任命版主");
    QStringList names = Forum::getInstance()->getBoardNames().split('*');
    ui->listBoard->addItem(QString("选定版块单击确定完成任命"));
    ui->listBoard->addItems(names);
}

ChooseBoardDlg::~ChooseBoardDlg()
{
    delete ui;
}

void ChooseBoardDlg::on_pushButton_clicked()
{
    int currentRow = ui->listBoard->currentRow();
    if(currentRow == -1 || currentRow == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("you have not choose any board!"),
                              QMessageBox::Yes);
    }
    else{
        QString name = ui->listBoard->item(currentRow)->text();
        UserManager::getInstance()->convertToModerator(id,name);
        accept();
    }
}
