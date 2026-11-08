#include "connection.h"

#include <QDir>
#include <QStandardPaths>
#include <QVariant>

// Two ways to run the app:
//  - default: a local SQLite file with fictional demo data, so the app opens anywhere;
//  - HAYATRIP_DB=oracle: the original Oracle XE database through an ODBC data source
//    (HAYATRIP_ODBC_DSN, HAYATRIP_DB_USER, HAYATRIP_DB_PASSWORD).

Connection::Connection() {}

static QString env(const char *name, const QString &fallback = QString())
{
    const QByteArray v = qgetenv(name);
    return v.isEmpty() ? fallback : QString::fromLocal8Bit(v);
}

static void seedDemoData()
{
    QSqlQuery q;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES") && q.next() && q.value(0).toInt() > 0)
        return;

    const char *statements[] = {
        "CREATE TABLE IF NOT EXISTS EMPLOYES (ID INTEGER, NUMERO_TELEPHONE TEXT, SALAIRE INTEGER, NOM TEXT, PRENOM TEXT, DATE_NAISSANCE TEXT, IMAGE TEXT)",
        "CREATE TABLE IF NOT EXISTS CLIENT (ID_CLIENT INTEGER, NOM_CLIENT TEXT, PRENOM_CLIENT TEXT, TEL_CLIENT TEXT, EMAIL_CLIENT TEXT, RDV_CLIENT TEXT)",
        "CREATE TABLE IF NOT EXISTS VOYAGE (NUM_VOYAGE INTEGER, DEPART TEXT, DESTINATION TEXT, DATE_DEPART TEXT, DATE_RETOUR TEXT)",
        "CREATE TABLE IF NOT EXISTS RESERVATION (ID INTEGER, NOM TEXT, PRENOM TEXT, MONTANT INTEGER)",
        "CREATE TABLE IF NOT EXISTS ACTUALITE (DESTINATION TEXT)",
        // Fictional people and trips, for demonstration only.
        "INSERT INTO EMPLOYES VALUES (101,'22145870',1850,'Ben Salah','Amine','1994-03-12',''),(102,'55301244',2400,'Trabelsi','Sarra','1990-07-25',''),"
        "(103,'98417733',1350,'Gharbi','Mehdi','1998-11-02',''),(104,'21650098',2900,'Mansouri','Ines','1987-01-18',''),"
        "(105,'50772361',1600,'Jaziri','Karim','1996-05-30',''),(106,'97224410',2100,'Haddad','Nour','1993-09-09','')",
        "INSERT INTO CLIENT VALUES (1,'Riahi','Youssef','23456781','youssef.riahi@example.com','2022-11-20'),(2,'Kacem','Leila','54123987','leila.kacem@example.com',NULL),"
        "(3,'Bouzid','Omar','92876540','omar.bouzid@example.com','2022-11-24'),(4,'Ferchichi','Rim','26544310','rim.ferchichi@example.com',NULL),"
        "(5,'Mejri','Sami','58990012','sami.mejri@example.com','2022-12-02')",
        "INSERT INTO VOYAGE VALUES (1,'tunis','france','2022-12-01','2022-12-08'),(2,'tunis','italy','2022-12-05','2022-12-12'),(3,'sfax','egypt','2022-12-10','2022-12-17'),"
        "(4,'tunis','usa','2022-12-15','2022-12-29'),(5,'monastir','frankfurt','2022-12-18','2022-12-23'),(6,'djerba','tunisia','2022-12-20','2022-12-24'),"
        "(7,'tunis','france','2023-01-03','2023-01-10')",
        "INSERT INTO RESERVATION VALUES (1,'Riahi','Youssef',120),(2,'Kacem','Leila',85),(3,'Bouzid','Omar',160),(4,'Ferchichi','Rim',95),(5,'Mejri','Sami',140),(6,'Haddad','Nour',70)",
    };
    for (const char *s : statements)
        q.exec(s);
}

bool Connection::createconnect()
{
    if (env("HAYATRIP_DB").compare("oracle", Qt::CaseInsensitive) == 0) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName(env("HAYATRIP_ODBC_DSN", "Source_projet2A"));
        db.setUserName(env("HAYATRIP_DB_USER"));
        db.setPassword(env("HAYATRIP_DB_PASSWORD"));
        return db.open();
    }

    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(env("HAYATRIP_SQLITE_PATH", dir + "/hayatrip_demo.sqlite"));
    if (!db.open())
        return false;
    seedDemoData();
    return true;
}
