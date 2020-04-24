#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//Main

    this->setWindowIcon(QIcon("/usr/share/pixmaps/qpdftools.svg"));
    this->setWindowTitle("Qpdf Tools");
    this->setCentralWidget(ui->stackedWidget);
    
    //Check if the system theme has the necessary icons.
    bool isThemeCompatible = (QIcon::hasThemeIcon("zoom-out") and
        QIcon::hasThemeIcon("edit-cut") and
        QIcon::hasThemeIcon("merge") and
        QIcon::hasThemeIcon("object-rotate-righ"));

    //If the theme is not compatible, the program will use breeze theme
    if(!isThemeCompatible){ 
        QIcon::setThemeName("breeze");
    }

    ui->stackedWidget->setCurrentIndex(0);
//page_menu (0)

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
//page_compress (1)

    ui->tbtn_return1->setIcon(QIcon::fromTheme("go-previous"));

    ui->tbtn_pdfCompress->setIcon(QIcon::fromTheme("zoom-out"));
    ui->tbtn_pdfCompress->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->tbtn_pdfCompress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//page_split (2)

    ui->tbtn_return2->setIcon(QIcon::fromTheme("go-previous"));

    ui->spinBox_fistPage->setMinimum(1);
    ui->rbtn_splitRange->setChecked(true);

    ui->tbtn_pdfSplit->setIcon(QIcon::fromTheme("edit-cut"));
    ui->tbtn_pdfSplit->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->tbtn_pdfSplit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//page_merge (3)

    ui->tbtn_return3->setIcon(QIcon::fromTheme("go-previous"));

    ui->btn_Madd->setIcon(QIcon::fromTheme("list-add"));
    ui->btn_Madd->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->btn_Madd->setToolTip("Click to add a PDF file");

    ui->btn_Mrm->setIcon(QIcon::fromTheme("list-remove"));
    ui->btn_Mrm->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->btn_Mrm->setToolTip("Click to remove a PDF file");

    ui->btn_Mup->setIcon(QIcon::fromTheme("go-up"));
    ui->btn_Mup->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->btn_Mup->setToolTip("Click to change the merge order");

    ui->btn_Mdown->setIcon(QIcon::fromTheme("go-down"));
    ui->btn_Mdown->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->btn_Mdown->setToolTip("Click to change the merge order");

    ui->tbtn_pdfMerge->setIcon(QIcon::fromTheme("merge"));
    ui->tbtn_pdfMerge->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->tbtn_pdfMerge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//page_rotate (4)

    ui->tbtn_return4->setIcon(QIcon::fromTheme("go-previous"));

    ui->btn_left->setIcon(QIcon::fromTheme("object-rotate-left"));
    ui->btn_left->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->btn_left->setToolTip("click to rotate the PDF 90 degrees to the left");

    ui->btn_right->setIcon(QIcon::fromTheme("object-rotate-right"));
    ui->btn_right->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->btn_right->setToolTip("click to rotate the PDF 90 degrees to the right");

    ui->btn_left->hide();
    ui->btn_right->hide();
    ui->label_pdfCover->hide();

    ui->tbtn_pdfRotate->setIcon(QIcon::fromTheme("object-rotate-right"));
    ui->tbtn_pdfRotate->setIconSize(QSize(ICONSIZE,ICONSIZE));
    ui->tbtn_pdfRotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//page_menu (0)

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
//page_compress (1)

void MainWindow::on_tbtn_return1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_selectFile1_clicked()
{
    ui->ln_file1->clear();
    ui->ln_file1->setText(
    QFileDialog::getOpenFileName(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)"));
    ui->ln_file1->setFocus();
}

void MainWindow::on_tbtn_pdfCompress_clicked()
{
    isRunnable = true;

    if(!QFile::exists(ui->ln_file1->text())){
        QMessageBox::warning(this,"Warning","You need to select a valide PDF file");
        isRunnable = false;
    }

    command = "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/";

    if(ui->rbtn_screen->isChecked()){
        command += "screen ";
    }else if(ui->rbtn_ebook->isChecked()){
        command += "ebook ";
    }else if(ui->rbtn_printer->isChecked()){
        command += "printer ";
    }else if(ui->rbtn_prepress->isChecked()){
        command += "prepress ";
    }else{
        QMessageBox::warning(this,"Warning","You need to select a compression mode");
        isRunnable = false;
    }

    if(isRunnable){

        command += "-dNOPAUSE -dBATCH -sOutputFile='";
        command += QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)") + "' '";
        command += ui->ln_file1->text() + "'";

        runCommand(command);
    }else{
        command.clear();
        qDebug() << "command not executed";
    }

}
//page_split (2)

void MainWindow::on_tbtn_return2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_selectFile2_clicked()
{
    ui->ln_file2->clear();
    ui->ln_file2->setText(
    QFileDialog::getOpenFileName(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)"));
    ui->ln_file2->setFocus();
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
    isRunnable = true;

    if(!QFile::exists(ui->ln_file2->text())){
        QMessageBox::warning(this,"Warning","You need to select a valide PDF file");
        isRunnable = false;
    }

    if(isRunnable){
        if(ui->rbtn_extractAll->isChecked()){
            command = "cd '"
            + QFileDialog::getExistingDirectory(this,"Select Output Folder", QDir::homePath()) + "' && "
            + "stapler split " + "'" + ui->ln_file2->text() + "'";
        }else if(ui->rbtn_splitRange->isChecked()){
            command = "stapler zip '"
            + ui->ln_file2->text() + "' "
            + ui->spinBox_fistPage->text() + "-" + ui->spinBox_lastPage->text() +
            + " '" + QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)") + "'";
        }
        runCommand(command);
    }else{
        command.clear();
        qDebug() << "command not executed";
    }
}
//page_merge (3)

void MainWindow::on_tbtn_return3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_Madd_clicked()
{
    QStringList aux = QFileDialog::getOpenFileNames(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)");

    for(int i=0; i < aux.count(); i++){
        qDebug() << i << ": " << aux[i];
        if(QFile::exists(aux[i])){
            ui->list_toMerge->addItem(aux[i]);
        }
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
        command = "stapler sel ";
        for(int i = 0; i < ui->list_toMerge->count(); i++){
            command = command + "'" + ui->list_toMerge->item(i)->text() + "' ";
        }
        command = command + "'"
        + QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)") + "'";
    }else{
        QMessageBox::warning(this,"Warning","You need to add two or more files to be able to merge them");
        command.clear();
    }

    runCommand(command);
}
//page_rotate (4)

void MainWindow::on_tbtn_return4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_selectFile4_clicked()
{
    ui->ln_file4->clear();
    ui->ln_file4->setText(
    QFileDialog::getOpenFileName(this,"Select the PDF file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)"));
    ui->ln_file4->setFocus();
}

void MainWindow::on_ln_file4_textChanged(const QString &arg1)
{
    rotate = 0;

    if(QFile::exists(arg1)){
        ui->btn_left->show();
        ui->btn_right->show();
        ui->label_pdfCover->show();

        command = "gs -q -o '";
        command += PDFCOVERPATH;
        command += "' -sDEVICE=pngalpha -dLastPage=1 -dUseCropBox '" + arg1 + "'";
        runCommand(command);

        QPixmap pdfCover(PDFCOVERPATH);
        ui->label_pdfCover->setPixmap(pdfCover.scaled(300,300,Qt::KeepAspectRatio));
    }else{
        ui->btn_left->hide();
        ui->btn_right->hide();
        ui->label_pdfCover->hide();
        command.clear();
    }

}

void MainWindow::on_btn_left_clicked()
{
    if(rotate <= 0){
        rotate = 360;
    }

    rotate -= 90;
    QTransform rote;
    rote = rote.rotate(rotate);

    QPixmap pdfCover(PDFCOVERPATH);
    pdfCover = QPixmap(pdfCover.transformed(rote));
    ui->label_pdfCover->setPixmap(pdfCover.scaled(300,300,Qt::KeepAspectRatio));
}

void MainWindow::on_btn_right_clicked()
{
    if(rotate >= 360){
        rotate = 0;
    }

    rotate += 90;
    QTransform rote;
    rote = rote.rotate(rotate);

    QPixmap pdfCover(PDFCOVERPATH);
    pdfCover = QPixmap(pdfCover.transformed(rote));
    ui->label_pdfCover->setPixmap(pdfCover.scaled(300,300,Qt::KeepAspectRatio));
}

void MainWindow::on_tbtn_pdfRotate_clicked()
{

    isRunnable = true;

    if(!QFile::exists(ui->ln_file4->text())){
        QMessageBox::warning(this,"Warning","You need to select a valide PDF file");
        isRunnable = false;
    }

    command = "stapler sel A='" + ui->ln_file4->text() + "' A1-end";

    if( (rotate==0) or (rotate==360) ){
        command += " '";
    }else if(rotate == 90){
        command += "R '";
    }else if(rotate == 180){
        command += "D '";
    }else if(rotate == 270){
        command += "L '";
    }

    if(isRunnable){
        command += QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),"PDF - Portable Document Format (*.pdf)") + "'";

        runCommand(command);
    }else{
        qDebug() << "command not executed";
    }
    command.clear();
}
//Other functions

void MainWindow::runCommand(QString command){

    qDebug() << "executing command: " << command << endl;

    ui->statusBar->showMessage("Processing...");

    QProcess process;
    process.start("sh");

    process.write(qPrintable(command));
    process.closeWriteChannel();
    process.waitForFinished();

    qDebug() << process.readAllStandardOutput() << endl;
    QString error = process.readAllStandardError();
    if(!error.isEmpty()){
        QMessageBox::warning(this,"ERROR",error);
        ui->statusBar->showMessage("Failed",10000);
    }else{
        ui->statusBar->showMessage("Success!",10000);
    }
    process.close();

    qDebug() << "finished to execute: " << command << endl;

}
