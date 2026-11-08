#include "mainwindow.h"
#include "connection.h"
#include "dialog_statistiques.h"
#include "theme.h"

#include <QApplication>
#include <QDir>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QTabBar>
#include <QTabWidget>
#include <QTableView>
#include <QTimer>

// Saves a PNG of every tab and of the statistics dialog, then quits.
// Used to produce the screenshots in docs/: HayaTrip --capture <folder>
static void captureScreens(MainWindow &w, const QString &out)
{
    // Let layouts and chart animations finish before grabbing.
    auto settle = [] {
        QElapsedTimer timer;
        timer.start();
        while (timer.elapsed() < 1200)
            QApplication::processEvents(QEventLoop::AllEvents, 50);
    };
    QDir().mkpath(out);

    QTabWidget *top = w.findChild<QTabWidget *>("tabWidget");
    for (int i = 0; top && i < top->count(); ++i) {
        top->setCurrentIndex(i);
        QTabWidget *sub = top->widget(i)->findChild<QTabWidget *>();
        const int pages = sub ? sub->count() : 1;
        for (int j = 0; j < pages; ++j) {
            if (sub) sub->setCurrentIndex(j);
            settle();
            w.grab().save(QString("%1/tab%2_%3.png").arg(out).arg(i).arg(j));
        }
    }

    // Trips: select the first trip and generate its QR code.
    if (QTableView *trips = w.findChild<QTableView *>("tab_voyageur_2")) {
        for (int i = 0; top && i < top->count(); ++i)
            if (top->widget(i)->isAncestorOf(trips)) top->setCurrentIndex(i);
        if (QTabWidget *sub = top->currentWidget()->findChild<QTabWidget *>()) sub->setCurrentIndex(0);
        trips->selectRow(0);
        settle();
        QMetaObject::invokeMethod(&w, "on_qr_button_clicked");
        settle();
        w.grab().save(out + "/trips_qr.png");
    }

    Dialog_Statistiques stats;
    stats.show();
    settle();
    stats.grab().save(out + "/reservation_stats.png");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("HayaTrip");
    Theme::apply(a);

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(nullptr, QObject::tr("Base de données"),
                              QObject::tr("Connexion à la base de données impossible."));
        return 1;
    }

    MainWindow w;
    Theme::polishTables(&w);
    // Module navigation: set the font on the widget (not in the stylesheet) so tabs are sized for it.
    if (QTabWidget *modules = w.findChild<QTabWidget *>("tabWidget"))
        modules->tabBar()->setFont(QFont("Segoe UI", 10, QFont::DemiBold));
    w.show();

    const QStringList args = a.arguments();
    const int capture = args.indexOf("--capture");
    if (capture != -1 && capture + 1 < args.size()) {
        const QString out = args.at(capture + 1);
        QTimer::singleShot(800, [&w, out, &a] { captureScreens(w, out); a.quit(); });
    }

    return a.exec();
}
