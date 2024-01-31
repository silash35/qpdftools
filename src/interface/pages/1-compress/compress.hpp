#pragma once

#include <QMessageBox>
#include <QWidget>

#define ICON_SIZE 30

namespace Ui {
class CompressPage;
}

class CompressPage : public QWidget {
  Q_OBJECT

public:
  explicit CompressPage(QWidget *parent = nullptr);
  ~CompressPage();

signals:
  void setPage(int newPage);

private slots:
  void on_tbtn_return1_clicked();

  void on_btn_selectFile1_clicked();

  void on_tbtn_pdfCompress_clicked();

private:
  Ui::CompressPage *ui;

  void runCommand(QString command, QStringList arguments, QString dir = "default");
};
