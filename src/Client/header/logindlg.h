#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();
    void closeEvent(QCloseEvent *);
signals:
    void log_in_accepted(QDialog* dlg);
public slots:
    void showLogin();
private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
