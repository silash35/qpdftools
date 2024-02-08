#include "compress.hpp"
#include "ui_compress.h"

#include "api/ghostscript.hpp"
#include "interface/utils/fileDialog.hpp"

CompressPage::CompressPage(QWidget *parent) : QWidget(parent), ui(new Ui::CompressPage) {
  ui->setupUi(this);
}

CompressPage::~CompressPage() { delete ui; }

void CompressPage::on_tbtn_return_clicked() { emit setPage(0); }

void CompressPage::on_btn_selectFile_clicked() {
  ui->ln_file->clear();
  ui->ln_file->setText(fileDialog.getOpenFileName(this));
  ui->ln_file->setFocus();
}

void CompressPage::on_tbtn_pdfCompress_clicked() {
  QString input = ui->ln_file->text();
  if (!QFile::exists(input)) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  QString output = fileDialog.getSaveFileName(this);
  if (output.isEmpty()) {
    return;
  }

  Ghostscript::CompressionMode mode;

  if (ui->rbtn_screen->isChecked()) {
    mode = Ghostscript::screen;
  } else if (ui->rbtn_ebook->isChecked()) {
    mode = Ghostscript::ebook;
  } else if (ui->rbtn_printer->isChecked()) {
    mode = Ghostscript::printer;
  } else if (ui->rbtn_prepress->isChecked()) {
    mode = Ghostscript::prepress;
  } else {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a compression mode"));
    return;
  }

  emit runAsyncFunction([input, output, mode] { ghostscript.compressPDF(input, output, mode); });
}
