#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  // Main
  ui->setupUi(this);
  setWindowIcon(QIcon(QIcon::fromTheme("io.github.silash35.qpdftools")));
  setWindowTitle("Qpdf Tools");
  setCentralWidget(ui->stackedWidget);

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
  connect(compressPage, &CompressPage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  SplitPage *splitPage = new SplitPage(this);
  ui->stackedWidget->addWidget(splitPage);
  connect(splitPage, &SplitPage::setPage, this, &MainWindow::setPage);
  connect(splitPage, &SplitPage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  MergePage *mergePage = new MergePage(this);
  ui->stackedWidget->addWidget(mergePage);
  connect(mergePage, &MergePage::setPage, this, &MainWindow::setPage);
  connect(mergePage, &MergePage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  RotatePage *rotatePage = new RotatePage(this);
  ui->stackedWidget->addWidget(rotatePage);
  connect(rotatePage, &RotatePage::setPage, this, &MainWindow::setPage);
  connect(rotatePage, &RotatePage::runAsyncFunction, this, &MainWindow::runAsyncFunction);
}

MainWindow::~MainWindow() { delete ui; }

// Public Slots
void MainWindow::setPage(int newPage) { ui->stackedWidget->setCurrentIndex(newPage); }

void MainWindow::runAsyncFunction(std::function<void()> asyncFunction) {
  ui->statusBar->showMessage(tr("Processing..."));

  QtConcurrent::run(asyncFunction)
      .then([this] { ui->statusBar->showMessage(tr("Success!"), 5000); })
      .onFailed([this](QString error) {
        QMessageBox::warning(this, tr("ERROR"), error);
        ui->statusBar->showMessage(tr("Failed"), 5000);
      });
}
