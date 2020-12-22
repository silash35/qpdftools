#ifndef LASTDIRECTORY_HPP
#define LASTDIRECTORY_HPP

#include <QDir>

class LastDirectory {
private:
  QString lastDirectory = QDir::homePath();

  bool directoryIsValid(QString dir) {
    QDir qDir(dir);
    return qDir.exists();
  }

public:
  QString get() {
    if (!directoryIsValid(lastDirectory)) {
      lastDirectory = QDir::homePath();
    }
    return lastDirectory;
  }

  void set(QString dir) {
    if (directoryIsValid(dir)) {
      lastDirectory = dir;
    }
  }

  void setByFile(QString file) { set(QFileInfo(file).absoluteDir().absolutePath()); }
};

LastDirectory lastDirectory;

#endif // LASTDIRECTORY_HPP