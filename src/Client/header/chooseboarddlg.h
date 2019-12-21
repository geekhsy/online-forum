#ifndef CHOOSEBOARDDLG_H
#define CHOOSEBOARDDLG_H

#include <QDialog>

namespace Ui {
class ChooseBoardDlg;
}

class ChooseBoardDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseBoardDlg(QString id,QWidget *parent = 0);
    ~ChooseBoardDlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChooseBoardDlg *ui;
    QString id;
};

#endif // CHOOSEBOARDDLG_H
