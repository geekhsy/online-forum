#include "mainwindow.h"
#include "logindlg.h"
#include <QApplication>
#include <QWidget>
#include <fstream>
#include "forum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->resize(910,470);
    LoginDlg* dlg = new LoginDlg();
    QObject::connect(dlg,&LoginDlg::log_in_accepted,w,&MainWindow::showForum);
    QObject::connect(w,&MainWindow::show_Log_in,dlg,&LoginDlg::showLogin);
    dlg->show();
    a.exec();
    return 0;
}
