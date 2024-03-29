#pragma once

#include <QMessageBox>
#include <QWidget>

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
  void runAsyncFunction(std::function<void()> asyncFunction);

private slots:
  void on_tbtn_return_clicked();

  void on_btn_selectFile_clicked();

  void on_tbtn_pdfCompress_clicked();

private:
  Ui::CompressPage *ui;
};
