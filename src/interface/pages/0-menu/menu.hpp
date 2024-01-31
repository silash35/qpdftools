#ifndef MENU_H
#define MENU_H

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
  void on_tbtn_compress_clicked();

  void on_tbtn_split_clicked();

  void on_tbtn_merge_clicked();

  void on_tbtn_rotate_clicked();

private:
  Ui::MenuPage *ui;
};

#endif // MENU_H
