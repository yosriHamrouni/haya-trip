#ifndef THEME_H
#define THEME_H

// Shared look for the whole app: Fusion style, a light palette, one stylesheet
// (resources/style.qss) and helpers that give charts and tables the same colours.

#include <QColor>
#include <QtCharts/QChart>

class QApplication;
class QWidget;

namespace Theme {

const QColor Primary("#2563eb");
const QColor PrimaryDark("#1d4ed8");
const QColor Accent("#14b8a6");
const QColor Ink("#0f172a");
const QColor Muted("#64748b");
const QColor Surface("#ffffff");
const QColor Background("#f1f5f9");
const QColor Line("#e2e8f0");

/** Series colours used by every chart, in order. */
QList<QColor> seriesColors();

/** Fusion style, palette, font and stylesheet. Call once, before creating windows. */
void apply(QApplication &app);

/** Clean background, readable title, legend at the bottom and palette colours on the series. */
void styleChart(QtCharts::QChart *chart, const QString &title);

/** Alternating rows, row selection, stretched last column and no row numbers on every table under root. */
void polishTables(QWidget *root);

}

#endif // THEME_H
