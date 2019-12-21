#ifndef INFODLG_H
#define INFODLG_H

#include <QDialog>

namespace Ui {
class InfoDlg;
}

class InfoDlg : public QDialog
{
    Q_OBJECT

public:
//    static InfoDlg* getInstance();
//    static InfoDlg* m_instance;
    explicit InfoDlg(QWidget *parent = 0);
    ~InfoDlg();

private:
//    InfoDlg(const InfoDlg* other);
    Ui::InfoDlg *ui;
};


#endif // INFODLG_H
