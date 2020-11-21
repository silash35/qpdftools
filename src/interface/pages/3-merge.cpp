#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::configMerge(){
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
}

void MainWindow::on_tbtn_return3_clicked(){
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_Madd_clicked(){
  QStringList aux = QFileDialog::getOpenFileNames(this,tr("Select the PDF file"),QDir::homePath(),"PDF - Portable Document Format (*.pdf)");

  for(int i=0; i < aux.count(); ++i){
    qDebug() << i << ": " << aux[i];
    if(QFile::exists(aux[i])){
      ui->list_toMerge->addItem(aux[i]);
    }
  }
}

void MainWindow::on_btn_Mrm_clicked(){
  if( (ui->list_toMerge->currentRow()>=0) and (ui->list_toMerge->count()>0)){
    delete ui->list_toMerge->takeItem(ui->list_toMerge->row(ui->list_toMerge->currentItem()));
  }
}

void MainWindow::on_btn_Mup_clicked(){
  int currentRow = ui->list_toMerge->currentRow();

  if(currentRow > 0){
    QString aux = ui->list_toMerge->item(currentRow - 1)->text();

    ui->list_toMerge->item(currentRow - 1)->setText(ui->list_toMerge->item(currentRow)->text());
    ui->list_toMerge->item(currentRow)->setText(aux);

    ui->list_toMerge->setCurrentRow(currentRow - 1);
  }

  ui->list_toMerge->update();
}

void MainWindow::on_btn_Mdown_clicked(){
  int currentRow = ui->list_toMerge->currentRow();

  if( (currentRow>=0) and (ui->list_toMerge->count()>0) and (ui->list_toMerge->count()!=(currentRow+1)) ){
    QString aux = ui->list_toMerge->item(currentRow + 1)->text();

    ui->list_toMerge->item(currentRow + 1)->setText(ui->list_toMerge->item(currentRow)->text());
    ui->list_toMerge->item(currentRow)->setText(aux);

    ui->list_toMerge->setCurrentRow(currentRow + 1);
  }

  ui->list_toMerge->update();
}

void MainWindow::on_tbtn_pdfMerge_clicked(){
  if(ui->list_toMerge->count()>1){
    command << "stapler sel ";
    for(int i = 0; i < ui->list_toMerge->count(); ++i){
      command << "'" + ui->list_toMerge->item(i)->text() + "' ";
    }
    command << "'" + getSaveFileName() + "'";
  }else{
    QMessageBox::warning(this,tr("Warning"),tr("You need to add two or more files to be able to merge them"));
    command.clear();
  }

  runCommand("stapler", command);
}
