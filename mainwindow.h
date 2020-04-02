#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tbtn_compress_clicked();

    void on_tbtn_split_clicked();

    void on_tbnt_return1_clicked();

    void on_btn_selectFile_clicked();

    void on_tbtn_pdfCompress_clicked();

    void on_tbnt_return2_clicked();

    void on_btn_selectFile_2_clicked();

    void on_rbtn_extractAll_clicked();

    void on_rbtn_splitRange_clicked();

    void on_spinBox_fistPage_valueChanged(int arg1);

    void on_tbtn_pdfSplit_clicked();

    void on_tbtn_merge_clicked();

    void on_tbtn_rotate_clicked();

    void on_tbnt_return3_clicked();

    void on_btn_Madd_clicked();

    void on_btn_Mrm_clicked();

    void on_btn_Mup_clicked();

    void on_btn_Mdown_clicked();

private:
    Ui::MainWindow *ui;

    QString command = "";

};
#endif // MAINWINDOW_H
