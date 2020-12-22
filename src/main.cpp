#include "interface/mainwindow.hpp"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator t;
  t.load(QLocale::system(), "qpdftools", "_", "/usr/lib/qpdftools");
  a.installTranslator(&t);

  MainWindow w;
  w.show();
  return a.exec();
}
