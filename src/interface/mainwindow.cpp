#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../api/ghostscript.hpp"
#include "../api/stapler.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
  //Main
  ui->setupUi(this);
  this->setWindowIcon(QIcon(QIcon::fromTheme("qpdftools")));
  this->setWindowTitle("Qpdf Tools");
  this->setCentralWidget(ui->stackedWidget);

  //Check if the system theme has the necessary icons.
  bool isThemeCompatible = (QIcon::hasThemeIcon("zoom-out") and
    QIcon::hasThemeIcon("edit-cut") and
    QIcon::hasThemeIcon("merge") and
    QIcon::hasThemeIcon("object-rotate-right"));

  //If the theme is not compatible, the program will use breeze theme
  if(!isThemeCompatible){
    QIcon::setThemeName("breeze");
  }

  ui->stackedWidget->setCurrentIndex(0);

  configMenu();
  configCompress();
  configSplit();
  configMerge();
  configRotate();
}

MainWindow::~MainWindow(){
  delete ui;
}

//Other functions
void MainWindow::runCommand(QString command, QStringList arguments){

  qDebug() << "executing command: " << command << "\n";
  ui->statusBar->showMessage(tr("Processing..."));

  if(command == "gs"){
    ghostscript.start(arguments);
  }

  QString error = ghostscript.getStandardError();

  if(!error.isEmpty()){
    QMessageBox::warning(this,tr("ERROR"),error);
    ui->statusBar->showMessage(tr("Failed"),10000);
  }else{
    ui->statusBar->showMessage(tr("Success!"),10000);
  }

}

QString MainWindow::getOpenFileName(){
  return QFileDialog::getOpenFileName(this,tr("Select the PDF file"),QDir::homePath(),"PDF - Portable Document Format (*.pdf  *.PDF)");
}

QString MainWindow::getSaveFileName(){
  return QFileDialog::getSaveFileName(this,tr("Save file"),QDir::homePath(),"PDF - Portable Document Format (*.pdf)");
}
