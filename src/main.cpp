#include "interface/mainwindow.hpp"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QApplication::setDesktopFileName("io.github.silash35.qpdftools");

  QTranslator translator;
  // look up e.g. :/i18n/qpdftools_pt_BR.qm
  if (translator.load(QLocale(), "qpdftools", "_", ":/i18n"))
    QCoreApplication::installTranslator(&translator);

  MainWindow w;
  w.show();
  return a.exec();
}
