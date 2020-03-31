#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    ui->tbtn_compress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtn_compress->setIcon(QIcon::fromTheme("application-x-tarz"));
    ui->tbtn_compress->setText("Compress a PDF file");
    ui->tbtn_compress->setIconSize(QSize(50,50));

    ui->tbtn_split->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtn_split->setIcon(QIcon::fromTheme("edit-cut"));
    ui->tbtn_split->setText("Split a PDF file");
    ui->tbtn_split->setIconSize(QSize(50,50));

    ui->tbnt_return->setIcon(QIcon::fromTheme("go-previous"));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tbtn_compress_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tbtn_split_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_tbnt_return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_selectFile_clicked()
{

}
