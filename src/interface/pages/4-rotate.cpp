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

void MainWindow::on_ln_file4_textChanged(const QString &arg1) {
  rotate = 0;

  if (QFile::exists(arg1)) {
    ui->btn_left->show();
    ui->btn_right->show();
    ui->label_pdfCover->show();

    command << "-q -o '";
    command << PDFCOVERPATH;
    command << "' -sDEVICE=pngalpha -dLastPage=1 -dUseCropBox '" + arg1 + "'";
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

  if (!QFile::exists(ui->ln_file4->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    isRunnable = false;
  }

  command << "sel A='" + ui->ln_file4->text() + "' A1-end";

  if ((rotate == 0) or (rotate == 360)) {
    command << " '";
  } else if (rotate == 90) {
    command << "R '";
  } else if (rotate == 180) {
    command << "D '";
  } else if (rotate == 270) {
    command << "L '";
  }

  if (isRunnable) {
    command += getSaveFileName() + "'";

    runCommand("stapler", command);
  } else {
    qDebug() << "command not executed";
  }
  command.clear();
}
