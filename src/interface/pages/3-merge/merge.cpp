#include "merge.hpp"
#include "ui_merge.h"

MergePage::MergePage(QWidget *parent) : QWidget(parent), ui(new Ui::MergePage) {
  ui->setupUi(this);
}

MergePage::~MergePage() { delete ui; }

void MergePage::on_tbtn_return_clicked() { emit setPage(0); }

void MergePage::on_btn_Madd_clicked() {
  QStringList files = fileDialog.getOpenFileNames(this);
  ui->list_toMerge->addItems(files);
}

void MergePage::on_btn_Mrm_clicked() {
  if ((ui->list_toMerge->currentRow() >= 0) and (ui->list_toMerge->count() > 0)) {
    delete ui->list_toMerge->takeItem(ui->list_toMerge->row(ui->list_toMerge->currentItem()));
  }
}

void MergePage::on_btn_Mup_clicked() {
  int currentRow = ui->list_toMerge->currentRow();

  if (currentRow > 0) {
    QString aux = ui->list_toMerge->item(currentRow - 1)->text();

    ui->list_toMerge->item(currentRow - 1)->setText(ui->list_toMerge->item(currentRow)->text());
    ui->list_toMerge->item(currentRow)->setText(aux);

    ui->list_toMerge->setCurrentRow(currentRow - 1);
  }

  ui->list_toMerge->update();
}

void MergePage::on_btn_Mdown_clicked() {
  int currentRow = ui->list_toMerge->currentRow();

  if ((currentRow >= 0) and (ui->list_toMerge->count() > 0) and
      (ui->list_toMerge->count() != (currentRow + 1))) {
    QString aux = ui->list_toMerge->item(currentRow + 1)->text();

    ui->list_toMerge->item(currentRow + 1)->setText(ui->list_toMerge->item(currentRow)->text());
    ui->list_toMerge->item(currentRow)->setText(aux);

    ui->list_toMerge->setCurrentRow(currentRow + 1);
  }

  ui->list_toMerge->update();
}

void MergePage::on_tbtn_pdfMerge_clicked() {
  if (ui->list_toMerge->count() <= 1) {
    QMessageBox::warning(this, tr("Warning"),
                         tr("You need to add two or more files to be able to merge them"));
    return;
  }

  QString output = fileDialog.getSaveFileName(this);
  if (output == "invalid") {
    return;
  }

  QStringList inputs;
  for (int i = 0; i < ui->list_toMerge->count(); ++i)
    inputs << ui->list_toMerge->item(i)->text();

  emit runAsyncFunction([inputs, output] { qpdf.mergePDF(inputs, output); });
}