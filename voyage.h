#ifndef VOYAGE_H
#define VOYAGE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>

class voyage
{
private:
    int num_voyage;
    QString depart, destination;
    QString date_depart;
    QString date_retour;


public:
    voyage();
    voyage(int, QString,QString,QString,QString);
    int getnum_voyage();
    QString getdepart();
    QString getdestination();
    QString getdate_depart();
    QString getdate_retour();


    void setnum_voyage(int);
    void setdepart(QString);
    void setdestination(QString);
    void setdate_depart(QString);
    void setdate_retour(QString);


public:
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool update();
    QSqlQueryModel * rechercher(QString );
    QSqlQueryModel * rechercher2(QString );
    QSqlQueryModel * rechercher3(QString );
    QSqlQueryModel * tri();
    QSqlQueryModel * tri2();
    QSqlQueryModel * tri3();
    void genererPDFact();
  // QSqlQueryModel * stats();




};

#endif // VOYAGE_H
