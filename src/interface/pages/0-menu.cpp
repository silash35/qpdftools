#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::on_tbtn_compress_clicked(){
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tbtn_split_clicked(){
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_tbtn_merge_clicked(){
  ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_tbtn_rotate_clicked(){
  ui->stackedWidget->setCurrentIndex(4);
}