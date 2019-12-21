#ifndef REGISTERDLG_H
#define REGISTERDLG_H

#include <QDialog>

namespace Ui {
class RegisterDlg;
}

class RegisterDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDlg(QWidget *parent = 0);
    ~RegisterDlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegisterDlg *ui;
};

#endif // REGISTERDLG_H
