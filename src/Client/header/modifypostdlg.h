#ifndef MODIFYPOSTDLG_H
#define MODIFYPOSTDLG_H

#include <QDialog>
#include "post.h"

namespace Ui {
class ModifyPostDlg;
}

class ModifyPostDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPostDlg(Post* post,QWidget *parent = 0);
    ~ModifyPostDlg();

private slots:
    void on_submitBtn_clicked();//点击提交按钮

private:
    Ui::ModifyPostDlg *ui;
    Post* post;
};

#endif // MODIFYPOSTDLG_H
