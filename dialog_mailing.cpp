#include "dialog_mailing.h"
#include "ui_dialog_mailing.h"
#include "smtp.h"
#include <QMessageBox>

Dialog_Mailing::Dialog_Mailing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Mailing)
{
    ui->setupUi(this);
    connect(ui->envoyer_dialog_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->annuler_mail_2, SIGNAL(clicked()),this, SLOT(close()));
}
Dialog_Mailing::Dialog_Mailing(QString e,QString n,QString s,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Mailing)
{
    QString contenu="Contenu";
    ui->setupUi(this);

    ui->recipient_2->setText(e);
    // SMTP account comes from the environment (or is typed in the dialog) — never from the source.
    ui->uname->setText(QString::fromLocal8Bit(qgetenv("HAYATRIP_SMTP_USER")));
    ui->passwd_2->setText(QString::fromLocal8Bit(qgetenv("HAYATRIP_SMTP_PASSWORD")));
    ui->passwd_2->setEchoMode(QLineEdit::Password);

    if (s=="Homme")
    {
        ui->message_2->setText("Cher Monsieur "+n+",\n\n"+contenu+"\n\n"+"Cordialement,\n");
    }
    else if (s=="Femme")
    {
        ui->message_2->setText("Chère Madame "+n+",\n\n"+contenu+"\n\n"+"Cordialement,\n");
    }

}
void Dialog_Mailing::on_envoyer_dialog_2_clicked()
{QString status;
    Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd_2->text(), "smtp.gmail.com", 465); //smtp.gmail.com

    smtp->sendMail(ui->uname->text(), ui->recipient_2->text() , ui->subjectLineEdit_2->text() ,ui->message_2->toPlainText());

    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
Dialog_Mailing::~Dialog_Mailing()
{
    delete ui;
}
