#include "merge.hpp"
#include "ui_merge.h"

#include "api/ghostscript.hpp"
#include "api/qpdf.hpp"
#include "interface/utils/fileDialog.hpp"

MergePage::MergePage(QWidget *parent) : QWidget(parent), ui(new Ui::MergePage) {
  ui->setupUi(this);

  ui->tbtn_return3->setIcon(QIcon::fromTheme("go-previous"));

  ui->btn_Madd->setIcon(QIcon::fromTheme("list-add"));
  ui->btn_Madd->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->btn_Madd->setToolTip(tr("Click to add a PDF file"));

  ui->btn_Mrm->setIcon(QIcon::fromTheme("list-remove"));
  ui->btn_Mrm->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->btn_Mrm->setToolTip(tr("Click to remove a PDF file"));

  ui->btn_Mup->setIcon(QIcon::fromTheme("go-up"));
  ui->btn_Mup->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->btn_Mup->setToolTip(tr("Click to change the merge order"));

  ui->btn_Mdown->setIcon(QIcon::fromTheme("go-down"));
  ui->btn_Mdown->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->btn_Mdown->setToolTip(tr("Click to change the merge order"));

  ui->tbtn_pdfMerge->setIcon(QIcon::fromTheme("edit-group"));
  ui->tbtn_pdfMerge->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->tbtn_pdfMerge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MergePage::~MergePage() { delete ui; }

void MergePage::on_tbtn_return3_clicked() { emit setPage(0); }

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