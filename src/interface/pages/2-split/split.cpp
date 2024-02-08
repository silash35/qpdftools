#include "split.hpp"
#include "ui_split.h"

SplitPage::SplitPage(QWidget *parent) : QWidget(parent), ui(new Ui::SplitPage) {
  ui->setupUi(this);
}

SplitPage::~SplitPage() { delete ui; }

void SplitPage::on_tbtn_return_clicked() { emit setPage(0); }

void SplitPage::on_btn_selectFile_clicked() {
  ui->ln_file->clear();
  ui->ln_file->setText(fileDialog.getOpenFileName(this));
  ui->ln_file->setFocus();
}

void SplitPage::on_rbtn_extractAll_clicked() {
  ui->label_2->hide();
  ui->label->hide();
  ui->spinBox_fistPage->hide();
  ui->spinBox_lastPage->hide();
}

void SplitPage::on_rbtn_splitRange_clicked() {
  ui->label_2->show();
  ui->label->show();
  ui->spinBox_fistPage->show();
  ui->spinBox_lastPage->show();
}

void SplitPage::on_spinBox_fistPage_valueChanged(int arg1) {
  ui->spinBox_lastPage->setMinimum(arg1);
}

void SplitPage::on_tbtn_pdfSplit_clicked() {
  QString input = ui->ln_file->text();
  if (!QFile::exists(input)) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  if (ui->rbtn_extractAll->isChecked()) {
    QString outputFolder = QFileDialog::getExistingDirectory(this, tr("Select Output Folder"));
    if (outputFolder == "") {
      return;
    }

    emit runAsyncFunction([input, outputFolder] { qpdf.splitPDF(input, outputFolder); });

  } else if (ui->rbtn_splitRange->isChecked()) {
    QString output = fileDialog.getSaveFileName(this);
    if (output.isEmpty()) {
      return;
    }

    int firstPage = ui->spinBox_fistPage->value();
    int lastPage = ui->spinBox_lastPage->value();

    emit runAsyncFunction([input, output, firstPage, lastPage] {
      qpdf.splitPDF(input, output, firstPage, lastPage);
    });
  }
}
