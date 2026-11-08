#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QChartView>
#include <QtCharts>

class Employe
{
public:
    Employe();
    Employe(int,QString,QString,QString,QString,QString,QString);
    int getid();
    QString getnumero_telephone();
    QString getsalaire();
    QString getnom();
    QString getprenom();
    QString getdate_naissance();
    QString getimage();
    void setid(int);
    void setnumero_telephone(QString) ;
    void setsalaire(QString);
    void setnom(QString);
    void setprenom(QString);
    void setdate_naissance(QString);
    void setimage(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool update();
    QSqlQueryModel* Rechercher(QString);
    QSqlQueryModel* tri();
    void genererPDFact();
    void employe();
    QChartView * stat();
    QSqlQueryModel* tri_alpha();
   // QSqlQueryModel* tri_salaire();


private:
    int id;
    QString nom,prenom,numero_telephone,salaire,date_naissance,image;

};

#endif // EMPLOYE_H
