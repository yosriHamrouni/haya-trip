#ifndef CLIENT_H
#define CLIENT_H
#include <QString>

#include <QSqlQueryModel>
#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QChartView>
QT_CHARTS_USE_NAMESPACE

class Client
{
public:
    Client();
    Client(int,QString,QString,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString get_tel();
    QString get_rdv();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
     void setemail(QString);
      void set_tel(QString);
       void set_rdv(QString);
    bool ajouter();
    QSqlQueryModel *afficher();
      bool supprimer(int);
      bool update();
           bool search();
               QSqlQueryModel * search(QString);
                   QSqlQueryModel  *tri();
             bool genererPDFact();
              QChartView * stat();



private:
    int idc;
    QString nom,prenom,email,tel,rdv;






};

#endif // CLIENT_H
