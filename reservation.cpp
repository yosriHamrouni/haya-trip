#include <QDir>
#include <QStandardPaths>
#include "reservation.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QFile>
/**************************************/
/*Declaration les donnnes*/
reservation::reservation()
{
    ID=0;
    NOM=" ";
    PRENOM=" ";
    MONTANT=0;
}
reservation::reservation(int ID, QString NOM, QString PRENOM, int MONTANT)
{
    this->ID=ID;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->MONTANT=MONTANT;
}
/**************************************/
/*Creation des pretit fonctions pour recuperer les donnes*/
int reservation::getid()
{
    return ID;
}
QString reservation::getnom()
{
    return NOM;
}
QString reservation::getprenom()
{
    return PRENOM;
}
int reservation::getmontant()
{
    return MONTANT;
}
/**************************************/
/*Creation des pretit fonctions pour envoyer les donnes*/
void reservation::setid(int ID)
{
    this->ID=ID;
}
void reservation::setnom(QString NOM)
{
    this->NOM=NOM;
}
void reservation::setprenom(QString PRENOM)
{
    this->PRENOM=PRENOM;
}
void reservation::setmontant(int MONTANT)
{
    this->MONTANT=MONTANT;
}
/**************************************/
bool reservation::ajouterS() //Cette fonction pour ajouter les donnes dans le tableau SQL.
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
         query.prepare("INSERT INTO RESERVATION(ID,NOM,PRENOM,MONTANT)" "VALUES (:ID,:NOM,:PRENOM,:MONTANT)");
         query.bindValue(":ID", ID);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":MONTANT", MONTANT);
    return query.exec();
}
bool reservation::supprimerS(int ID) //Cette fonction pour suppimer les donnes dans le tableau SQL.
{
    QSqlQuery query;
         query.prepare("DELETE FROM RESERVATION where ID= :ID");
         query.bindValue(0, ID);
    return query.exec();
}
bool reservation::modifierS() //Cette fonction pour modifier les donnes dans le tableau SQL.
{
    QSqlQuery query;
        query.prepare("UPDATE RESERVATION SET NOM=:NOM, PRENOM=:PRENOM, MONTANT=:MONTANT WHERE ID=:ID ");
        query.bindValue(":ID", ID);
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":MONTANT", MONTANT);
    return query.exec();
}
/**************************************/
QSqlQueryModel* reservation::afficher() //cette QueryModel fonction pour afficher les donnes dans TableView.
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM RESERVATION");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    return  model;
}
QSqlQueryModel* reservation ::afficher_id() //cette QueryModel fonction pour afficher les ID dans ComboBox.
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT ID from RESERVATION");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return model;
}
/**************************************/

QSqlQueryModel * reservation::tri_id() //Fonction de la Tri par ID
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from RESERVATION order by ID");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    return model;
}
QSqlQueryModel * reservation::tri_nom() //Fonction de la Tri par Nom
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from RESERVATION order by NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    return model;
}
QSqlQueryModel * reservation::tri_Montant() //Fonction de la Tri par Montant
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from RESERVATION order by MONTANT");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    return model;
}
// Reservation history log, kept in the per-user app data folder.
static QString historyPath()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/historiques.txt";
}
/**************************************/
/* Les fonction Read/Write/Time/Clearh cest pour les logs dans le TextBrowser*/
QString reservation::read()
{
    QFile file(historyPath());
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void reservation::write(QString time, QString txt)
{
    QFile file(historyPath());
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString reservation::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void reservation::clearh()
{
    QFile file(historyPath());
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void reservation::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
/**************************************/
/*  Voici les fonctions cherche par ID et Nom et Montant */
void reservation::chercheID(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from RESERVATION where regexp_like(ID,:ID);");
   query->bindValue(":ID",x);
   if(x==0)
   {
       query->prepare("select * from RESERVATION;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void reservation::chercheMont(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from RESERVATION where regexp_like(MONTANT,:MONTANT);");
   query->bindValue(":MONTANT",x);
   if(x==0)
   {
       query->prepare("select * from RESERVATION;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void reservation::chercheNom(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from RESERVATION where regexp_like(NOM,:NOM);");
   query->bindValue(":NOM",x);
   if(x==0)
   {
       query->prepare("select * from RESERVATION;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
