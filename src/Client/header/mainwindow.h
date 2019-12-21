#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QCloseEvent>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);//重构关闭事件
public slots:
    void showForum(QDialog* dlg);//显示论坛
private slots:
    void on_logoutBtn_clicked();//点击注销
    void on_PersonalInfoBtn_clicked();//点击个人信息按钮

    void on_checkBoards_clicked();//点击查看板块

    void on_queryUsers_clicked();//点击查询用户

    void on_listLeft_doubleClicked(const QModelIndex &index);//展示框左边点击

    void on_listRight_doubleClicked(const QModelIndex &index);//展示框右边点击

signals:
    void show_Log_in();//信号，成功登陆

private:
    Ui::MainWindow *ui;
    void flashListRight();//刷新右侧显示框
    QList<QString> rec;//存储当前展示版块的帖子id

};

#endif // MAINWINDOW_H
