
#include "employe.h"
#include "theme.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QChartView>
#include <QPieSeries>
#include <QChart>
#include <QGridLayout>

QT_CHARTS_USE_NAMESPACE


Employe::Employe()
{
id=0 ;numero_telephone="";salaire="" ; nom="" ; prenom="" ;  date_naissance=""; image="" ;}

Employe::Employe(int id ,QString numero_telephone, QString salaire,QString nom,QString prenom, QString date_naissance, QString image)
{
    this->id=id;
    this->numero_telephone=numero_telephone;
    this->salaire=salaire;
    this->nom=nom;
    this->prenom=prenom;
    this->date_naissance=date_naissance;
    this->image=image;


}
int Employe::getid()
{   return id;  }
QString Employe::getnumero_telephone()
{   return numero_telephone;  }
QString Employe::getsalaire()
{   return salaire; }
QString Employe::getnom()
{   return nom; }
QString Employe::getprenom()
{   return prenom;  }
QString Employe::getdate_naissance()
{   return date_naissance;  }
QString Employe::getimage()
{   return image;  }
void Employe::setid(int id){ this->id=id; }
void Employe::setnumero_telephone(QString numero_telephone){this->numero_telephone=numero_telephone; }
void Employe::setsalaire(QString  salaire){this->salaire=salaire; }
void Employe::setnom(QString nom){this->nom=nom; }
void Employe::setprenom(QString prenom){this->prenom=prenom; }
void Employe::setdate_naissance(QString date_naissance){this->date_naissance=date_naissance; }
void Employe::setimage(QString image){this->image=image; }

bool Employe::ajouter()
{
   QString res=QString::number(id);

   QSqlQuery query;

          query.prepare("INSERT INTO EMPLOYES (ID,NUMERO_TELEPHONE,SALAIRE ,NOM,PRENOM,DATE_NAISSANCE,IMAGE) "
                        "VALUES (:id,:numero_telephone, :saliare,:nom, :prenom,:date_naissance, :image )");
          query.bindValue(0, res);
          query.bindValue(1, numero_telephone);
          query.bindValue(2, salaire);
          query.bindValue(3, nom);
          query.bindValue(4, prenom);
          query.bindValue(5 ,date_naissance );
          query.bindValue(6 ,image );
           return query.exec();

}
QSqlQueryModel* Employe ::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM EMPLOYES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero_telephone"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("salaire"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("image"));
          return  model;
}
bool Employe::supprimer(int id)
{

    QSqlQuery query;

           query.prepare("Delete from EMPLOYES where id=:id");
           query.bindValue(0, id);

            return query.exec();

}
bool Employe::update()
        {

            QSqlQuery query;

            QString id_string=QString::number(id);


                query.prepare("UPDATE EMPLOYES SET ID='"+id_string+"' , NUMERO_TELEPHONE='"+numero_telephone+"' , SALAIRE='"+salaire+"' , NOM='"+nom+"' , PRENOM='"+prenom+"' , DATE_NAISSANCE='"+date_naissance+"' ,IMAGE='"+image+"'  WHERE ID='"+id_string+"' ");

                query.bindValue(0, id);
                query.bindValue(1, numero_telephone);
                query.bindValue(2, salaire);
                query.bindValue(3, nom);
                query.bindValue(4, prenom);
                query.bindValue(5 ,date_naissance );
                query.bindValue(6 ,image);


                return  query.exec();


        }

QSqlQueryModel* Employe::tri()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM EMPLOYES ORDER BY ID ASC ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("numero_telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("image"));

   return  model;

}
QSqlQueryModel* Employe::tri_alpha()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM EMPLOYES ORDER BY NOM ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("numero_telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("image"));

   return  model;

}
/*QSqlQueryModel* Employe::tri_salaire()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM EMPLOYES ORDER BY SALAIRE ASC ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("numero_telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("image"));

   return  model;

}*/


QSqlQueryModel* Employe ::Rechercher(QString id_string)
{
    QSqlQueryModel *model=new::QSqlQueryModel;
                   model->setQuery("SELECT * FROM  EMPLOYES where ID like '%"+id_string+"%'");
                   return model;

    }


void Employe::genererPDFact()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
            { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;
        q.prepare("SELECT * FROM EMPLOYES ");
        q.exec();
        QString pdf="<br> <h1  style='color:blue'>LISTE DES EMPLOYES  <br></h1>\n <br> <table>  <tr>  <th>ID </th> <th>NUMERO-TELEPHONE </th> <th>PRENOM  </th> <th>SALAIRE  </th><th>NOM  </th><th>PRENOM </th><th>DATE_NAISSANCE  </th> </tr>" ;
    //br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

        while ( q.next())
            {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);


    }
QChartView * Employe ::stat()
        {
          /*int row_count = 0;
          int row_count1 = 0;


                  QSqlQuery query,query2;



                  query2.prepare("SELECT SALAIRE FROM EMPLOYES  WHERE SALAIRE<1500 ");
                  query2.exec();

                  while(query2.next())

                      row_count1++;

                  query.prepare("SELECT SALAIRE FROM EMPLOYES WHERE SALAIRE>=1500 ");
                  query.exec();

                  while(query.next())
                      row_count++;



                  qDebug()<<"row1="<<row_count<<row_count1;

          QPieSeries *series = new QPieSeries();
          series->append("SALAIRE INFERIEUR à 1500", row_count1);
          series->append("SALAIRE SUPERIEUR à 1500", row_count);

          QPieSlice *slice= series->slices().at(0);
                 slice->setExploded(true);
                 slice->setLabelVisible(true);
                 slice->setPen((QPen(Qt::white)));

          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("SALAIRE DES EMPLOYES ");
          chart->legend()->setAlignment(Qt::AlignRight);
          chart->legend()->setBackgroundVisible(true);
          chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
          chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
          return chartView;*/
    int row_count = 0;
            int row_count1 = 0;

                    QSqlQuery query,query1;

                    query.prepare("SELECT * FROM employes where SALAIRE>=2000");
                    query.exec();
                    while(query.next())
                        row_count++;

                    query1.prepare("SELECT * FROM employes where SALAIRE<2000");
                    query1.exec();
                    while(query1.next())
                        row_count1++;

                   // qDebug()<<"row1="<<row_count<<row_count1;

            QPieSeries *series = new QPieSeries();
            series->append("2000 DT et plus", row_count);
            series->append("Moins de 2000 DT", row_count1);

            QChart *chart = new QChart();
            chart->addSeries(series);
            Theme::styleChart(chart, "Répartition des salaires");

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            return chartView;

        }




