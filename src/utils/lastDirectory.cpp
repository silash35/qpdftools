#include "lastDirectory.hpp"

bool LastDirectory::directoryIsValid(QString dir) {
  QDir qDir(dir);
  return qDir.exists();
}

QString LastDirectory::get() {
  if (!directoryIsValid(lastDirectory)) {
    lastDirectory = QDir::homePath();
  }
  return lastDirectory;
}

void LastDirectory::set(QString dir) {
  if (directoryIsValid(dir)) {
    lastDirectory = dir;
  }
}

void LastDirectory::setByFile(QString file) { set(QFileInfo(file).absoluteDir().absolutePath()); }

LastDirectory lastDirectory;