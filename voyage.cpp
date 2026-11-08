#include "voyage.h"
#include <QFileDialog>
#include <QSqlQuery>
#include <QtDebug>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QPainter>
#include <QPdfWriter>
#include <QPainter>

#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include"QSortFilterProxyModel"

using namespace std;

voyage::voyage()
{
   num_voyage=0;
   depart="";
   destination="";
   date_depart="";
   date_retour="";

}
voyage::voyage(int num_voyage,QString depart,QString destination,QString date_depart,QString date_retour){
    this->num_voyage=num_voyage;
    this->depart=depart;
    this->destination=destination;
    this->date_depart=date_depart;
    this->date_retour=date_retour;


}
    int voyage::getnum_voyage(){
        return num_voyage;}
    QString voyage:: getdepart(){
        return depart;}
    QString voyage:: getdestination(){
        return destination;}
    QString voyage:: getdate_depart(){
        return date_depart;}
    QString voyage:: getdate_retour(){
        return date_retour;}

    void voyage::setnum_voyage(int num_voyage){
        this->num_voyage=num_voyage;}
    void voyage::setdepart(QString depart){
        this->depart=depart;}
    void voyage::setdestination(QString destination){
        this->destination=destination;}
    void voyage::setdate_depart(QString date_depart){
        this->date_depart=date_depart;}
    void voyage::setdate_retour(QString date_retour){
        this->date_retour=date_retour;}


bool voyage::ajouter(){
       QSqlQuery query;
     QString num_voyage_string= QString::number(num_voyage);
             query.prepare("INSERT INTO VOYAGE (NUM_VOYAGE, DEPART, DESTINATION,DATE_DEPART,DATE_RETOUR) "
                        "VALUES (:num_voyage, :depart, :destination,:date_depart, :date_retour)");
             query.bindValue(0,num_voyage_string);
             query.bindValue(1,depart);
             query.bindValue(2,destination);
             query.bindValue(3,date_depart);
             query.bindValue(4,date_retour);

        return query.exec();
    }
bool voyage::supprimer(int num_voyage){
    QSqlQuery query;
  QString num_voyage_string= QString::number(num_voyage);
           query.prepare("delete from VOYAGE where NUM_VOYAGE= :num_voyage");
          query.bindValue(":num_voyage",num_voyage_string);
    return query.exec();

}
QSqlQueryModel* voyage::afficher(){
   QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT* FROM VOYAGE");
         model->setHeaderData(0, Qt::Horizontal, QObject:: tr("numero_voyage"));
         model->setHeaderData(1, Qt::Horizontal, QObject:: tr("depart"));
         model->setHeaderData(2, Qt::Horizontal, QObject:: tr("destination"));
         model->setHeaderData(3, Qt::Horizontal, QObject:: tr("date_depart"));
         model->setHeaderData(4, Qt::Horizontal, QObject:: tr("date_retour"));



 return model;
}

bool voyage::update()
        {

    QSqlQuery query;
  QString num_voyage_string= QString::number(num_voyage);

          query.prepare("UPDATE VOYAGE SET NUM_VOYAGE='"+num_voyage_string+"', DEPART='"+depart+"', DESTINATION='"+destination+"',DATE_DEPART='"+date_depart+"',DATE_RETOUR='"+date_retour+"' where NUM_VOYAGE='"+num_voyage_string+"' ");

          query.bindValue(0,num_voyage_string);
          query.bindValue(1,depart);
          query.bindValue(2,destination);
          query.bindValue(3,date_depart);
          query.bindValue(4,date_retour);

     return query.exec();

        }

QSqlQueryModel* voyage::rechercher(QString num_voyage_string)
{
    QSqlQueryModel *model=new::QSqlQueryModel;
               model->setQuery("select * from  VOYAGE where NUM_VOYAGE like '%"+num_voyage_string+"%'");
               return model;

            /*   QSqlQueryModel * model= new QSqlQueryModel();
               QSqlQuery query;
               query.prepare(" select * from VOYAGE where NUM_VOYAGE like = ?");
               query.addBindValue(num_voyage_string);
               query.exec();
               model->setQuery(query);
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_voyage_string"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("depart "));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("destination"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_depart"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_retour"));  */

                   return model;

}
QSqlQueryModel* voyage::rechercher2(QString depart)
{
    QSqlQueryModel *model=new::QSqlQueryModel;
               model->setQuery("select * from  VOYAGE where DEPART like '%"+depart+"%'");
               return model;


}
QSqlQueryModel* voyage::rechercher3(QString destination)
{
    QSqlQueryModel *model=new::QSqlQueryModel;
               model->setQuery("select * from  VOYAGE where DESTINATION like '%"+destination+"%'");
               return model;

}

QSqlQueryModel * voyage::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VOYAGE ORDER BY NUM_VOYAGE ASC");
        return model;
}
QSqlQueryModel * voyage::tri2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VOYAGE ORDER BY DEPART ASC");
        return model;
}
QSqlQueryModel * voyage::tri3()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VOYAGE ORDER BY DESTINATION ASC");
        return model;
}


void voyage::genererPDFact()
{
    const QString path = QFileDialog::getSaveFileName(nullptr, "Exporter les voyages", "voyages.pdf", "PDF (*.pdf)");
    if (path.isEmpty())
        return;
    QPdfWriter pdf(path);
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::darkBlue);
        painter.setFont(QFont("euphemia", 40));
        painter.drawText(1100,1200,"Liste Des Voyages");
        painter.setPen(Qt::black);
        painter.setFont(QFont("calibri", 20));
        painter.drawRect(100,100,7300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("consolas", 9));
        painter.drawText(200,3300,"num_voyage");
        painter.drawText(1300,3300,"depart");
        painter.drawText(2400,3300,"destination");
        painter.drawText(3500,3300,"date_depart");
        painter.drawText(4600,3300,"date_retour");

        QSqlQuery query;
        query.prepare("select * from VOYAGE");
        query.exec();
        while (query.next())
        {
            painter.drawText(200,i,query.value(0).toString());
            painter.drawText(1300,i,query.value(1).toString());
            painter.drawText(2400,i,query.value(2).toString());
            painter.drawText(3500,i,query.value(3).toString());
            painter.drawText(4600,i,query.value(4).toString());



           i = i + 600;
        }
}

     /*   QSqlQueryModel *voyage::stats(){

            QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM voyage WHERE destination );");
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("destination"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("stats"));

                return model;

        }
       */

