#ifndef DIALOG_MAILING_H
#define DIALOG_MAILING_H

#include <QDialog>

namespace Ui {
class Dialog_Mailing;
}

class Dialog_Mailing : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Mailing(QWidget *parent = nullptr);
    explicit Dialog_Mailing(QString,QString,QString,QWidget *parent = nullptr);
    ~Dialog_Mailing();
private slots:
void set_tmpemail(QString e){tmpemail=e;}

void on_envoyer_dialog_2_clicked();

private:
    Ui::Dialog_Mailing *ui;
    QString tmpemail;
};

#endif // DIALOG_MAILING_H
