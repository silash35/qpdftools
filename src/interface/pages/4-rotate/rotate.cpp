#include "rotate.hpp"
#include "ui_rotate.h"

RotatePage::RotatePage(QWidget *parent) : QWidget(parent), ui(new Ui::RotatePage) {
  ui->setupUi(this);

  ui->btn_left->hide();
  ui->btn_right->hide();
  ui->label_pdfCover->hide();
}

RotatePage::~RotatePage() { delete ui; }

void RotatePage::on_tbtn_return_clicked() { emit setPage(0); }

void RotatePage::on_btn_selectFile4_clicked() {
  ui->ln_file->clear();
  ui->ln_file->setText(fileDialog.getOpenFileName(this));
  ui->ln_file->setFocus();
}

void RotatePage::on_ln_file_textChanged(const QString &pdfPath) {
  rotate = 0;

  if (QFile::exists(pdfPath)) {
    ui->btn_left->show();
    ui->btn_right->show();
    ui->label_pdfCover->show();

    QtConcurrent::run([this, pdfPath] {
      ghostscript.generateThumbnail(pdfPath, pdfCoverPath);
      QPixmap pdfCover(pdfCoverPath);
      ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
    }).onFailed(qApp, [this]() {
      QMessageBox::warning(this, tr("ERROR"), tr("Failed to generate thumbnail"));
    });

  } else {
    ui->btn_left->hide();
    ui->btn_right->hide();
    ui->label_pdfCover->hide();
  }
}

void RotatePage::on_btn_left_clicked() {
  if (rotate <= 0) {
    rotate = 360;
  }

  rotate -= 90;
  QTransform rote;
  rote = rote.rotate(rotate);

  QPixmap pdfCover(pdfCoverPath);
  pdfCover = QPixmap(pdfCover.transformed(rote));
  ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
}

void RotatePage::on_btn_right_clicked() {
  if (rotate >= 360) {
    rotate = 0;
  }

  rotate += 90;
  QTransform rote;
  rote = rote.rotate(rotate);

  QPixmap pdfCover(pdfCoverPath);
  pdfCover = QPixmap(pdfCover.transformed(rote));
  ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
}

void RotatePage::on_tbtn_pdfRotate_clicked() {
  if (!QFile::exists(ui->ln_file->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  QString output = fileDialog.getSaveFileName(this);
  if (output == "invalid") {
    return;
  }
  QString input = ui->ln_file->text();
  int angle = rotate;

  emit runAsyncFunction([input, output, angle] { qpdf.rotatePDF(input, output, angle); });
}
