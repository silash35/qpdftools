#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::configCompress() {
  ui->tbtn_return1->setIcon(QIcon::fromTheme("go-previous"));
  ui->tbtn_pdfCompress->setIcon(QIcon::fromTheme("zoom-out"));
  ui->tbtn_pdfCompress->setIconSize(QSize(ICONSIZE, ICONSIZE));
  ui->tbtn_pdfCompress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MainWindow::on_tbtn_return1_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void MainWindow::on_btn_selectFile1_clicked() {
  ui->ln_file1->clear();
  ui->ln_file1->setText(getOpenFileName());
  ui->ln_file1->setFocus();
}

void MainWindow::on_tbtn_pdfCompress_clicked() {
  isRunnable = true;

  if (!QFile::exists(ui->ln_file1->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    isRunnable = false;
  }

  command.clear();
  command << "-sDEVICE=pdfwrite"
          << "-dCompatibilityLevel=1.4";

  if (ui->rbtn_screen->isChecked()) {
    command << "-dPDFSETTINGS=/screen";
  } else if (ui->rbtn_ebook->isChecked()) {
    command << "-dPDFSETTINGS=/ebook";
  } else if (ui->rbtn_printer->isChecked()) {
    command << "-dPDFSETTINGS=/printer";
  } else if (ui->rbtn_prepress->isChecked()) {
    command << "-dPDFSETTINGS=/prepress";
  } else {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a compression mode"));
    isRunnable = false;
  }

  if (isRunnable) {

    command << "-dNOPAUSE"
            << "-dBATCH";
    command << "-sOutputFile=" + getSaveFileName();
    command << ui->ln_file1->text();

    runCommand("gs", command);
  } else {
    qDebug() << "command not executed";
  }
}
