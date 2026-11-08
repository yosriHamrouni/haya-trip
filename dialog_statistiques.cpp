#include "dialog_statistiques.h"
#include "ui_dialog_statistiques.h"
#include "qcustomplot.h"
#include "mainwindow.h"
#include "reservation.h"
#include "theme.h"

Dialog_Statistiques::Dialog_Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Statistiques)
{
    ui->setupUi(this);
    Dialog_Statistiques::MakeStat();
}

Dialog_Statistiques::~Dialog_Statistiques()
{
    delete ui;
}
void Dialog_Statistiques::statistiques(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery qry;
    int i=0;
    qry.exec("SELECT ID FROM RESERVATION");
    while (qry.next())
    {
        QString ID = qry.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<ID;
    }
}
void Dialog_Statistiques::MakeStat()
{
    /***** Background *****/
    ui->plot->setBackground(QBrush(Theme::Surface));
    QCPBars *A = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);
    /***** Couleurs*****/
    A->setName("Montant des réservations par ID");
    A->setPen(Qt::NoPen);
    A->setBrush(Theme::Primary);
    A->setWidth(0.6);
    /***** Axe des abscisses *****/
    QVector<double> ticks;
    QVector<QString> labels;
    statistiques(&ticks,&labels);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->plot->xAxis->setTicker(textTicker);
    ui->plot->xAxis->setTickLabelRotation(0);
    ui->plot->xAxis->setSubTicks(false);
    ui->plot->xAxis->setLabel("ID");
    ui->plot->xAxis->setTickLength(0, 4);
    ui->plot->xAxis->setRange(0, ticks.size() + 1);
    ui->plot->xAxis->setBasePen(QPen(Theme::Line));
    ui->plot->xAxis->setTickPen(QPen(Theme::Line));
    ui->plot->xAxis->grid()->setVisible(true);
    ui->plot->xAxis->grid()->setVisible(false);
    ui->plot->xAxis->setTickLabelColor(Theme::Muted);
    ui->plot->xAxis->setLabelColor(Theme::Muted);
    /***** Axe des ordonnées *****/
    ui->plot->yAxis->setRange(0,200);
    ui->plot->yAxis->setPadding(5);
    ui->plot->yAxis->setLabel("MONTANT");
    ui->plot->yAxis->setBasePen(QPen(Theme::Line));
    ui->plot->yAxis->setTickPen(QPen(Theme::Line));
    ui->plot->yAxis->setSubTickPen(QPen(Theme::Line));
    ui->plot->yAxis->grid()->setSubGridVisible(false);
    ui->plot->yAxis->setTickLabelColor(Theme::Muted);
    ui->plot->yAxis->setLabelColor(Theme::Muted);
    ui->plot->yAxis->grid()->setPen(QPen(Theme::Line, 0, Qt::SolidLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> PlaceData;
    QSqlQuery q1("SELECT MONTANT FROM RESERVATION");
    while (q1.next())
    {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    A->setData(ticks, PlaceData);
    double maxAmount = 0;
    for (double v : PlaceData) maxAmount = qMax(maxAmount, v);
    ui->plot->yAxis->setRange(0, maxAmount > 0 ? maxAmount * 1.2 : 100);
    ui->plot->legend->setVisible(true);
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(9);
    ui->plot->legend->setFont(legendFont);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void Dialog_Statistiques::on_pushButton_Fermer_clicked()
{
    close();
}
