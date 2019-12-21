#include "editdlg.h"
#include "ui_editdlg.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QMessageBox>
#include "forum.h"

EditDlg::EditDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("新建帖子"));
    ui->titleEdit->setPlaceholderText(QString("请在此处输入标题..."));
    ui->contentsEdit->setPlaceholderText(QString("请在此处输入正文..."));
}

EditDlg::~EditDlg()
{
    delete ui;
}

void EditDlg::on_submitBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString contents = ui->contentsEdit->toPlainText();
    if(title.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the title!"),
                              QMessageBox::Yes);
    }
    else if(contents.length() == 0){
        QMessageBox::warning(this, tr("Error"),
                              tr("please input the contents!"),
                              QMessageBox::Yes);
    }
    else{
        Forum::getInstance()->getCurrentBoard()->addPost(title,contents);
        QMessageBox::information(this,tr("Success"),
                                 tr("the post has been posting successfully!"),
                                 QMessageBox::Ok);
        accept();
    }
}
