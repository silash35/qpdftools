#pragma once

#include <QDir>
#include <QFileDialog>
#include <QObject>
#include <QWidget>

class FileDialog : public QObject {
  Q_OBJECT

private:
  QString filter; // What type of files are allowed
  // Keep track of the last directory opened,
  // so the user does not have to select the same directory every time
  QString lastDirectory = QDir::homePath();

  bool directoryIsValid(QString dir);

  void setLastDirectory(QString dir);
  void setLastDirectoryByFile(QString file);

public:
  FileDialog(QString filter);

  QString getOpenFileName(QWidget *parent = nullptr);
  QString getSaveFileName(QWidget *parent = nullptr);
  QStringList getOpenFileNames(QWidget *parent = nullptr);
};

extern FileDialog fileDialog;
