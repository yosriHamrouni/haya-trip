#include "theme.h"

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QHeaderView>
#include <QPalette>
#include <QStyleFactory>
#include <QTableView>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

namespace Theme {

QList<QColor> seriesColors()
{
    return { Primary, Accent, QColor("#f59e0b"), QColor("#8b5cf6"), QColor("#ef4444"), QColor("#0ea5e9") };
}

void apply(QApplication &app)
{
    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette p;
    p.setColor(QPalette::Window, Background);
    p.setColor(QPalette::WindowText, Ink);
    p.setColor(QPalette::Base, Surface);
    p.setColor(QPalette::AlternateBase, QColor("#f8fafc"));
    p.setColor(QPalette::Text, Ink);
    p.setColor(QPalette::Button, Surface);
    p.setColor(QPalette::ButtonText, Ink);
    p.setColor(QPalette::Highlight, QColor("#dbeafe"));
    p.setColor(QPalette::HighlightedText, Ink);
    p.setColor(QPalette::ToolTipBase, Ink);
    p.setColor(QPalette::ToolTipText, Surface);
    app.setPalette(p);

    QFont font("Segoe UI");
    font.setPointSizeF(9);
    app.setFont(font);

    QFile qss(":/style.qss");
    if (qss.open(QFile::ReadOnly | QFile::Text))
        app.setStyleSheet(QString::fromUtf8(qss.readAll()));
}

void styleChart(QChart *chart, const QString &title)
{
    chart->setTitle(title);
    QFont titleFont("Segoe UI", 11, QFont::DemiBold);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(Ink);
    chart->setBackgroundBrush(Surface);
    chart->setBackgroundRoundness(8);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QLegend *legend = chart->legend();
    legend->setAlignment(Qt::AlignBottom);
    legend->setBackgroundVisible(false);
    legend->setLabelColor(Muted);
    legend->setFont(QFont("Segoe UI", 9));

    const QList<QColor> colors = seriesColors();
    for (QAbstractSeries *s : chart->series()) {
        if (auto pie = qobject_cast<QPieSeries *>(s)) {
            pie->setHoleSize(0.45);
            int i = 0;
            for (QPieSlice *slice : pie->slices()) {
                slice->setBrush(colors.at(i++ % colors.size()));
                slice->setBorderColor(Surface);
                slice->setBorderWidth(2);
                slice->setExploded(false);
                slice->setLabelVisible(false);
            }
        } else if (auto bars = qobject_cast<QAbstractBarSeries *>(s)) {
            int i = 0;
            for (QBarSet *set : bars->barSets()) {
                set->setColor(colors.at(i++ % colors.size()));
                set->setBorderColor(Qt::transparent);
            }
        }
    }
}

void polishTables(QWidget *root)
{
    for (QTableView *t : root->findChildren<QTableView *>()) {
        t->setAlternatingRowColors(true);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->setShowGrid(false);
        t->verticalHeader()->setVisible(false);
        t->verticalHeader()->setDefaultSectionSize(30);
        t->horizontalHeader()->setStretchLastSection(true);
        t->horizontalHeader()->setHighlightSections(false);
        t->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}

}
