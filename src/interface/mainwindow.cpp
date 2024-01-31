#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../api/ghostscript.hpp"
#include "../api/qpdf.hpp"

#include "pages/0-menu/menu.hpp"
#include "pages/1-compress/compress.hpp"
#include "pages/2-split/split.hpp"
#include "pages/3-merge/merge.hpp"
#include "pages/4-rotate/rotate.hpp"

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
  ui->stackedWidget->addWidget(menuPage);
  connect(menuPage, &MenuPage::setPage, this, &MainWindow::setPage);

  CompressPage *compressPage = new CompressPage(this);
  ui->stackedWidget->addWidget(compressPage);
  connect(compressPage, &CompressPage::setPage, this, &MainWindow::setPage);

  SplitPage *splitPage = new SplitPage(this);
  ui->stackedWidget->addWidget(splitPage);
  connect(splitPage, &SplitPage::setPage, this, &MainWindow::setPage);

  MergePage *mergePage = new MergePage(this);
  ui->stackedWidget->addWidget(mergePage);
  connect(mergePage, &MergePage::setPage, this, &MainWindow::setPage);

  RotatePage *rotatePage = new RotatePage(this);
  ui->stackedWidget->addWidget(rotatePage);
  connect(rotatePage, &RotatePage::setPage, this, &MainWindow::setPage);
}

MainWindow::~MainWindow() { delete ui; }

// Public Slots
void MainWindow::setPage(int newPage) { ui->stackedWidget->setCurrentIndex(newPage); }
