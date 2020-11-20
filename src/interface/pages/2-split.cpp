#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::on_tbtn_return2_clicked(){
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_selectFile2_clicked(){
  ui->ln_file2->clear();
  ui->ln_file2->setText(getOpenFileName());
  ui->ln_file2->setFocus();
}

void MainWindow::on_rbtn_extractAll_clicked(){
  ui->label_2->hide();
  ui->label->hide();
  ui->spinBox_fistPage->hide();
  ui->spinBox_lastPage->hide();
}

void MainWindow::on_rbtn_splitRange_clicked(){
  ui->label_2->show();
  ui->label->show();
  ui->spinBox_fistPage->show();
  ui->spinBox_lastPage->show();
}

void MainWindow::on_spinBox_fistPage_valueChanged(int arg1){
  ui->spinBox_lastPage->setMinimum(arg1);
}

void MainWindow::on_tbtn_pdfSplit_clicked(){
  isRunnable = true;

  if(!QFile::exists(ui->ln_file2->text())){
    QMessageBox::warning(this,tr("Warning"),tr("You need to select a valide PDF file"));
    isRunnable = false;
  }

  if(isRunnable){
    if(ui->rbtn_extractAll->isChecked()){
      command = "cd '"
      + QFileDialog::getExistingDirectory(this,tr("Select Output Folder"), QDir::homePath()) + "' && "
      + "stapler split " + "'" + ui->ln_file2->text() + "'";
    }else if(ui->rbtn_splitRange->isChecked()){
      command = "stapler zip '"
      + ui->ln_file2->text() + "' "
      + ui->spinBox_fistPage->text() + "-" + ui->spinBox_lastPage->text() +
      + " '" + getSaveFileName() + "'";
    }
    runCommand(command);
  }else{
    command.clear();
    qDebug() << "command not executed";
  }
}