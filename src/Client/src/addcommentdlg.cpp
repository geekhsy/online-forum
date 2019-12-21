#include "addcommentdlg.h"
#include "ui_addcommentdlg.h"
#include <QTextEdit>
#include <QMessageBox>

AddCommentDlg::AddCommentDlg(Post* post,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCommentDlg)
{
    ui->setupUi(this);
    this->post = post;
    this->setWindowTitle(QString("发表评论"));
    ui->commentEdit->setPlaceholderText(QString("请在此处输入评论..."));

}

AddCommentDlg::~AddCommentDlg()
{
    delete ui;
}

void AddCommentDlg::on_submitBtn_clicked()
{
    QString comment = ui->commentEdit->toPlainText();
    if(comment.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the comments!"),
                              QMessageBox::Yes);
    }
    else{
        post->addComment(comment);
        accept();
    }
}
