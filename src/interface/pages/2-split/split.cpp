#include "split.hpp"
#include "ui_split.h"

#include "api/ghostscript.hpp"
#include "api/qpdf.hpp"
#include "utils/lastDirectory.hpp"

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
  ui->ln_file2->setText(lastDirectory.getOpenFileName());
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
  if (!QFile::exists(ui->ln_file2->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  QStringList arguments;

  if (ui->rbtn_extractAll->isChecked()) {
    QString targetFolder = QFileDialog::getExistingDirectory(this, tr("Select Output Folder"));
    if (targetFolder == "") {
      return;
    }
    // qpdf in.pdf out.pdf --split-pages
    arguments << ui->ln_file2->text();
    arguments << "out.pdf";
    arguments << "--split-pages";

    runCommand("qpdf", arguments, targetFolder);

  } else if (ui->rbtn_splitRange->isChecked()) {
    QString targetFile = lastDirectory.getSaveFileName();
    if (targetFile == "invalid") {
      return;
    }
    // qpdf in.pdf --pages . start-end -- out.pdf
    arguments << ui->ln_file2->text();
    arguments << "--pages";
    arguments << ".";
    arguments << ui->spinBox_fistPage->text() + "-" + ui->spinBox_lastPage->text();
    arguments << "--";
    arguments << targetFile;

    runCommand("qpdf", arguments);
  }
}

// Remove later

void SplitPage::runCommand(QString command, QStringList arguments, QString dir) {
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
