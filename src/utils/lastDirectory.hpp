#ifndef LASTDIRECTORY_HPP
#define LASTDIRECTORY_HPP

#include <QDir>

class LastDirectory {
private:
  QString lastDirectory = QDir::homePath();
  bool directoryIsValid(QString dir);

public:
  QString get();

  void set(QString dir);

  void setByFile(QString file);
};

extern LastDirectory lastDirectory;

#endif // LASTDIRECTORY_HPP