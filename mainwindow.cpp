#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "theme.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>
#include <excel.h>
#include<QRegularExpression>
#include <arduino.h>

#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include "connection.h"
#include "QDebug"
#include <QRegExpValidator>
#include "mainwindow.h"


#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QVBoxLayout>

#include <QMenu>
#include <QAction>
#include <QFileDialog>







//INCLUDES SARRA



#include "voyage.h"
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include "qcustomplot.h"
#include <vector>
#include "connection.h"
#include <QFont>
#include "qrcode.h"
#include "qrwidget.h"
#include "QWidget"
#include <QFile>
#include <QPainter>
#include <string>
#include <QtSvg>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>



//INCLUDES AHMED



#include "dialog_statistiques.h"
#include "dialog_mailing.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include<QUrl>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets>
#include <QFileDialog>









MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 99999, this));


   ui->tab_employe->setModel(E.afficher());

   ui->horizontalLayout->addWidget(E.stat());



   /*********************************************************/

   //**************************************************arduino*********************

   int ret=A.connect_arduino();

       switch (ret) {
       case 0 :
           qDebug()<<"Arduino is available and connected to : "<<A.getarduino_port_name();
           break;

       case 1 :
           qDebug()<<"Arduino is available but not connected to : "<<A.getarduino_port_name();
           break;
       case -1 :
           qDebug()<<"Arduino is not available ";
           break;
       }

 //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(concatRfid()));
 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
 //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label2()));













   /*
   ui->setupUi(this);
   int ret=A.connect_arduino(); // lancer la connexion à arduino
   switch(ret){
   case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
   break;
   case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
   break;
   case(-1):qDebug() << "arduino is not available";

   QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); */



 //CLIENTS





 ui->le_idc->setValidator(new QIntValidator(0, 9999999, this));

/* QRegExp rxEmail(EMAIL_RX);
 QRegExpValidator *valiEmail = new QRegExpValidator(rxEmail, this);

*/
ui->le_email->setValidator(new QRegExpValidator(  QRegExp("[a-z]{1,19}@[a-z]{1,9}\\.[a-z]{1,4}")  ));

 ui->tab_clients->setModel(C.afficher());
   ui->verticalLayout->addWidget(C.stat());

   //CAMERA


   mCamera= new QCamera(this);
  mCameraViewfinder= new QCameraViewfinder(this);
  mCameraImageCapture = new QCameraImageCapture(mCamera, this);
  mLayout= new QVBoxLayout;

  mOptionsMenu = new QMenu("options", this);



  mEncenderAction = new QAction("Switchon",this);
  mApagarAction = new QAction("apagar",this);
  mCapturarAction= new QAction("Capture",this);

  mOptionsMenu->addActions({mEncenderAction,mApagarAction, mCapturarAction});
  ui->Options__pushButton->setMenu(mOptionsMenu);
  mCamera->setViewfinder(mCameraViewfinder);
  mLayout->addWidget(mCameraViewfinder);

  mLayout->setMargin(0);


  ui->scrollArea->setLayout(mLayout);

  connect(mEncenderAction,&QAction::triggered ,[&](){
      mCamera->start();
  });



  connect(mApagarAction,&QAction::triggered ,[&](){
      mCamera->stop();

  });



  connect(mCapturarAction, &QAction::triggered , [&](){


       auto filename=  QFileDialog::getSaveFileName(this,"Capture", "/","Images(*.jpg;*.jpeg)" );

       if(filename.isEmpty()){
           return ;

       };



         mCameraImageCapture->setCaptureDestination(
                     QCameraImageCapture::CaptureToFile );


         QImageEncoderSettings imageEncoderSettings;
         imageEncoderSettings.setCodec("image/jpeg");
         imageEncoderSettings.setResolution(1600,1200);
         mCameraImageCapture->setEncodingSettings(imageEncoderSettings);

         mCamera->setCaptureMode(QCamera :: CaptureStillImage);
         mCamera->start();
         mCamera->searchAndLock();
         mCameraImageCapture->capture(filename);
         mCamera->unlock();







  });


//VOYAGES



  ui->le_num_voyag->setValidator( new QIntValidator(0, 9999999, this));
  ui->tab_voyageur_2->setModel(V.afficher());
  int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
 total ( a,   b,  c,  d,  e,  f,   g,   h);






//Reservations


 ui->lineEdit_ID->setValidator( new QIntValidator(0, 99999999, this));
 ui->lineEdit_Mont->setValidator( new QIntValidator(0, 99999999, this));
 ui->comboBox_ID->setModel(R.afficher_id());
 R.write(R.time(),"App started");
 ui->tab_res->setModel (R.afficher());


















 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();
    QString numero_telephone=ui->le_numero_telephone->text();
    QString salaire=ui->le_salaire->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString date_naissance=ui->le_date_naissance->text();
    QString image=ui->path->text();

    Employe E(id, numero_telephone,salaire,  nom, prenom, date_naissance,image);
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("Ajout avec succes.");
        ui->tab_employe->setModel(E.afficher());

    }
    else
        msgBox.setText("Echec de l'ajout.");
    msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{
   Employe E1;
   E1.setid(ui->le_id_supp->text().toInt());
   bool test=E1.supprimer(E1.getid());
   QMessageBox msgBox;
   if(test)
   {msgBox.setText("Suppression avec succes.");
   ui->tab_employe->setModel(E.afficher());




   }
   else
       msgBox.setText("Echec de suppression.");

   msgBox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    int id=ui->edit_id->text().toInt();
    QString numero_telephone=ui->edit_numero->text();
    QString salaire=ui->edit_salaire->text();
    QString nom=ui->edit_nom->text();
    QString prenom=ui->edit_prenom->text();
    QString date_naissance=ui->edit_date->text();
    QString image=ui->path->text();

          Employe E(id, numero_telephone,salaire, nom, prenom, date_naissance, image);


         bool test=E.update();
          if (test){
              QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("modification effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


      }
          else
            {  QMessageBox::critical(nullptr, QObject::tr("not OK"),
                          QObject::tr("modif non effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);}
     ui->tab_employe->setModel(E.afficher());

}

void MainWindow::on_bin_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Image(*.png *.jpg *.jpeg *.bmp *.gif)")) ;
    if(QString::compare(filename, QString())!=0)
    {
       QImage image;
       bool valid = image.load(filename);
       if(valid)
       {
           image=image.scaledToWidth(ui->lbl_image_2->width(), Qt::SmoothTransformation);
          ui->lbl_image_2->setPixmap(QPixmap::fromImage(image));


          ui->path->setText(filename);
       }

    }


    }



void MainWindow::on_tri_clicked()
{
    Employe E;

    ui->tab_employe->setModel(E.tri());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_recherher_clicked()
{

     QString search=ui->id_chercher->text();
            ui->tab_employe->setModel(E.Rechercher(search));


}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    int id=ui->tab_employe->model()->data(index).toInt();
     QImage image;

        QString id_string = QString::number(id) ;


       /*if (!test.createconnect()){

            qDebug()<<"Failed to open dtabase";

            return;
               }*/


            QSqlQuery qry;
            qry.prepare("SELECT* FROM EMPLOYES WHERE ID='"+id_string+"' or NOM='"+id_string+"' or NUMERO_TELEPHONE='"+id_string+"' or SALAIRE='"+id_string+"' or NOM='"+id_string+"'  or PRENOM='"+id_string+"' or DATE_NAISSANCE='"+id_string+"' or IMAGE='"+id_string+"'  ") ;
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->edit_id->setText(qry.value(0).toString()) ;
                    ui->edit_numero->setText(qry.value(1).toString()) ;
                    ui->edit_salaire->setText(qry.value(2).toString()) ;
                    ui->edit_nom->setText(qry.value(3).toString()) ;
                    ui->edit_prenom->setText(qry.value(4).toString()) ;
                    ui->edit_date->setText(qry.value(5).toString()) ;

                    image.load(qry.value(6).toString());
                    image=image.scaledToWidth(ui->aff_image->width(), Qt::SmoothTransformation);
                    ui->aff_image->setPixmap(QPixmap::fromImage(image));

                    image=image.scaledToWidth(ui->edit_image->width(), Qt::SmoothTransformation);
                    ui->edit_image->setPixmap(QPixmap::fromImage(image));
                }
            }


}

void MainWindow::on_le_modd_clicked()
{



    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Image(*.png *.jpg *.jpeg *.bmp *.gif)")) ;
    if(QString::compare(filename, QString())!=0)
    {


        QImage image;
        bool valid = image.load(filename);



       if(valid)
       {
           image=image.scaledToWidth(ui->edit_image->width(), Qt::SmoothTransformation);
          ui->edit_image->setPixmap(QPixmap::fromImage(image));


          ui->path->setText(filename);
       }

    }

    }


void MainWindow::on_pdf_clicked()
{

    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->tab_employe->model()->rowCount();
                      const int columnCount = ui->tab_employe->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES EMPLOYES **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tab_employe->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->tab_employe->isColumnHidden(column)) {
                                  QString data =ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);
}






void MainWindow::on_le_fich_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                            tr("Excel Files (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tab_employe);

            //colums to export

            obj.addField(0, "id", "char(20)");
            obj.addField(1, "numero_telephone", "char(20)");
            obj.addField(2, "salaire", "char(20)");
            obj.addField(3, "nom", "char(20)");
            obj.addField(4, "prenom", "char(20)");
            obj.addField(5, "date_naissance", "char(20)");


            int retVal = obj.export2Excel();
            if( retVal > 0)
            {
                QMessageBox::information(this, tr("Done"),
                                         QString(tr("%1 records exported!")).arg(retVal)
                                         );
            }
}

void MainWindow::on_tri_alpha_clicked()
{
    Employe E;

    ui->tab_employe->setModel(E.tri_alpha());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




//CLIENTS////



void MainWindow::on_pb_ajouter_client_clicked()
{
        //int idc=ui->le_idc
              int idc=ui->le_idc->text().toInt();

                QString nom=ui->le_nom->text();
                QString prenom=ui->le_prenom->text();
                QString tel=ui->le_tel->text();
                QString email=ui->le_email->text();
                QString  rdv=ui->le_rdv->text();





                Client C(idc,nom,prenom,tel,email,rdv);




                bool test=C.ajouter();
                if (test){
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("ajout effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_clients->setModel(C.afficher());

            }
                else
                    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                QObject::tr("ajout non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pb_supprimer_client_clicked()
{



    Client C;
    C.setid(ui->le_id_supp->text().toInt());

   bool test=C.supprimer(C.getid());

   QMessageBox msgBox;
   if(test)
   {msgBox.setText("Suppression avec succes.");
   ui->tab_clients->setModel(C.afficher());}
   else
   msgBox.setText("Echec de suppression");
   msgBox.exec();

}

/*void MainWindow::on_comboBox_supp_activated(const QString &idc)
{
  //  ui->comboBox_supp->addItems()
}*/

void MainWindow::on_pb_update_clicked()
{

    int idc=ui->le__edit_idc->text().toInt();

      QString nom=ui->le_edit_name->text();
      QString prenom=ui->le_edit_prenom->text();
      QString tel=ui->le_edit_tel->text();
      QString email=ui->le_edit_email->text();


     QString rdv=ui->le_edit_rdv->text();


      Client C(idc,nom,prenom,tel,email,rdv);




      bool test=C.update();
      if (test){
          QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("modification effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_clients->setModel(C.afficher());

             }
      else
          QMessageBox::critical(nullptr, QObject::tr("not OK"),
                      QObject::tr("modif non effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_tab_clients_activated(const QModelIndex &index)

{




int idc=ui->tab_clients->model()->data(index).toInt();

    QString id_string = QString::number(idc) ;





   /* if (!test.createconnect()){

        qDebug()<<"Failed to open dtabase";

        return;
           }*/


        QSqlQuery qry ;
        qry.prepare("SELECT* FROM CLIENT WHERE ID_CLIENT='"+id_string+"' or NOM_CLIENT='"+id_string+"' or PRENOM_CLIENT='"+id_string+"' or TEL_CLIENT='"+id_string+"' or EMAIL_CLIENT='"+id_string+"'   " ) ;
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->le_id_supp->setText(qry.value(0).toString()) ;
                ui->le__edit_idc->setText(qry.value(0).toString()) ;
                ui->le_edit_name->setText(qry.value(1).toString()) ;
                ui->le_edit_prenom->setText(qry.value(2).toString()) ;
                ui->le_edit_tel->setText(qry.value(3).toString()) ;
                   ui->le_edit_email->setText(qry.value(4).toString()) ;

            }
        }




}

void MainWindow::on_pb_find_clicked()
{

    QString search=ui->le_id_supp->text();
    ui->tab_clients->setModel(C.search(search));


/*
    Client C;
    C.setid(ui->le_id_supp->text().toInt());




    bool test=C.search();
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("client trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_clients->setModel(C.afficher());

           }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("client non trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/
}

void MainWindow::on_pb_tri_client_clicked()
{
    Client C;

     ui->tab_clients->setModel(C.tri());
     bool test=C.tri();
     if(test){
         QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("tri effectué. \n"
                                              "click Cancel to exist."),QMessageBox::Cancel);

     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                     QObject::tr("tri non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
}

void MainWindow::on_pb_genererPdf_clicked()
{
        Client C;
  bool test= C.genererPDFact();
   if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("PDF Géneré. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



//VOYAGES




void MainWindow::on_quitter_button_clicked()
{
    this->close();

}

void MainWindow::on_le_ajouter_clicked()
{
    int num_voyage=ui->le_num_voyag->text().toInt();
    QString depart=ui->le_depart->text();
    QString destination=ui->le_destination->text();
    QString date_depart=ui->date_depart->text();
    QString date_retour=ui->date_retour->text();

    voyage V(num_voyage,depart,destination,date_depart,date_retour);

     bool test=V.ajouter();
     if (test){
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_voyageur_2->setModel(V.afficher());
         ui->tab_voyageur_2->setModel(V.rechercher(""));
         ui->tab_voyageur_2->setModel(V.rechercher2(""));
         ui->tab_voyageur_2->setModel(V.rechercher3(""));



 }
     else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                     QObject::tr("ajout non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


 }


void MainWindow::on_boutton_supp_clicked()
{
    voyage VS;
    VS.setnum_voyage(ui->le_voyage_supp_2->text().toInt());
    bool test=VS.supprimer(VS.getnum_voyage());
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->tab_voyageur_2->setModel(V.afficher());
ui->tab_voyageur_2->setModel(V.rechercher(""));
ui->tab_voyageur_2->setModel(V.rechercher2(""));
ui->tab_voyageur_2->setModel(V.rechercher3(""));



}
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

    /* int num_voyage = ui->comboBox->currentText().toInt();
        bool test=tmpclient.supprimer(num_voyage);
        if(test)
        {ui->tab_voyageur_2->setModel(tmpclient.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                        QObject::tr("client supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            QSqlQueryModel * model= new QSqlQueryModel;
            model->setQuery("SELECT MATRICULE_FISCALE FROM client");
            ui->comboBox_3->setModel(model);
            ui->comboBox_2->setModel(model);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

       */


void MainWindow::on_le_update_clicked()
{
    int num_voyage=ui->le_num_voyag->text().toInt();
    QString depart=ui->le_depart->text();
    QString destination=ui->le_destination->text();
    QString date_depart=ui->date_depart->text();
    QString date_retour=ui->date_retour->text();

    voyage V(num_voyage,depart,destination,date_depart,date_retour);

     bool test=V.update();
     if (test){
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("update effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_voyageur_2->setModel(V.afficher());
         ui->tab_voyageur_2->setModel(V.rechercher(""));


 }
     else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                     QObject::tr("update non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_recherche_button_clicked()
{
    QString search=ui->le_search_numv->text();
        ui->tab_voyageur_2->setModel(V.rechercher(search));
       }

void MainWindow::on_recherche_button_2_clicked()
{
    QString search2=ui->le_search_depart->text();
        ui->tab_voyageur_2->setModel(V.rechercher2(search2));

}

void MainWindow::on_recherche_button_3_clicked()
{
    QString search3=ui->le_search_destination->text();
        ui->tab_voyageur_2->setModel(V.rechercher3(search3));
}



void MainWindow::on_tri_button_clicked()
{

       ui->tab_voyageur_2->setModel(V.tri());
}

void MainWindow::on_tri_button_2_clicked()
{
     ui->tab_voyageur_2->setModel(V.tri2());
}


void MainWindow::on_tri_button_3_clicked()
{
     ui->tab_voyageur_2->setModel(V.tri3());
}



void MainWindow::on_pdf_button_clicked()
{
       V.genererPDFact();
       bool test=V.update();
       if (test){
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("pdf is ready now.\n"
                                   " Click Cancel to exit."), QMessageBox::Cancel);
           ui->tab_voyageur_2->setModel(V.afficher());
           ui->tab_voyageur_2->setModel(V.rechercher(""));


   }
       else
           QMessageBox::critical(nullptr, QObject::tr("not OK"),
                       QObject::tr("pdf has failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);



}



void MainWindow::on_tab_voyageur_2_activated(const QModelIndex &index)
{
    int num_voyage=ui->tab_voyageur_2->model()->data(index).toInt();

        QString num_voyage_string = QString::number(num_voyage) ;

            QSqlQuery qry ;
            qry.prepare("SELECT* FROM VOYAGE WHERE num_voyage='"+num_voyage_string+"' or num_voyage='"+num_voyage_string+"' or depart='"+num_voyage_string+"' or destination='"+num_voyage_string+"' or date_depart='"+num_voyage_string+"'or date_retour='"+num_voyage_string+"'  " ) ;
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->le_num_voyag->setText(qry.value(0).toString()) ;
                    ui->le_depart->setText(qry.value(1).toString()) ;
                    ui->le_destination->setText(qry.value(2).toString()) ;
                    ui->date_depart->setText(qry.value(3).toString()) ;
                    ui->date_retour->setText(qry.value(4).toString()) ;
                    ui->le_voyage_supp_2->setText(qry.value(0).toString()) ;

                }
            }
}

/*

void MainWindow::on_stat_button_clicked()
{
             QTableView table_necessiteux,table_n2;
                 QSqlQueryModel * Mod=new  QSqlQueryModel();
                 QSqlQueryModel * Mod2=new  QSqlQueryModel();
                      Connection c;
                      QSqlQuery qry,q2;
                      qry.prepare("select DESTINATION from VOYAGE");
                      qry.exec();
                      Mod->setQuery(qry);
                      table_necessiteux.setModel(Mod);

                      q2.prepare("select NUM_VOYAGE from VOYAGE group by DESTINATION");
                      q2.exec();
                      Mod2->setQuery(q2);
                      table_n2.setModel(Mod2);

                      //c.closeConnection();

                     qDebug()<<table_necessiteux.model()->data(table_necessiteux.model()->index(0, 0)).toString().simplified();
                     qDebug()<<table_n2.model()->data(table_n2.model()->index(0, 0)).toInt();

                     const int rowCount = table_necessiteux.model()->rowCount();
                     const int rowCount2 = table_n2.model()->rowCount();



                    // set dark background gradient:
                     QLinearGradient gradient(0, 0, 0, 400);
                     gradient.setColorAt(0, QColor(192, 192, 192));
                     gradient.setColorAt(0.38, QColor(192, 192, 192));
                     gradient.setColorAt(1, QColor(70, 70, 70));
                     ui->customplot->setBackground(QBrush(gradient));

                     // create empty bar chart objects:
                     QCPBars *besoin = new QCPBars(ui->customplot->xAxis, ui->customplot->yAxis);

                     besoin->setAntialiased(false); // gives more crisp, pixel aligned bar borders

                     besoin->setStackingGap(1);

                     // set names and colors:

                     besoin->setName("Destinations");
                     besoin->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                 besoin->setBrush(QColor(18, 116, 161));
                     // stack bars on top of each other:


                     // prepare x axis with needs' labels:
                     QVector<double> ticks;
                     QVector<QString> labels;

                     for(int i=0; i<rowCount; ++i){
                         ticks.push_back(i);
                         labels.push_back(table_necessiteux.model()->data(table_necessiteux.model()->index(i, 0)).toString().simplified());
                         qDebug()<<ticks[i];
                         qDebug()<<labels[i];
                     }
                     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                     textTicker->addTicks(ticks, labels);
                     ui->customplot->xAxis->setTicker(textTicker);
                     ui->customplot->xAxis->setTickLabelRotation(60);
                     ui->customplot->xAxis->setSubTicks(false);
                     ui->customplot->xAxis->setTickLength(0, 4);
                     ui->customplot->xAxis->setRange(0, 8);
                     ui->customplot->xAxis->setBasePen(QPen(Qt::black));
                     ui->customplot->xAxis->setTickPen(QPen(Qt::black));
                     ui->customplot->xAxis->grid()->setVisible(true);
                     ui->customplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                     ui->customplot->xAxis->setTickLabelColor(Qt::black);
                     ui->customplot->xAxis->setLabelColor(Qt::black);

                     // prepare y axis:
                     ui->customplot->yAxis->setRange(0,50);
                 ui->customplot->yAxis->setPadding(5); // a bit more space to the left border
                 ui->customplot->yAxis->setBasePen(QPen(Qt::white));
                 ui->customplot->yAxis->setTickPen(QPen(Qt::white));
                 ui->customplot->yAxis->setSubTickPen(QPen(Qt::white));
                 ui->customplot->yAxis->grid()->setSubGridVisible(true);
                 ui->customplot->yAxis->setTickLabelColor(Qt::white);
                 ui->customplot->yAxis->setLabelColor(Qt::white);
                 ui->customplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                 ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                     // Add data:
                     QVector<double>besoinData;

                     for(int i=0; i<rowCount2; ++i){
                         besoinData.push_back(table_n2.model()->data(table_n2.model()->index(i, 0)).toInt());
                         qDebug()<<besoinData;

                     }
                    besoin->setData(ticks, besoinData);

                     // setup legend:
                     ui->customplot->legend->setVisible(true);
                 ui->customplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                 ui->customplot->legend->setBrush(QColor(255, 255, 255, 100));
                 ui->customplot->legend->setBorderPen(Qt::NoPen);
                 QFont legendFont = font();
                 legendFont.setPointSize(10);
                 ui->customplot->legend->setFont(legendFont);
                 ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
                 ui->customplot->replot();
    }

*/


  void MainWindow::on_qr_button_clicked()
    {
if(ui->tab_voyageur_2->currentIndex().row()==-1)
                    QMessageBox::information(nullptr, QObject::tr("suppression"),
                                             QObject::tr("Veuillez Choisir un num_voyage du tab.\n"
                                                         "Click Ok to exit."), QMessageBox::Ok);
                else
                {
                     int  Code=ui->tab_voyageur_2->model()->data(ui->tab_voyageur_2->model()->index(ui->tab_voyageur_2->currentIndex().row(),0)).toInt();
                     const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(std::to_string(Code).c_str(), qrcodegen::QrCode::Ecc::LOW);
                     std::ofstream myfile;
                     myfile.open ("qrcode.svg") ;
                     myfile << qr.toSvgString(1);
                     myfile.flush();
                     myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                     QPixmap pix(QSize(100, 100));
                     pix.fill(Qt::white);
                     {
                         QPainter pixPainter(&pix);
                         svgRenderer.render(&pixPainter);
                     }
                     ui->qr_label->setPixmap(pix);
                }
}
/* void MainWindow::on_actionplay_video_triggered()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}
void MainWindow::on_actionstop_video_triggered()
{
    player->stop();
    vw->close();
}
*/

void MainWindow::on_traduire_clicked()
{
    QString test ;
        test = ui->label_11->text();
        if(test=="Num_voyage")
        {
            ui->label_11->setText("Num_travel");
            ui->label_2->setText("Depart");
            ui->label_5->setText("Destination");
            ui->label->setText("Date_depart");
            ui->label_3->setText("Date_return");
            ui->label_12->setText("Look for");
            ui->label_13->setText("Erase");
            ui->label_15->setText("scan Qrcode");

            ui->tri_button->setText("sort by num_travel");
            ui->tri_button_2->setText("sort by depart");
            ui->tri_button_3->setText("sort by destination");

            ui->le_search_numv->setPlaceholderText("num_travel");
            ui->le_search_depart->setPlaceholderText("depart");
            ui->le_search_destination->setPlaceholderText("destination");
            ui->le_voyage_supp_2->setPlaceholderText("num travel to erase");

            ui->traduire->setText("translate in french");
            ui->le_ajouter->setText("Add");


        }

        else
        {
            ui->label_11->setText("Num_voyage");
            ui->label_2->setText("Depart");
            ui->label_5->setText("Destination");
            ui->label->setText("Date_depart");
            ui->label_3->setText("Date_retour");
            ui->label_12->setText("chercher");
            ui->label_13->setText("supprimer");
            ui->label_15->setText("scanner Qrcode");

            ui->tri_button->setText("tri par num_voyage");
            ui->tri_button_2->setText("tri par depart");
            ui->tri_button_3->setText("tri par destination");

            ui->le_search_numv->setPlaceholderText("num_voyage");
            ui->le_search_depart->setPlaceholderText("depart");
            ui->le_search_destination->setPlaceholderText("destination");
            ui->le_voyage_supp_2->setPlaceholderText("num voyage a supprimé");

            ui->traduire->setText("traduire en anglais");
            ui->le_ajouter->setText("Ajouter");

        }
}



void MainWindow::total (int a,  int b, int c, int d, int e, int f, int  g,  int h )
{
    QBarSet *set0 = new QBarSet ("Voyages par destination");


    //**
    QSqlQuery qry;
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","france");
    qry.exec();
    while(qry.next())
        a++;
    //**
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","egypt");
    qry.exec();
    while(qry.next())
        b++;
    //**
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","frankfurt");
    qry.exec();
    while(qry.next())
        c++;
    //**
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","tunisia");
    qry.exec();
    while(qry.next())
        d++;
    //**
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","italy");
    qry.exec();
    while(qry.next())
        e++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","belgique");
    qry.exec();
    while(qry.next())
        f++;
    //**
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","usa");
    qry.exec();
    while(qry.next())
        g++;
    //**
    qry.prepare("SELECT * FROM VOYAGE where DESTINATION=:DESTINATION");
       qry.bindValue(":DESTINATION","australia");
    qry.exec();
    while(qry.next())
        h++;

    *set0 << a << b << c << d << e << f << g << h;


    QBarSeries *series = new QBarSeries();
    series->append(set0);


    QChart *chart = new QChart();
    chart->addSeries(series);
    QStringList categories;
    categories << "france" << "egypt" << "frankfurt" << "tunisia" << "italy" << "belgique"  << "usa"  << "australie";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->setAxisX(axis, series);
    QValueAxis *countAxis = new QValueAxis();
    countAxis->setLabelFormat("%d");
    // Whole-number ticks: one per trip up to 5, otherwise let Qt pick round values.
    const int maxTrips = qMax(1, qMax(qMax(qMax(a, b), qMax(c, d)), qMax(qMax(e, f), qMax(g, h))));
    countAxis->setRange(0, maxTrips);
    if (maxTrips <= 5) countAxis->setTickCount(maxTrips + 1);
    else countAxis->applyNiceNumbers();
    chart->setAxisY(countAxis, series);
    Theme::styleChart(chart, "Destinations les plus visitées");
    QChartView *chartview = new QChartView (chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->graphe);
    chartview->resize(ui->graphe->size());
    // The chart sits inside a leftover QCustomPlot that is never filled: drop its empty axes.
    ui->customplot->plotLayout()->clear();
    ui->customplot->setBackground(QBrush(Theme::Surface));
    ui->customplot->replot();


}

/*void MainWindow::on_ref_clicked()
{


            A.write_to_arduino(("0"));

}

void MainWindow::on_acc_clicked()
{

            A.write_to_arduino(("1"));

}

void MainWindow::on_verif_clicked()
{

int nbr= ui->nbr_perso->text().toInt();

   if(nbr>20)
    {
         A.write_to_arduino(("1"));
    }
   else if(nbr>=20)
    {
         A.write_to_arduino(("0"));
     }

}
*/

void MainWindow::update_nb()
{

  data=A.read_from_arduino();

  if(data== "1"){
      ui->etat_buzzer->setText("person detected");
  }
  else if(data== "0"){
      ui->etat_buzzer->setText("person not detected");
      }
  qDebug()<<"data"<<data;
}
  /* if(data == "0000"){
      test=1;
  }
  if(data == "1111" && test == 1){
      test=0;
      pas++;
      if(pas==2){
          nb++;
          pas=0;
      }

  }

qDebug()<<"test"<<nb;
qDebug()<<"data"<<data;*/



//*******************ReSERVATIONS**************************//







void MainWindow::on_pB_Ajouter_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    int MONTANT=ui->lineEdit_Mont->text().toInt();
    reservation R(ID,NOM,PRENOM,MONTANT);
    bool test=R.ajouterS();
    if(test)
    {
        ui->label_Info->setText("Ajout effectué");
        ui->comboBox_ID->setModel(R.afficher_id());
        ui->tab_res->setModel(R.afficher());
        R.write(R.time(),"RESERVATION: Ajout effectué");
        ui->textBrowser_res->setText(R.read());
    }
    else
    {
        ui->label_Info->setText("Ajout non effectué");
    }
}

void MainWindow::on_pB_Supprimer_clicked()
{
    reservation R;
    R.setid(ui->comboBox_ID->currentText().toInt());
    bool test=R.supprimerS(R.getid());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tab_res->setModel(R.afficher());
        ui->comboBox_ID->setModel(R.afficher_id());
        R.write(R.time(),"RESERVATION: Suppression effectué");
        ui->textBrowser_res->setText(R.read());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void MainWindow::on_pB_Modifier_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    int MONTANT=ui->lineEdit_Mont->text().toInt();
    reservation R(ID,NOM,PRENOM,MONTANT);
    bool test=R.modifierS();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_res->setModel(R.afficher());
        ui->comboBox_ID->setModel(R.afficher_id());
        R.write(R.time(),"RESERVATION: Modification effectué");
        ui->textBrowser_res->setText(R.read());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void MainWindow::on_pB_TirerParID_clicked()
{
    ui->label_Info->setText("Tri par ID effectué");
    ui->tab_res->setModel(R.tri_id());
}

void MainWindow::on_pB_TirerParType_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_res->setModel(R.tri_nom());
}

void MainWindow::on_comboBox_ID_currentIndexChanged(int)
{
    int id=ui->comboBox_ID->currentText().toInt();
        QString id_1=QString::number(id);
        QSqlQuery query;
        query.prepare("SELECT * FROM RESERVATION where ID='"+id_1+"'");
        if(query.exec())
        {
            while (query.next())
            {
                ui->lineEdit_ID->setText(query.value(0).toString()) ;
                ui->lineEdit_Nom->setText(query.value(1).toString()) ;
                ui->lineEdit_Prenom->setText(query.value(2).toString()) ;
                ui->lineEdit_Mont->setText(query.value(3).toString()) ;
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                                  QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void MainWindow::on_pB_Recherche_clicked()
{
    reservation R;
    QString text;

    if (ui->rB_ID->isChecked()==true)
    {
        R.clearTable(ui->tab_res);
            int ID=ui->lineEdit_IDRecherche->text().toInt();
            R.chercheID(ui->tab_res,ID);
    }
    if (ui->rB_Nom->isChecked()==true)
    {
        R.clearTable(ui->tab_res);
            QString Nom=ui->lineEdit_IDRecherche->text();
            R.chercheNom(ui->tab_res,Nom);
    }
    if (ui->rB_Mont->isChecked()==true)
    {
        R.clearTable(ui->tab_res);
            int MONTANT=ui->lineEdit_IDRecherche->text().toInt();
            R.chercheMont(ui->tab_res,MONTANT);
    }
}

void MainWindow::on_pB_ExPDF_clicked()
{
    const QString pdfPath = QFileDialog::getSaveFileName(this, "Exporter les réservations", "ListeReservation.pdf", "PDF (*.pdf)");
    if (pdfPath.isEmpty())
        return;
    QPdfWriter pdf(pdfPath);
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    //painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("D:/images/logo.png"));
    painter.drawText(3000,1500,"LISTE DES RESERVATIONS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    //painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2300,3300,"NOM");
    painter.drawText(4300,3300,"PRENOM");
    painter.drawText(6300,3300,"MONTANT");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from RESERVATION");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        painter.drawText(10000,i,query.value(5).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(pdfPath));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_pushButton_SupprimerS_clicked()
{
    R.clearh();
    ui->textBrowser_res->setText(R.read());
}

void MainWindow::on_pushButton_Fermer_clicked()
{
    close();
}

void MainWindow::on_pB_Mailing_clicked()
{
    Dialog_Mailing mailing;
    mailing.setModal(true);
    mailing.exec();
}

void MainWindow::on_pB_Stats_clicked()
{
    Dialog_Statistiques stats;
    stats.setModal(true);
    stats.exec();
}

void MainWindow::on_pB_TirerParMontant_clicked()
{
    ui->label_Info->setText("Tri par Montant effectué");
    ui->tab_res->setModel(R.tri_Montant());
}





















//ARDUINO YOSRI+SALMA



/*void MainWindow::on_tri_salaire_clicked()
{
    Employe E;

    ui->tab_employe->setModel(E.tri_salaire());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}*/

void MainWindow::on_pb_accept_clicked()
{
    A.write_to_arduino("1");
}

void MainWindow::on_pb_refuser_clicked()
{
       A.write_to_arduino("0");
}

void MainWindow::on_arduino_clicked()
{

    data = a.read_from_arduino() ;

   if (a.read_from_arduino()=="1"){
 QMessageBox::information(nullptr, QObject::tr("OK"),
             QObject::tr("carte validee .\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);


}


else
 {
 QMessageBox::critical(nullptr, QObject::tr("not OK"),
             QObject::tr("carte non validee  .\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
}
}





void MainWindow::update_label()
{
    data=A.read_from_arduino();

    // The Arduino sends "1" (card accepted) or "0" (refused); shown on the access tab.
    if (data == "1")
        ui->label_9->setText("ON");
    else if (data == "0")
        ui->label_9->setText("OFF");
}
