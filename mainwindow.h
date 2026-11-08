#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "arduino.h"


#include "client.h"


#include "voyage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>










#include "reservation.h"
#include <QMainWindow>




namespace Ui {
class MainWindow;
}



class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu ;
class QAction;




















class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_clicked();

    void on_bin_image_clicked();

    void on_tri_clicked();

    void on_recherher_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_pdf_clicked();

    void on_le_modd_clicked();

    void on_le_fich_excel_clicked();

    void on_tri_alpha_clicked();

   // void on_tri_salaire_clicked();

    void on_pb_accept_clicked();

    void on_pb_refuser_clicked();

    void on_arduino_clicked();

    void update_label();


//CLIENT
    // void on_pushButton_clicked();

     void on_pb_ajouter_client_clicked();

     void on_pb_supprimer_client_clicked();




     //void on_comboBox_supp_activated(const QString &arg1);

     void on_pb_update_clicked();

     void on_tab_clients_activated(const QModelIndex &index);

     void on_pb_find_clicked();

     void on_pb_tri_client_clicked();

     void on_pb_genererPdf_clicked();


//VOYAGES


     void on_le_ajouter_clicked();

     void on_boutton_supp_clicked();

     void on_le_update_clicked();

     void on_recherche_button_clicked();

     void on_tri_button_clicked();

     void on_tri_button_2_clicked();

     void on_tri_button_3_clicked();

     void on_pdf_button_clicked();

     void on_tab_voyageur_2_activated(const QModelIndex &index);

     void on_recherche_button_2_clicked();

     void on_recherche_button_3_clicked();

     void on_quitter_button_clicked();



     void on_qr_button_clicked();

     void on_traduire_clicked();




    void total (int a,  int b, int c, int d, int e, int f, int  g,  int h );
    void update_nb();



// RESERVATIONS




    void on_pB_Ajouter_clicked();

    void on_pB_Supprimer_clicked();

    void on_pB_Modifier_clicked();

    void on_pB_TirerParID_clicked();

    void on_pB_TirerParType_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pB_Recherche_clicked();

    void on_pB_ExPDF_clicked();

    void on_pushButton_SupprimerS_clicked();

    void on_pushButton_Fermer_clicked();

    void on_pB_Mailing_clicked();

    void on_pB_Stats_clicked();

    void on_pB_TirerParMontant_clicked();


























private:
    Ui::MainWindow *ui;
    Employe E;
    arduino A,a;

    QByteArray data;

    Client C;

    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOptionsMenu;
    QAction *mEncenderAction;
    QAction  *mApagarAction;
    QAction *mCapturarAction;
  //  QAction




    voyage V;


 reservation R;






};

#endif // MAINWINDOW_H
