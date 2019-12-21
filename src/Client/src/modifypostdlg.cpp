#include "modifypostdlg.h"
#include "ui_modifypostdlg.h"
#include <QTextEdit>
#include <QMessageBox>

ModifyPostDlg::ModifyPostDlg(Post *post, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPostDlg)
{
    ui->setupUi(this);
    this->post = post;
    this->setWindowTitle(QString("修改帖子"));
    ui->titleEdit->setText(post->getTitle());
    ui->postEdit->setPlainText(post->getContents());
}

ModifyPostDlg::~ModifyPostDlg()
{
    delete ui;
}

void ModifyPostDlg::on_submitBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString contents = ui->postEdit->toPlainText();
    if(contents.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the contents!"),
                              QMessageBox::Yes);
    }
    else if(title.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the title!"),
                              QMessageBox::Yes);
    }
    else{
        post->rewrite(title,contents);
        QMessageBox::information(this, tr("Success"),
                                  tr("you have rewritten the post successfully!"),
                                  QMessageBox::Ok);
        accept();
    }
}
