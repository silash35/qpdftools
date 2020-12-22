#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::configSplit() {
  ui->tbtn_return2->setIcon(QIcon::fromTheme("go-previous"));

  ui->spinBox_fistPage->setMinimum(1);
  ui->rbtn_splitRange->setChecked(true);

  ui->tbtn_pdfSplit->setIcon(QIcon::fromTheme("edit-cut"));
  ui->tbtn_pdfSplit->setIconSize(QSize(ICONSIZE, ICONSIZE));
  ui->tbtn_pdfSplit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MainWindow::on_tbtn_return2_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void MainWindow::on_btn_selectFile2_clicked() {
  ui->ln_file2->clear();
  ui->ln_file2->setText(getOpenFileName());
  ui->ln_file2->setFocus();
}

void MainWindow::on_rbtn_extractAll_clicked() {
  ui->label_2->hide();
  ui->label->hide();
  ui->spinBox_fistPage->hide();
  ui->spinBox_lastPage->hide();
}

void MainWindow::on_rbtn_splitRange_clicked() {
  ui->label_2->show();
  ui->label->show();
  ui->spinBox_fistPage->show();
  ui->spinBox_lastPage->show();
}

void MainWindow::on_spinBox_fistPage_valueChanged(int arg1) {
  ui->spinBox_lastPage->setMinimum(arg1);
}

void MainWindow::on_tbtn_pdfSplit_clicked() {
  isRunnable = true;

  if (!QFile::exists(ui->ln_file2->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    isRunnable = false;
  }

  arguments.clear();
  if (isRunnable) {
    if (ui->rbtn_extractAll->isChecked()) {
      arguments << "split" << ui->ln_file2->text();
      runCommand("stapler", arguments,
                 QFileDialog::getExistingDirectory(this, tr("Select Output Folder")));

    } else if (ui->rbtn_splitRange->isChecked()) {

      QString targetFile = getSaveFileName();
      if (targetFile != "invalid") {
        arguments << "zip" << ui->ln_file2->text();
        arguments << ui->spinBox_fistPage->text() + "-" + ui->spinBox_lastPage->text();
        arguments << targetFile;
        runCommand("stapler", arguments);
      }
    }
  } else {
    qDebug() << "command not executed";
  }
}
