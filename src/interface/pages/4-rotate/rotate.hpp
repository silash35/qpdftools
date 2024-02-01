#pragma once

#include <QDir>
#include <QMessageBox>
#include <QWidget>
#include <QtConcurrent>

#define ICON_SIZE 30

namespace Ui {
class RotatePage;
}

class RotatePage : public QWidget {
  Q_OBJECT

public:
  explicit RotatePage(QWidget *parent = nullptr);
  ~RotatePage();

signals:
  void setPage(int newPage);
  void runAsyncFunction(std::function<void()> asyncFunction);

private slots:
  void on_tbtn_return4_clicked();

  void on_btn_selectFile4_clicked();

  void on_ln_file4_textChanged(const QString &arg1);

  void on_btn_left_clicked();

  void on_btn_right_clicked();

  void on_tbtn_pdfRotate_clicked();

private:
  Ui::RotatePage *ui;
  int rotate{0};

  QString pdfCoverPath = QDir::tempPath() + "/pdfCover.jpeg";
};
