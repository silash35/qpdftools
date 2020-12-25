#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../utils/lastDirectory.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>

#define ICONSIZE 30
#define MENUICONSIZE 50

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  // page_menu (0)
  void on_tbtn_compress_clicked();

  void on_tbtn_split_clicked();

  void on_tbtn_merge_clicked();

  void on_tbtn_rotate_clicked();

  // page_compress (1)
  void on_tbtn_return1_clicked();

  void on_btn_selectFile1_clicked();

  void on_tbtn_pdfCompress_clicked();

  // page_split (2)
  void on_tbtn_return2_clicked();

  void on_btn_selectFile2_clicked();

  void on_rbtn_extractAll_clicked();

  void on_rbtn_splitRange_clicked();

  void on_spinBox_fistPage_valueChanged(int arg1);

  void on_tbtn_pdfSplit_clicked();

  // page_merge (3)
  void on_tbtn_return3_clicked();

  void on_btn_Madd_clicked();

  void on_btn_Mrm_clicked();

  void on_btn_Mup_clicked();

  void on_btn_Mdown_clicked();

  void on_tbtn_pdfMerge_clicked();

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

  void configMenu();
  void configCompress();
  void configSplit();
  void configMerge();
  void configRotate();

  void runCommand(QString command, QStringList arguments, QString dir = "default");
  QString getOpenFileName();
  QString getSaveFileName();
};
#endif // MAINWINDOW_H
