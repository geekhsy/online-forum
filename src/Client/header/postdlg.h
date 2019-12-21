#ifndef POSTDLG_H
#define POSTDLG_H

#include <QDialog>
#include "post.h"

namespace Ui {
class PostDlg;
}

class PostDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PostDlg(Post* post,QWidget *parent = 0);
    ~PostDlg();

private slots:
    void on_deleteBtn_clicked();//点击删除帖子

    void on_commentBtn_clicked();//点击发表评论

    void on_modifyBtn_clicked();//点击修改帖子

private:
    void flashPost();//刷新帖子信息
    void flashComments();//刷新评论区
    void flashButtons();//刷新按钮
    Ui::PostDlg *ui;
    Post* post;
};

#endif // POSTDLG_H
