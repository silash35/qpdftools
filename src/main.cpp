#include "interface/mainwindow.hpp"
#include <QApplication>
#include <QStyleHints>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QApplication::setDesktopFileName("br.eng.silas.qpdftools");

  QString fallbackIcon =
      Qt::ColorScheme() == Qt::ColorScheme::Dark ? ":fallback-icons-dark" : ":fallback-icons-light";
  QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << fallbackIcon);

  QTranslator translator;
  // look up e.g. :/i18n/qpdftools_pt_BR.qm
  if (translator.load(QLocale(), "qpdftools", "_", ":/i18n"))
    QCoreApplication::installTranslator(&translator);

  MainWindow w;
  w.show();
  return a.exec();
}
