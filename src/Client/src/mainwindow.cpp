#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QListWidget>
#include "infodlg.h"
#include "forum.h"
#include "usermanager.h"
#include <QDebug>
#include "postdlg.h"
#include "editdlg.h"
#include "chooseboarddlg.h"
#include <QMessageBox>
#include <QDateTime>
#include <QStringList>
#include "Socket.h"
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("C++ 学习论坛");
    rec.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showForum(QDialog *dlg)
{
    dlg->hide();
    this->show();
    ui->listLeft->clear();
    ui->listRight->clear();
}

void MainWindow::on_logoutBtn_clicked()//点击注销
{
    this->hide();
    Socket::getInstance()->logOut(UserManager::getInstance()->getCurrentUser()->getUsername());
    UserManager::getInstance()->logOut();
    emit show_Log_in();
}

void MainWindow::on_PersonalInfoBtn_clicked()//点击个人信息
{
    InfoDlg* info = new InfoDlg(this);
    info->show();
}

void MainWindow::on_checkBoards_clicked()
{
    ui->listLeft->clear();
    ui->listRight->clear();
    ui->listLeft->addItem("双击版块名显示帖子");
    ui->listLeft->item(0)->setFlags(false);//使之不可点
    //获取所有版块名称
    QStringList names = Forum::getInstance()->getBoardNames().split('*');
    ui->listLeft->addItems(names);
}

void MainWindow::on_queryUsers_clicked()
{
    ui->listLeft->clear();
    ui->listRight->clear();
    ui->listLeft->addItem("双击用户名显示详细信息");
    ui->listLeft->item(0)->setFlags(false);
    QStringList names = UserManager::getInstance()->getUserNames().split('*');
    ui->listLeft->addItems(names);
}

void MainWindow::on_listLeft_doubleClicked(const QModelIndex &index)
{
    if(index.data().toString() == ""){
        return;
    }
    QString s = ui->listLeft->item(0)->text();
    QStringList info;
    if(s == QString("双击版块名显示帖子")){
        info.append("点此发布新帖~~");
        Forum::getInstance()->switchBoard(index.data().toString());
        rec.clear();
        QList<QString> names = Forum::getInstance()->getCurrentBoard()->getPostsTitles();
        //将与帖子名称对应的帖子ID进行记录
        for(int i = 0;i < names.size();i ++){
            rec.append(names[i]);
            i ++;
            info.append(names[i]);
        }
    }
    else{
        //int currentRow = ui->listLeft->currentRow();//当前单击选中ListLeft控件的行号（第几行）
        info = UserManager::getInstance()->getUserInfo(index.data().toString()).split('*');
    }
    ui->listRight->clear();
    ui->listRight->addItems(info);
}

void MainWindow::on_listRight_doubleClicked(const QModelIndex &index)
{
    if(index.data().toString() == ""){
        return;
    }
    QString s = ui->listLeft->item(0)->text();
    if(s == QString("双击版块名显示帖子")){
        if(index.data().toString() == QString("点此发布新帖~~")){
            if(UserManager::getInstance()->getCurrentUser()->getType() == 4){
                QMessageBox::warning(this, tr("Error"),
                                      tr("the user is anonymous!\nFail to post!"),
                                      QMessageBox::Yes);
            }
            else{
                EditDlg* dlg = new EditDlg();
                if(dlg->exec() == QDialog::Accepted){//发布帖子后刷新列表
                    flashListRight();
                }
            }
        }
        else{
            int currentRow = ui->listRight->currentRow();
            QStringList info = Socket::getInstance()->getPostInfo(rec[currentRow-1]);
            qDebug() << "info.length() = " << info.length() << endl;
            if(info.length() == 7){//若成功读取到了帖子
                Post* post = new Post(info.at(0),info.at(1),info.at(2),info.at(3),info.at(4),info.at(5).toInt(),info.at(6));
                PostDlg* postdlg = new PostDlg(post);
                postdlg->show();
                if(postdlg->exec() == QDialog::Accepted){
                    flashListRight();
                }
                else{
                    delete post;
                }
            }
            else{//若帖子已经被删除，则报错提示
                QMessageBox::warning(this, tr("Warning"),
                                      tr("the post has already been removed!"),
                                      QMessageBox::Yes);
                flashListRight();//刷新列表
            }
        }
    }
    else{
        //若为管理员
        if(UserManager::getInstance()->getCurrentUser()->getType() == 3){
            int currentRow = ui->listRight->currentRow();
            if(currentRow == 1){
                QString type = index.data().toString();
                type = type.mid(5);
                QString id = ui->listRight->item(2)->text();
                id = id.mid(3);
                if(type == "普通会员"){
                    QMessageBox msgBox;
                    msgBox.setText(QString("是否要任命版主？"));
                    QPushButton *yesBtn = msgBox.addButton(QMessageBox::Yes);
                    msgBox.addButton(QMessageBox::No);
                    msgBox.exec();
                    if (msgBox.clickedButton() == yesBtn) {
                        ChooseBoardDlg* dlg = new ChooseBoardDlg(id);
                        dlg->show();
                        if(dlg->exec() == QDialog::Accepted){
                            flashListRight();
                        }
                    }
                }
                else if(type == "版主"){
                    QMessageBox msgBox;
                    msgBox.setText(QString("是否要取消版主任命？"));
                    QPushButton *yesBtn = msgBox.addButton(QMessageBox::Yes);
                    msgBox.addButton(QMessageBox::No);
                    msgBox.exec();
                    if (msgBox.clickedButton() == yesBtn) {
                        UserManager::getInstance()->convertToMember(id);
                        flashListRight();
                    }
                }
            }
        }
    }
}

void MainWindow::flashListRight()
{
    QString s = ui->listLeft->item(0)->text();
    QStringList info;
    if(s == QString("双击版块名显示帖子")){
        info.append("点此发布新帖~~");
        rec.clear();
        //刷新后，重新读取该板块中所有帖子的信息，并进行记录
        QList<QString> names = Forum::getInstance()->getCurrentBoard()->getPostsTitles();
        for(int i = 0;i < names.size();i ++){
            rec.append(names[i]);
            i ++;
            info.append(names[i]);
        }
    }
    else{
        //当前单击选中ListLeft控件的行号（第几行）
        info = UserManager::getInstance()->getUserInfo(ui->listLeft->item(ui->listLeft->currentRow())->text()).split('*');
    }
    ui->listRight->clear();
    ui->listRight->addItems(info);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::question(this,tr("Last Hint"),
                                       tr("Are you sure you want to quit?"),
                                       QMessageBox::Yes|QMessageBox::Default,
                                       QMessageBox::No|QMessageBox::Escape);
    if (result == QMessageBox::Yes){
        Socket::getInstance()->logOut(UserManager::getInstance()->getCurrentUser()->getUsername());
        delete Forum::getInstance();
        event->accept();
    }
    else{
        event->ignore();
    }
}
