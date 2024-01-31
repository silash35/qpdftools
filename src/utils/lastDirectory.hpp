#ifndef LAST_DIRECTORY_HPP
#define LAST_DIRECTORY_HPP

#include <QDir>
#include <QFileDialog>
#include <QObject>
#include <QWidget>

class LastDirectory : public QObject {
  Q_OBJECT

private:
  QString lastDirectory = QDir::homePath();
  bool directoryIsValid(QString dir);

public:
  QString get();
  void set(QString dir);
  void setByFile(QString file);

  QString getOpenFileName(QWidget *parent = nullptr);
  QString getSaveFileName(QWidget *parent = nullptr);
};

extern LastDirectory lastDirectory;

#endif // LAST_DIRECTORY_HPP