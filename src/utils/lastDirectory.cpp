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

QString LastDirectory::getOpenFileName(QWidget *parent) {
  QString file = QFileDialog::getOpenFileName(parent, tr("Select the PDF file"), get(),
                                              "PDF - Portable Document Format (*.pdf  *.PDF)");

  if (!file.isEmpty()) {
    setByFile(file);
  }
  return file;
}

QString LastDirectory::getSaveFileName(QWidget *parent) {
  QString file = QFileDialog::getSaveFileName(parent, tr("Save file"), get(),
                                              "PDF - Portable Document Format (*.pdf)");
  if (file.isEmpty()) {
    file = "invalid";
  } else {
    setByFile(file);
  }

  return file;
}

LastDirectory lastDirectory;