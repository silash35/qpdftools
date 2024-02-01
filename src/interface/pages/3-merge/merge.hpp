#pragma once

#include <QMessageBox>
#include <QWidget>

#define ICON_SIZE 30

namespace Ui {
class MergePage;
}

class MergePage : public QWidget {
  Q_OBJECT

public:
  explicit MergePage(QWidget *parent = nullptr);
  ~MergePage();

signals:
  void setPage(int newPage);
  void runAsyncFunction(std::function<void()> asyncFunction);

private slots:
  void on_tbtn_return3_clicked();

  void on_btn_Madd_clicked();

  void on_btn_Mrm_clicked();

  void on_btn_Mup_clicked();

  void on_btn_Mdown_clicked();

  void on_tbtn_pdfMerge_clicked();

private:
  Ui::MergePage *ui;
};
