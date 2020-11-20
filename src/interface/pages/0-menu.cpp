#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::configMenu(){
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
}

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