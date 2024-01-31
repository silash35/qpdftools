#pragma once

#include "../utils/lastDirectory.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>

#define ICON_SIZE 30
#define MENU_ICON_SIZE 50

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

private slots:
  // page_rotate (4)
  void on_tbtn_return4_clicked();

  void on_btn_selectFile4_clicked();

  void on_ln_file4_textChanged(const QString &arg1);

  void on_btn_left_clicked();

  void on_btn_right_clicked();

  void on_tbtn_pdfRotate_clicked();

private:
  Ui::MainWindow *ui;

  QStringList arguments; // Stores the command to be executed
  int rotate{0};         // Stores in degrees how much the pdf will be rotated in rotation mode

  void configRotate();

  void runCommand(QString command, QStringList arguments, QString dir = "default");
  QString getOpenFileName();
  QString getSaveFileName();
};
