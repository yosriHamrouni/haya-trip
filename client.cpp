#include "client.h"
#include <QFileDialog>
#include "theme.h"
#include <QSqlQuery>




#include <QtDebug>
#include <QString>
#include <QObject>
#include <QSqlDriver>
#include <QPdfWriter>
#include <QPainter>
#include <QImage>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>





Client::Client()
{



    idc=0; nom=""; prenom="";tel="";email="";
}
    Client :: Client(int idc,QString nom,QString prenom,QString tel,QString email,QString rdv  )
{
        this->idc=idc; this->nom=nom; this->prenom=prenom;this->tel=tel;this->email=email;this->rdv=rdv;


    }


    //getters
    int Client:: getid(){return  idc;};
    QString Client::getnom(){return nom;};
    QString Client::getprenom(){return prenom;};
    QString Client::get_tel(){return tel;};
    QString Client::getemail(){return email;};
     QString Client::get_rdv(){return rdv;};




    //setters
    void  Client:: setid(int id){this->idc=id;};
    void Client::setnom(QString nom){this->nom=nom;};
    void Client::setprenom(QString prenom){this->prenom=prenom;};
    void Client::set_tel(QString tel){this->tel=tel;};

    void Client::setemail(QString email){this->email=email;};

      void Client::set_rdv(QString rdv){this->rdv=rdv;};




    bool Client::ajouter()
    {



        QSqlQuery query;

        QString id_string=QString::number(idc);
            query.prepare("INSERT INTO CLIENT (ID_CLIENT,NOM_CLIENT,PRENOM_CLIENT,TEL_CLIENT,EMAIL_CLIENT,RDV_CLIENT) "
                          "VALUES (:id, :forename, :surname,:tel ,:email,:rdv )");
            query.bindValue(0, id_string);
            query.bindValue(1, nom);
            query.bindValue(2, prenom);
             query.bindValue(3, tel);
              query.bindValue(4, email);
              query.bindValue(5,rdv);

            return   query.exec();





    }


    QSqlQueryModel* Client::afficher(){


        QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM CLIENT");
        model->setHeaderData(0, Qt :: Horizontal,QObject:: tr("Idc"));
        model->setHeaderData(1, Qt :: Horizontal,QObject:: tr("Nom"));
        model->setHeaderData(2, Qt :: Horizontal,QObject:: tr("Prenom"));
       /* model->setHeaderData(3, Qt :: Horizontal,QObject:: tr("tel"));
        model->setHeaderData(4, Qt :: Horizontal,QObject:: tr("EMAIL_CLIENT"));
*/



        return  model;


    }




        bool Client::supprimer(int)
        {


            QSqlQuery query;
            query.prepare(" Delete from CLIENT where ID_CLIENT=:idc");
            query.bindValue(0, idc );


               return   query.exec();
        }





        bool Client::update()
        {

            QSqlQuery query;

            QString id_string=QString::number(idc);


                query.prepare("UPDATE CLIENT SET ID_CLIENT='"+id_string+"' , NOM_CLIENT='"+nom+"' , PRENOM_CLIENT='"+prenom+"', TEL_CLIENT='"+tel+"',EMAIL_CLIENT='"+email+"'   where ID_CLIENT='"+id_string+"' ");

                query.bindValue(0, id_string);
                query.bindValue(1, nom);
                query.bindValue(2, prenom);
                query.bindValue(3, tel);

                query.bindValue(4, email);








                return   query.exec();


        }




        QSqlQueryModel * Client::search(QString id_string)
        {

 /*   int numRows;


     QSqlDatabase defaultDB = QSqlDatabase::database();




     if (defaultDB.driver()->hasFeature(QSqlDriver::QuerySize)) {
         numRows = query.size();
     } else {
         // this can be very slow
         query.last();
         numRows = query.at() + 1;
     }

            QString id_string=QString::number(idc);


               query.prepare("SELECT NOM_CLIENT, PRENOM_CLIENT FROM CLIENT where ID_CLIENT='"+id_string+"'");
               while (query.next()) {
                     QString nom = query.value(1).toString();
                     QString  prenom  = query.value(2).toString();
                     qDebug() << nom<< prenom;
                 }




               return  query.exec();

*/




            QSqlQueryModel *model=new::QSqlQueryModel;
                           model->setQuery("select * from  CLIENT where ID_CLIENT like '%"+id_string+"%'");
                           return model;











        }



        QSqlQueryModel* Client::tri()
        {
           QSqlQueryModel * model=new QSqlQueryModel();
           model->setQuery("SELECT * FROM CLIENT ORDER BY NOM_CLIENT ASC,PRENOM_CLIENT ASC ,EMAIL_CLIENT ASC");

           model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
           model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_CLIENT"));
           model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_CLIENT"));
           model->setHeaderData(3,Qt::Horizontal,QObject::tr("TEL_CLIENT"));
           model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL_CLIENT"));

           return  model;

        }

  bool Client::genererPDFact()
        {
            const QString path = QFileDialog::getSaveFileName(nullptr, "Exporter les clients", "clients.pdf", "PDF (*.pdf)");
            if (path.isEmpty())
                return false;
            QPdfWriter pdf(path);
            QPainter painter(&pdf);
           int i = 4000;


                painter.setPen(Qt::darkBlue);
                painter.setFont(QFont("euphemia", 40));
                painter.drawText(1100,1200,"Liste Des Clients");
                painter.setPen(Qt::black);
                painter.setFont(QFont("calibri", 20));
                painter.drawRect(100,100,7300,2600);
                painter.drawRect(0,3000,9600,500);
                painter.setFont(QFont("consolas", 9));
                painter.drawText(200,3300,"ID_CLIENT");
                painter.drawText(1300,3300,"NOM_CLIENT");
                painter.drawText(2400,3300,"PRENOM_CLIENT");
                painter.drawText(3500,3300,"TEL_CLIENT");
                painter.drawText(4600,3300,"EMAIL_CLIENT");

                QSqlQuery query;
                query.prepare("select * from CLIENT");
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



                return query.exec();

       }



 QChartView * Client::stat()
  {
      //fzfezz
      int row_count = 0;
      int row_count1 = 0;

              QSqlQuery query,query2;

              query.prepare("SELECT NOM_CLIENT FROM CLIENT ");
              query.exec();

              query2.prepare("SELECT RDV_CLIENT FROM CLIENT  WHERE RDV_CLIENT IS NOT NULL ");
              query2.exec();

              while(query2.next())

                  row_count1++;



              while(query.next())
                  row_count++;

              qDebug()<<"row1="<<row_count<<row_count1;

      QPieSeries *series = new QPieSeries();
      // row_count = all clients, row_count1 = clients with an appointment.
      series->append("Avec rendez-vous", row_count1);
      series->append("Sans rendez-vous", row_count - row_count1);
      QChart *chart = new QChart();
      chart->addSeries(series);
      Theme::styleChart(chart, "Rendez-vous des clients");

      QChartView *chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);
      return chartView;
  }










