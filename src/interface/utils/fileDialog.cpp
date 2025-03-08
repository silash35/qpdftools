#include "fileDialog.hpp"

FileDialog::FileDialog(QString filter, QString extension) : filter(filter), extension(extension) {}

// Private Methods

bool FileDialog::directoryIsValid(const QString &dir) {
  QDir qDir(dir);
  return qDir.exists();
}

void FileDialog::setLastDirectory(const QString &dir) {
  if (directoryIsValid(dir)) {
    lastDirectory = dir;
  }
}

void FileDialog::setLastDirectoryByFile(const QString &file) {
  setLastDirectory(QFileInfo(file).absoluteDir().absolutePath());
}

// Public Methods

QString FileDialog::getOpenFileName(QWidget *parent) {
  QString file =
    QFileDialog::getOpenFileName(parent, tr("Select the PDF file"), lastDirectory, filter);

  if (!file.isEmpty()) {
    setLastDirectoryByFile(file);
  }
  return file;
}

QString FileDialog::getSaveFileName(QWidget *parent) {
  QString file = QFileDialog::getSaveFileName(parent, tr("Save file"), lastDirectory, filter);

  if (!file.isEmpty()) {
    if (!file.endsWith(extension)) {
      file.append(extension);
    }
    setLastDirectoryByFile(file);
  }

  return file;
}

QStringList FileDialog::getOpenFileNames(QWidget *parent) {
  QStringList files =
    QFileDialog::getOpenFileNames(parent, tr("Select the PDF files"), lastDirectory, filter);
  QStringList validFiles;

  for (int i = 0; i < files.count(); ++i) {
    qInfo() << i << ": " << files[i];
    if (QFile::exists(files[i])) {
      validFiles.push_back(files[i]);
    }
  }

  if (!validFiles.isEmpty()) {
    setLastDirectoryByFile(validFiles.last());
  }

  return validFiles;
}

// Initialize only allowing PDF files
FileDialog fileDialog("PDF - Portable Document Format (*.pdf  *.PDF)", ".pdf");