#include "split.hpp"
#include "ui_split.h"

#include "api/ghostscript.hpp"
#include "api/qpdf.hpp"
#include "interface/utils/fileDialog.hpp"

SplitPage::SplitPage(QWidget *parent) : QWidget(parent), ui(new Ui::SplitPage) {
  ui->setupUi(this);

  ui->tbtn_return2->setIcon(QIcon::fromTheme("go-previous"));

  ui->spinBox_fistPage->setMinimum(1);
  ui->rbtn_splitRange->setChecked(true);

  ui->tbtn_pdfSplit->setIcon(QIcon::fromTheme("edit-cut"));
  ui->tbtn_pdfSplit->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->tbtn_pdfSplit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

SplitPage::~SplitPage() { delete ui; }

void SplitPage::on_tbtn_return2_clicked() { emit setPage(0); }

void SplitPage::on_btn_selectFile2_clicked() {
  ui->ln_file2->clear();
  ui->ln_file2->setText(fileDialog.getOpenFileName(this));
  ui->ln_file2->setFocus();
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
  QString input = ui->ln_file2->text();
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
    if (output == "invalid") {
      return;
    }

    int firstPage = ui->spinBox_fistPage->value();
    int lastPage = ui->spinBox_lastPage->value();

    emit runAsyncFunction([input, output, firstPage, lastPage] {
      qpdf.splitPDF(input, output, firstPage, lastPage);
    });
  }
}
