#ifndef RESERVATION_H
#define RESERVATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QTableView>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QDate>

class reservation
{
public:
    reservation();
    reservation(int,QString,QString,int);

    int getid();
    QString getnom();
    QString getprenom();
    int getmontant();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setmontant(int);

    bool ajouterS();
    bool modifierS();
    bool supprimerS(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_Montant();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void chercheID(QTableView *table, int x);
    void chercheMont(QTableView *table, int x);
    void chercheNom(QTableView *table, QString x);

private:
    int ID;
    QString NOM;
    QString PRENOM;
    int MONTANT;
};

#endif // RESERVATION_H
