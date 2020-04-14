#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;

    if(QLocale::system().name() == QString("pt_BR")){
        t.load("/home/silas/qpdftools/qpdftools_pt_BR.qm");
        a.installTranslator(&t);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
