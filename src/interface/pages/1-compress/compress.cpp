#include "compress.hpp"
#include "ui_compress.h"

#include "api/ghostscript.hpp"
#include "interface/utils/fileDialog.hpp"

CompressPage::CompressPage(QWidget *parent) : QWidget(parent), ui(new Ui::CompressPage) {
  ui->setupUi(this);

  ui->tbtn_return1->setIcon(QIcon::fromTheme("go-previous"));
  ui->tbtn_pdfCompress->setIcon(QIcon::fromTheme("zoom-out"));
  ui->tbtn_pdfCompress->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->tbtn_pdfCompress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

CompressPage::~CompressPage() { delete ui; }

void CompressPage::on_tbtn_return1_clicked() { emit setPage(0); }

void CompressPage::on_btn_selectFile1_clicked() {
  ui->ln_file1->clear();
  ui->ln_file1->setText(fileDialog.getOpenFileName(this));
  ui->ln_file1->setFocus();
}

void CompressPage::on_tbtn_pdfCompress_clicked() {

  if (!QFile::exists(ui->ln_file1->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  QString targetFile = fileDialog.getSaveFileName(this);
  if (targetFile == "invalid") {
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

  emit runAsyncFunction([this, targetFile, mode]() {
    ghostscript.compressPDF(ui->ln_file1->text(), targetFile, mode);
  });
}
