#include "mainwindow.hpp"
#include "ui_mainwindow.h"

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
    QIcon::hasThemeIcon("object-rotate-righ"));

  //If the theme is not compatible, the program will use breeze theme
  if(!isThemeCompatible){
    QIcon::setThemeName("breeze");
  }

  ui->stackedWidget->setCurrentIndex(0);

  //page_menu (0)
  ui->tbtn_compress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_compress->setIcon(QIcon::fromTheme("zoom-out"));
  ui->tbtn_compress->setIconSize(QSize(MENUICONSIZE,MENUICONSIZE));

  ui->tbtn_split->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_split->setIcon(QIcon::fromTheme("edit-cut"));
  ui->tbtn_split->setIconSize(QSize(MENUICONSIZE,MENUICONSIZE));

  ui->tbtn_merge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_merge->setIcon(QIcon::fromTheme("merge"));
  ui->tbtn_merge->setIconSize(QSize(MENUICONSIZE,MENUICONSIZE));

  ui->tbtn_rotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_rotate->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->tbtn_rotate->setIconSize(QSize(MENUICONSIZE,MENUICONSIZE));

  //page_compress (1)
  ui->tbtn_return1->setIcon(QIcon::fromTheme("go-previous"));

  ui->tbtn_pdfCompress->setIcon(QIcon::fromTheme("zoom-out"));
  ui->tbtn_pdfCompress->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->tbtn_pdfCompress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  //page_split (2)
  ui->tbtn_return2->setIcon(QIcon::fromTheme("go-previous"));

  ui->spinBox_fistPage->setMinimum(1);
  ui->rbtn_splitRange->setChecked(true);

  ui->tbtn_pdfSplit->setIcon(QIcon::fromTheme("edit-cut"));
  ui->tbtn_pdfSplit->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->tbtn_pdfSplit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  //page_merge (3)
  ui->tbtn_return3->setIcon(QIcon::fromTheme("go-previous"));

  ui->btn_Madd->setIcon(QIcon::fromTheme("list-add"));
  ui->btn_Madd->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->btn_Madd->setToolTip(tr("Click to add a PDF file"));

  ui->btn_Mrm->setIcon(QIcon::fromTheme("list-remove"));
  ui->btn_Mrm->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->btn_Mrm->setToolTip(tr("Click to remove a PDF file"));

  ui->btn_Mup->setIcon(QIcon::fromTheme("go-up"));
  ui->btn_Mup->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->btn_Mup->setToolTip(tr("Click to change the merge order"));

  ui->btn_Mdown->setIcon(QIcon::fromTheme("go-down"));
  ui->btn_Mdown->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->btn_Mdown->setToolTip(tr("Click to change the merge order"));

  ui->tbtn_pdfMerge->setIcon(QIcon::fromTheme("merge"));
  ui->tbtn_pdfMerge->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->tbtn_pdfMerge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  //page_rotate (4)
  ui->tbtn_return4->setIcon(QIcon::fromTheme("go-previous"));

  ui->btn_left->setIcon(QIcon::fromTheme("object-rotate-left"));
  ui->btn_left->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->btn_left->setToolTip(tr("click to rotate the PDF 90 degrees to the left"));

  ui->btn_right->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->btn_right->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->btn_right->setToolTip(tr("click to rotate the PDF 90 degrees to the right"));

  ui->btn_left->hide();
  ui->btn_right->hide();
  ui->label_pdfCover->hide();

  ui->tbtn_pdfRotate->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->tbtn_pdfRotate->setIconSize(QSize(ICONSIZE,ICONSIZE));
  ui->tbtn_pdfRotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MainWindow::~MainWindow(){
  delete ui;
}

//Other functions
void MainWindow::runCommand(QString command){
  qDebug() << "executing command: " << command << "\n";

  ui->statusBar->showMessage(tr("Processing..."));

  QProcess process;
  process.start("sh");

  process.write(qPrintable(command));
  process.closeWriteChannel();
  process.waitForFinished();

  qDebug() << process.readAllStandardOutput() << "\n";
  QString error = process.readAllStandardError();

  if(!error.isEmpty()){
    QMessageBox::warning(this,tr("ERROR"),error);
    ui->statusBar->showMessage(tr("Failed"),10000);
  }else{
    ui->statusBar->showMessage(tr("Success!"),10000);
  }

  process.close();

  qDebug() << "finished to execute: " << command << "\n";
}

QString MainWindow::getSaveFileName(){
  return QFileDialog::getSaveFileName(this,tr("Save file"),QDir::homePath(),"PDF - Portable Document Format (*.pdf)");
}
QString MainWindow::getOpenFileName(){
  return QFileDialog::getOpenFileName(this,tr("Select the PDF file"),QDir::homePath(),"PDF - Portable Document Format (*.pdf  *.PDF)");
}
