#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../api/ghostscript.hpp"
#include "../api/qpdf.hpp"
#include "../api/stapler.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

  // Main
  ui->setupUi(this);
  this->setWindowIcon(QIcon(QIcon::fromTheme("qpdftools")));
  this->setWindowTitle("Qpdf Tools");
  this->setCentralWidget(ui->stackedWidget);

  // Check if the system theme has the necessary icons.
  bool isThemeCompatible =
      (QIcon::hasThemeIcon("zoom-out") and QIcon::hasThemeIcon("edit-cut") and
       QIcon::hasThemeIcon("merge") and QIcon::hasThemeIcon("object-rotate-right"));

  // If the theme is not compatible, the program will use breeze theme
  if (!isThemeCompatible) {
    QIcon::setThemeName("breeze");
  }

  ui->stackedWidget->setCurrentIndex(0);

  configMenu();
  configCompress();
  configSplit();
  configMerge();
  configRotate();
}

MainWindow::~MainWindow() { delete ui; }

// Other functions
void MainWindow::runCommand(QString command, QStringList arguments, QString dir) {
  ui->statusBar->showMessage(tr("Processing..."));

  QString error = "";

  if (command == "gs") {
    ghostscript.start(arguments, dir);
    error = ghostscript.getStandardError();
  } else if (command == "stapler") {
    stapler.start(arguments, dir);
    error = stapler.getStandardError();
  } else if (command == "qpdf") {
    qpdf.start(arguments, dir);
    error = qpdf.getStandardError();
  }

  if (!error.isEmpty()) {
    QMessageBox::warning(this, tr("ERROR"), error);
    ui->statusBar->showMessage(tr("Failed"), 5000);
  } else {
    ui->statusBar->showMessage(tr("Success!"), 5000);
  }
}

QString MainWindow::getOpenFileName() {
  QString file = QFileDialog::getOpenFileName(this, tr("Select the PDF file"), lastDirectory.get(),
                                              "PDF - Portable Document Format (*.pdf  *.PDF)");

  if (!file.isEmpty()) {
    lastDirectory.setByFile(file);
  }
  return file;
}

QString MainWindow::getSaveFileName() {
  QString file = QFileDialog::getSaveFileName(this, tr("Save file"), lastDirectory.get(),
                                              "PDF - Portable Document Format (*.pdf)");
  if (file.isEmpty()) {
    file = "invalid";
  } else {
    lastDirectory.setByFile(file);
  }

  return file;
}
