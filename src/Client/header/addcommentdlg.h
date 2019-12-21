#ifndef ADDCOMMENTDLG_H
#define ADDCOMMENTDLG_H

#include <QDialog>
#include "post.h"

namespace Ui {
class AddCommentDlg;
}

class AddCommentDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddCommentDlg(Post* post,QWidget *parent = 0);
    ~AddCommentDlg();

private slots:
    void on_submitBtn_clicked();//点击提交按钮

private:
    Ui::AddCommentDlg *ui;
    Post* post;//指向当前展示的帖子
};

#endif // ADDCOMMENTDLG_H
