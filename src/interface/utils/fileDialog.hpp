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

  bool directoryIsValid(const QString &dir);

  void setLastDirectory(const QString &dir);
  void setLastDirectoryByFile(const QString &file);

public:
  FileDialog(QString filter);

  QString getOpenFileName(QWidget *parent);
  QString getSaveFileName(QWidget *parent);
  QStringList getOpenFileNames(QWidget *parent);
};

extern FileDialog fileDialog;
