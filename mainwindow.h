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

    void on_tbnt_return_clicked();

    void on_btn_selectFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
