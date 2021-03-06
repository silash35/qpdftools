#ifndef EXTERNALSOFTWARE_HPP
#define EXTERNALSOFTWARE_HPP

#include <QDebug>
#include <QProcess>

class ExternalSoftware {
protected:
  QProcess process;
  QString softwareName = "";
  QString softwareCommand = "";

  void waitForFinished() {
    process.waitForFinished();
    qDebug() << "finished to execute " + softwareName << "\n";
  }

public:
  void start(QStringList arguments, QString dir) {
    if (dir != "default") {
      process.setWorkingDirectory(dir);
      qDebug() << dir << "\n";
    }
    qDebug() << "starting to execute " << softwareName
             << " with the folowing arguments:" << arguments << "\n";
    process.start(softwareCommand, arguments, QIODevice::ReadWrite);
    process.closeWriteChannel();
  }

  QString getStandardError() {
    waitForFinished();
    qDebug() << process.readAllStandardOutput() << "\n";
    return process.readAllStandardError();
  }

  ~ExternalSoftware() { process.close(); }
};
#endif // EXTERNALSOFTWARE_HPP
