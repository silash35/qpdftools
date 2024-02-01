#pragma once

#include "interface/utils/globals.hpp"
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class SplitPage;
}

class SplitPage : public QWidget {
  Q_OBJECT

public:
  explicit SplitPage(QWidget *parent = nullptr);
  ~SplitPage();

signals:
  void setPage(int newPage);
  void runAsyncFunction(std::function<void()> asyncFunction);

private slots:
  void on_tbtn_return2_clicked();

  void on_btn_selectFile2_clicked();

  void on_rbtn_extractAll_clicked();

  void on_rbtn_splitRange_clicked();

  void on_spinBox_fistPage_valueChanged(int arg1);

  void on_tbtn_pdfSplit_clicked();

private:
  Ui::SplitPage *ui;
};
