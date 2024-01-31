#include "compress.hpp"
#include "ui_compress.h"

#include "api/ghostscript.hpp"
#include "api/qpdf.hpp"
#include "utils/lastDirectory.hpp"

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
  ui->ln_file1->setText(lastDirectory.getOpenFileName(this));
  ui->ln_file1->setFocus();
}

void CompressPage::on_tbtn_pdfCompress_clicked() {

  if (!QFile::exists(ui->ln_file1->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  QString targetFile = lastDirectory.getSaveFileName(this);
  if (targetFile == "invalid") {
    return;
  }

  QStringList arguments;
  arguments << "-sDEVICE=pdfwrite"
            << "-dCompatibilityLevel=1.4";

  if (ui->rbtn_screen->isChecked()) {
    arguments << "-dPDFSETTINGS=/screen";
  } else if (ui->rbtn_ebook->isChecked()) {
    arguments << "-dPDFSETTINGS=/ebook";
  } else if (ui->rbtn_printer->isChecked()) {
    arguments << "-dPDFSETTINGS=/printer";
  } else if (ui->rbtn_prepress->isChecked()) {
    arguments << "-dPDFSETTINGS=/prepress";
  } else {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a compression mode"));
    return;
  }

  arguments << "-dNOPAUSE"
            << "-dBATCH";
  arguments << "-sOutputFile=" + targetFile;
  arguments << ui->ln_file1->text();

  runCommand("gs", arguments);
}

// Remove later

void CompressPage::runCommand(QString command, QStringList arguments, QString dir) {
  QString error = "";

  if (command == "gs") {
    ghostscript.start(arguments, dir);
    error = ghostscript.getStandardError();
  } else if (command == "qpdf") {
    qpdf.start(arguments, dir);
    error = qpdf.getStandardError();
  }

  if (!error.isEmpty()) {
    QMessageBox::warning(this, tr("ERROR"), error);
  } else {
  }
}
