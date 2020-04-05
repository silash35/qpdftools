#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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

    ui->tbtn_merge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtn_merge->setIcon(QIcon::fromTheme("merge"));
    ui->tbtn_merge->setText("Merge PDF files");
    ui->tbtn_merge->setIconSize(QSize(50,50));

    ui->tbtn_rotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbtn_rotate->setIcon(QIcon::fromTheme("object-rotate-right"));
    ui->tbtn_rotate->setText("Rotate a PDF file");
    ui->tbtn_rotate->setIconSize(QSize(50,50));

    ui->tbnt_return1->setIcon(QIcon::fromTheme("go-previous"));
    ui->tbnt_return2->setIcon(QIcon::fromTheme("go-previous"));
    ui->tbnt_return3->setIcon(QIcon::fromTheme("go-previous"));

    ui->tbtn_pdfCompress->setIcon(QIcon::fromTheme("zoom-out"));
    ui->tbtn_pdfCompress->setIconSize(QSize(30,30));
    ui->tbtn_pdfCompress->setText("Compress PDF");
    ui->tbtn_pdfCompress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->tbtn_pdfSplit->setIcon(QIcon::fromTheme("edit-cut"));
    ui->tbtn_pdfSplit->setIconSize(QSize(30,30));
    ui->tbtn_pdfSplit->setText("Split PDF");
    ui->tbtn_pdfSplit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->tbtn_pdfMerge->setIcon(QIcon::fromTheme("merge"));
    ui->tbtn_pdfMerge->setIconSize(QSize(30,30));
    ui->tbtn_pdfMerge->setText("Merge PDF");
    ui->tbtn_pdfMerge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->spinBox_fistPage->setMinimum(1);
    ui->rbtn_splitRange->setChecked(true);

    ui->label_status_2->hide();
    ui->label_status->hide();

    ui->btn_Madd->setIcon(QIcon::fromTheme("list-add"));
    ui->btn_Madd->setIconSize(QSize(30,30));
    ui->btn_Madd->setToolTip("Click to add a PDF file");

    ui->btn_Mrm->setIcon(QIcon::fromTheme("list-remove"));
    ui->btn_Mrm->setIconSize(QSize(30,30));
    ui->btn_Mrm->setToolTip("Click to remove a PDF file");

    ui->btn_Mup->setIcon(QIcon::fromTheme("go-up"));
    ui->btn_Mup->setIconSize(QSize(30,30));
    ui->btn_Mup->setToolTip("Click to change the merge order");

    ui->btn_Mdown->setIcon(QIcon::fromTheme("go-down"));
    ui->btn_Mdown->setIconSize(QSize(30,30));
    ui->btn_Mdown->setToolTip("Click to change the merge order");

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Menu buttons
void MainWindow::on_tbtn_compress_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tbtn_split_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_tbtn_merge_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_tbtn_rotate_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_tbnt_return1_clicked()
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

    ui->label_status_2->setText("Processing");
    ui->label_status_2->show();

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

    command = command + "-dNOPAUSE -dQUIET -dBATCH -sOutputFile='";
    command = command + QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)") + "' '";
    command = command + ui->ln_file->text() + "'";

    qDebug() << command;
    QProcess::execute(command);

    ui->label_status_2->setText("Success!");

}

void MainWindow::on_tbnt_return2_clicked()
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

    ui->label_status_2->setText("Processing");
    ui->label_status_2->show();

    if(ui->rbtn_extractAll->isChecked()){
        command = "gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -o '"
        + QFileDialog::getExistingDirectory(this,"Select Output Folder", QDir::homePath()) + "/page%d.pdf' '"
        + ui->ln_file_2->text() + "'";
    }else if(ui->rbtn_splitRange->isChecked()){
        command = "gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -dFirstPage=" + ui->spinBox_fistPage->text()
        + " -dLastPage=" + ui->spinBox_lastPage->text()
        + " -sOutputFile='" + QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)")
        + "' '" + ui->ln_file_2->text() + "'";
    }

    qDebug() << command;
    QProcess::execute(command);

    ui->label_status_2->setText("Success!");

}

void MainWindow::on_tbnt_return3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_Madd_clicked()
{
    QString aux = QFileDialog::getOpenFileName(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)");
    if(aux[0]=='/'){
        ui->list_toMerge->addItem(aux);
    }
}

void MainWindow::on_btn_Mrm_clicked()
{
    if( (ui->list_toMerge->currentRow()>=0) and (ui->list_toMerge->count()>0)){
        delete ui->list_toMerge->takeItem(ui->list_toMerge->row(ui->list_toMerge->currentItem()));
    }
}

void MainWindow::on_btn_Mup_clicked()
{
    int currentRow = ui->list_toMerge->currentRow();

    if(currentRow > 0){
        QString aux = ui->list_toMerge->item(currentRow - 1)->text();

        ui->list_toMerge->item(currentRow - 1)->setText(ui->list_toMerge->item(currentRow)->text());
        ui->list_toMerge->item(currentRow)->setText(aux);

        ui->list_toMerge->setCurrentRow(currentRow - 1);
    }

    ui->list_toMerge->update();
}

void MainWindow::on_btn_Mdown_clicked()
{
    int currentRow = ui->list_toMerge->currentRow();

    if( (currentRow>=0) and (ui->list_toMerge->count()>0) and (ui->list_toMerge->count()!=(currentRow+1)) ){
        QString aux = ui->list_toMerge->item(currentRow + 1)->text();

        ui->list_toMerge->item(currentRow + 1)->setText(ui->list_toMerge->item(currentRow)->text());
        ui->list_toMerge->item(currentRow)->setText(aux);

        ui->list_toMerge->setCurrentRow(currentRow + 1);
    }

    ui->list_toMerge->update();
}

void MainWindow::on_tbtn_pdfMerge_clicked()
{

    if(ui->list_toMerge->count()>1){
        command = "gs -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE='"
        + QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)")
        + "' -dBATCH";
        for(int i = 0; i < ui->list_toMerge->count(); i++){
            command = command + " '" + ui->list_toMerge->item(i)->text() + "'";
        }
    }else{
        QMessageBox::warning(this,"Warning","You need to add two or more files to be able to merge them");
        command.clear();
    }

    qDebug() << command;
    QProcess::execute(command);
}
