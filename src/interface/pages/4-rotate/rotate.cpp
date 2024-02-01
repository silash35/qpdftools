#include "rotate.hpp"
#include "ui_rotate.h"

#include "api/ghostscript.hpp"
#include "api/qpdf.hpp"
#include "interface/utils/fileDialog.hpp"

RotatePage::RotatePage(QWidget *parent) : QWidget(parent), ui(new Ui::RotatePage) {
  ui->setupUi(this);

  ui->tbtn_return4->setIcon(QIcon::fromTheme("go-previous"));

  ui->btn_left->setIcon(QIcon::fromTheme("object-rotate-left"));
  ui->btn_left->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->btn_left->setToolTip(tr("click to rotate the PDF 90 degrees to the left"));

  ui->btn_right->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->btn_right->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->btn_right->setToolTip(tr("click to rotate the PDF 90 degrees to the right"));

  ui->btn_left->hide();
  ui->btn_right->hide();
  ui->label_pdfCover->hide();

  ui->tbtn_pdfRotate->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->tbtn_pdfRotate->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  ui->tbtn_pdfRotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

RotatePage::~RotatePage() { delete ui; }

void RotatePage::on_tbtn_return4_clicked() { emit setPage(0); }

void RotatePage::on_btn_selectFile4_clicked() {
  ui->ln_file4->clear();
  ui->ln_file4->setText(fileDialog.getOpenFileName());
  ui->ln_file4->setFocus();
}

void RotatePage::on_ln_file4_textChanged(const QString &pdfPath) {
  rotate = 0;
  QStringList arguments;

  if (QFile::exists(pdfPath)) {
    ui->btn_left->show();
    ui->btn_right->show();
    ui->label_pdfCover->show();

    emit runAsyncFunction([this, pdfPath]() {
      ghostscript.generateThumbnail(pdfPath, pdfCoverPath);
      QPixmap pdfCover(pdfCoverPath);
      ui->label_pdfCover->setPixmap(pdfCover.scaled(300, 300, Qt::KeepAspectRatio));
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

  if (!QFile::exists(ui->ln_file4->text())) {
    QMessageBox::warning(this, tr("Warning"), tr("You need to select a valide PDF file"));
    return;
  }

  QString output = fileDialog.getSaveFileName();
  if (output == "invalid") {
    return;
  }
  QString input = ui->ln_file4->text();
  int angle = rotate;

  emit runAsyncFunction([input, output, angle]() { qpdf.rotatePDF(input, output, angle); });
}
