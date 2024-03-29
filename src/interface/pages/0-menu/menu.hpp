#pragma once

#include <QWidget>

namespace Ui {
class MenuPage;
}

class MenuPage : public QWidget {
  Q_OBJECT

public:
  explicit MenuPage(QWidget *parent = nullptr);
  ~MenuPage();

signals:
  void setPage(int newPage);

private slots:
  void on_btn_compress_clicked();

  void on_btn_split_clicked();

  void on_btn_merge_clicked();

  void on_btn_rotate_clicked();

private:
  Ui::MenuPage *ui;
};
