#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../api/ghostscript.hpp"
#include "../api/qpdf.hpp"

#include "pages/0-menu/menu.hpp"
#include "pages/1-compress/compress.hpp"
#include "pages/2-split/split.hpp"
#include "pages/3-merge/merge.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  // Main
  ui->setupUi(this);
  this->setWindowIcon(QIcon(QIcon::fromTheme("io.github.silash35.qpdftools")));
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

  MenuPage *menuPage = new MenuPage(this);
  ui->stackedWidget->insertWidget(0, menuPage);
  connect(menuPage, &MenuPage::setPage, this, &MainWindow::setPage);

  CompressPage *compressPage = new CompressPage(this);
  ui->stackedWidget->insertWidget(1, compressPage);
  connect(compressPage, &CompressPage::setPage, this, &MainWindow::setPage);

  SplitPage *splitPage = new SplitPage(this);
  ui->stackedWidget->insertWidget(1, splitPage);
  connect(splitPage, &SplitPage::setPage, this, &MainWindow::setPage);

  MergePage *mergePage = new MergePage(this);
  ui->stackedWidget->insertWidget(1, mergePage);
  connect(mergePage, &MergePage::setPage, this, &MainWindow::setPage);

  configRotate();

  ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() { delete ui; }

// Public Slots
void MainWindow::setPage(int newPage) { ui->stackedWidget->setCurrentIndex(newPage); }

// Other functions
void MainWindow::runCommand(QString command, QStringList arguments, QString dir) {
  ui->statusBar->showMessage(tr("Processing..."));

  QString error = "";

  if (command == "gs") {
    ghostscript.start(arguments, dir);
    error = ghostscript.getStandardError();
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
