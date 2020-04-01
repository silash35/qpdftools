#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon::fromTheme("application-pdf"));
    this->setWindowTitle("Qpdf Tools");

    this->setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->setCurrentIndex(0);

    ui->tbtn_compress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtn_compress->setIcon(QIcon::fromTheme("zoom-out"));
    ui->tbtn_compress->setText("Compress a PDF file");
    ui->tbtn_compress->setIconSize(QSize(50,50));

    ui->tbtn_split->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtn_split->setIcon(QIcon::fromTheme("edit-cut"));
    ui->tbtn_split->setText("Split a PDF file");
    ui->tbtn_split->setIconSize(QSize(50,50));

    ui->tbnt_return->setIcon(QIcon::fromTheme("go-previous"));

    ui->tbtn_compressPdf->setIcon(QIcon::fromTheme("zoom-out"));
    ui->tbtn_compressPdf->setIconSize(QSize(30,30));
    ui->tbtn_compressPdf->setText("Start compression");
    ui->tbtn_compressPdf->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

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
    ui->ln_file->clear();
    ui->ln_file->setText(
    QFileDialog::getOpenFileName(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)"));
    ui->ln_file->setFocus();
}

void MainWindow::on_tbtn_compressPdf_clicked()
{

    QString command = "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/";
    if(ui->rbtn_screen->isChecked()){
        command = command + "screen ";
    }else if(ui->rbtn_ebook->isChecked()){
        command = command + "ebook ";
    }else if(ui->rbtn_printer->isChecked()){
        command = command + "printer ";
    }else if(ui->rbtn_prepress->isChecked()){
        command = command + "prepress ";
    }

    command = command + "-dNOPAUSE -dQUIET -dBATCH -sOutputFile=";
    command = command + QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)") + " ";
    command = command + ui->ln_file->text();

    qDebug() << command;
    QProcess::execute(command);
}
