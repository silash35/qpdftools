#pragma once

#include <QMainWindow>

#include "pages/0-menu/menu.hpp"
#include "pages/1-compress/compress.hpp"
#include "pages/2-split/split.hpp"
#include "pages/3-merge/merge.hpp"
#include "pages/4-rotate/rotate.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void setPage(int newPage);

private:
  Ui::MainWindow *ui;
};
