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
    ui->tbnt_return_2->setIcon(QIcon::fromTheme("go-previous"));

    ui->tbtn_pdfCompress->setIcon(QIcon::fromTheme("zoom-out"));
    ui->tbtn_pdfCompress->setIconSize(QSize(30,30));
    ui->tbtn_pdfCompress->setText("Compress PDF");
    ui->tbtn_pdfCompress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->tbtn_pdfSplit->setIcon(QIcon::fromTheme("edit-cut"));
    ui->tbtn_pdfSplit->setIconSize(QSize(30,30));
    ui->tbtn_pdfSplit->setText("Split PDF");
    ui->tbtn_pdfSplit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->spinBox_fistPage->setMinimum(1);
    ui->rbtn_splitRange->setChecked(true);

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

void MainWindow::on_tbtn_pdfCompress_clicked()
{

    command = "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/";

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

void MainWindow::on_tbnt_return_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_selectFile_2_clicked()
{
    ui->ln_file_2->clear();
    ui->ln_file_2->setText(
    QFileDialog::getOpenFileName(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)"));
    ui->ln_file_2->setFocus();
}

void MainWindow::on_rbtn_extractAll_clicked()
{
    ui->label_2->hide();
    ui->label->hide();
    ui->spinBox_fistPage->hide();
    ui->spinBox_lastPage->hide();
}

void MainWindow::on_rbtn_splitRange_clicked()
{
    ui->label_2->show();
    ui->label->show();
    ui->spinBox_fistPage->show();
    ui->spinBox_lastPage->show();
}

void MainWindow::on_spinBox_fistPage_valueChanged(int arg1)
{
    ui->spinBox_lastPage->setMinimum(arg1);
}

void MainWindow::on_tbtn_pdfSplit_clicked()
{
    if(ui->rbtn_extractAll->isChecked()){
        command = "gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -o  -sOutputFile=";
        command = command + QFileDialog::getExistingDirectory(this,"Select Output Folder", QDir::homePath()) + "/page%d.pdf ";
        command = command + ui->ln_file_2->text();
    }else{

    }

    qDebug() << command;
    QProcess::execute(command);
}
