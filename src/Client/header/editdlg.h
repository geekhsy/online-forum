#ifndef EDITDLG_H
#define EDITDLG_H

#include <QDialog>

namespace Ui {
class EditDlg;
}

class EditDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EditDlg(QWidget *parent = 0);
    ~EditDlg();

private slots:
    void on_submitBtn_clicked();

private:
    Ui::EditDlg *ui;
};

#endif // EDITDLG_H
