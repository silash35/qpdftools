#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::configRotate() {
  ui->tbtn_return4->setIcon(QIcon::fromTheme("go-previous"));

  ui->btn_left->setIcon(QIcon::fromTheme("object-rotate-left"));
  ui->btn_left->setIconSize(QSize(ICONSIZE, ICONSIZE));
  ui->btn_left->setToolTip(tr("click to rotate the PDF 90 degrees to the left"));

  ui->btn_right->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->btn_right->setIconSize(QSize(ICONSIZE, ICONSIZE));
  ui->btn_right->setToolTip(tr("click to rotate the PDF 90 degrees to the right"));

  ui->btn_left->hide();
  ui->btn_right->hide();
  ui->label_pdfCover->hide();

  ui->tbtn_pdfRotate->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->tbtn_pdfRotate->setIconSize(QSize(ICONSIZE, ICONSIZE));
  ui->tbtn_pdfRotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MainWindow::on_tbtn_return4_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void MainWindow::on_btn_selectFile4_clicked() {
  ui->ln_file4->clear();
  ui->ln_file4->setText(getOpenFileName());
  ui->ln_file4->setFocus();
}

void MainWindow::on_ln_file4_textChanged(const QString &pdfPath) {
  rotate = 0;
  command.clear();

  if (QFile::exists(pdfPath)) {
    ui->btn_left->show();
    ui->btn_right->show();
    ui->label_pdfCover->show();

    command << "-q"
            << "-o" << PDFCOVERPATH << "-sDEVICE=pngalpha"
            << "-dLastPage=1"
            << "-dUseCropBox" << pdfPath;
    runCommand("gs", command);

    QPixmap pdfCover(PDFCOVERPATH);
    ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
  } else {
    ui->btn_left->hide();
    ui->btn_right->hide();
    ui->label_pdfCover->hide();
    command.clear();
  }
}

void MainWindow::on_btn_left_clicked() {
  if (rotate <= 0) {
    rotate = 360;
  }

  rotate -= 90;
  QTransform rote;
  rote = rote.rotate(rotate);

  QPixmap pdfCover(PDFCOVERPATH);
  pdfCover = QPixmap(pdfCover.transformed(rote));
  ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
}

void MainWindow::on_btn_right_clicked() {
  if (rotate >= 360) {
    rotate = 0;
  }

  rotate += 90;
  QTransform rote;
  rote = rote.rotate(rotate);

  QPixmap pdfCover(PDFCOVERPATH);
  pdfCover = QPixmap(pdfCover.transformed(rote));
  ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
}

void MainWindow::on_tbtn_pdfRotate_clicked() {

  isRunnable = true;
  command.clear();

  if (!QFile::exists(ui->ln_file4->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    isRunnable = false;
  }

  QString targetFile = getSaveFileName();
  if (targetFile == "invalid") {
    isRunnable = false;
  }

  command << "sel";
  command << "A=" + ui->ln_file4->text();

  if (rotate == 90) {
    command << "A1-endR";
  } else if (rotate == 180) {
    command << "A1-endD";
  } else if (rotate == 270) {
    command << "A1-endL";
  } else {
    command << "A1-end";
  }

  if (isRunnable) {
    command << targetFile;

    runCommand("stapler", command);
  } else {
    qDebug() << "command not executed";
  }
  command.clear();
}
