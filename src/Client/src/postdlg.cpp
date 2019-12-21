#include "postdlg.h"
#include "ui_postdlg.h"
#include "usermanager.h"
#include <QTextBrowser>
#include "forum.h"
#include <QMessageBox>
#include "addcommentdlg.h"
#include "modifypostdlg.h"
#include "Socket.h"

PostDlg::PostDlg(Post *post, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("帖子信息"));
    this->post = post;

    flashPost();
    flashComments();
    flashButtons();
}

PostDlg::~PostDlg()
{
    delete ui;
}

void PostDlg::on_deleteBtn_clicked()
{
    Forum::getInstance()->switchBoard(post->getBoardName());//获得当前版块名称
    Forum::getInstance()->getCurrentBoard()->deletePost(post->getId());//对版块内指定帖子进行删除
    QMessageBox::information(this,tr("Success"),
                             tr("the post has been deleted succefully!"),
                             QMessageBox::Ok);
    accept();
}

void PostDlg::on_commentBtn_clicked()
{
    AddCommentDlg* dlg = new AddCommentDlg(post);
    if(dlg->exec() == QDialog::Accepted){
        flashComments();
        flashButtons();
    }
}

void PostDlg::on_modifyBtn_clicked()
{
    ModifyPostDlg* dlg = new ModifyPostDlg(post);
    if(dlg->exec() == QDialog::Accepted){
        flashPost();
        flashButtons();
    }
}

void PostDlg::flashPost()
{
    QString title = post->getTitle();
    QString contents = post->getContents();
    QString authorId = post->getAuthorId();
    QString authorName = UserManager::getInstance()->getUserName(authorId);
    ui->titleBrowser->setText(QString("标题：") + title);
    if(post->isPostModify()){
        ui->titleBrowser->setText(QString(QString("标题：") + title + "(已修改)"));
    }
    ui->authorBrowser->setText(QString("作者：") + authorName);
    ui->timeBrowser->setText(QString("发表时间：") + post->getPostedTime());
    ui->contentsBrowser->setText(QString("正文：\n") + contents);
}

void PostDlg::flashComments()
{
    QStringList comments = Socket::getInstance()->getComments(post->getId());
    int size = comments.at(0).toInt();
    if(!size){
        ui->commentsBrowser->setText("当前帖子暂无评论");
    }
    else{
        ui->commentsBrowser->setText(QString("评论如下:\n-------------------------"));
        for(int i = 0;i < size;i ++){
            QString authorName = UserManager::getInstance()->getUserName(comments.at(3 * i + 2));
            if(i == 0){
                ui->commentsBrowser->append(QString("沙发"));
            }
            else if(i == 1){
                ui->commentsBrowser->append(QString("板凳"));
            }
            else{
                ui->commentsBrowser->append(QString("%1楼").arg(i+1));
            }
            ui->commentsBrowser->append(QString("发信人：") + authorName +
                                        QString("\nRe：") + comments.at(3 * i + 1) +
                                        QString("\n时间：") + comments.at(3 * i + 3));
            ui->commentsBrowser->append(QString("-------------------------"));
        }
    }
}

void PostDlg::flashButtons()
{
    int userType = UserManager::getInstance()->getCurrentUser()->getType();
    QString curUserId = UserManager::getInstance()->getCurrentUser()->getId();
    if(userType == 4){
        ui->deleteBtn->setVisible(false);
        ui->modifyBtn->setVisible(false);
        ui->commentBtn->setVisible(false);
    }
    else{
        if(userType == 1){//如果是普通用户
            if(curUserId != post->getAuthorId()){
                ui->deleteBtn->setVisible(false);
            }
            if(post->hasComment()){
                ui->deleteBtn->setVisible(false);
            }
        }
        else if(userType == 2){//如果是版主
            Moderator* ptr = (Moderator*)UserManager::getInstance()->getCurrentUser();
            if(curUserId != post->getAuthorId() && ptr->getManagementName() != post->getBoardName()){
                ui->deleteBtn->setVisible(false);
            }
        }
        if(curUserId != post->getAuthorId()){
            ui->modifyBtn->setVisible(false);//只有作者才允许修改帖子
        }
    }

}
