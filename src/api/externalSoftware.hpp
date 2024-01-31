#pragma once

#include <QDebug>
#include <QProcess>

class ExternalSoftware {
protected:
  QProcess process;
  QString softwareName = "";
  QString softwareCommand = "";

  void waitForFinished() {
    process.waitForFinished();
    qInfo() << "finished to execute " + softwareName << "\n";
  }

public:
  void start(QStringList arguments, QString dir) {
    if (dir != "default") {
      process.setWorkingDirectory(dir);
      qInfo() << dir << "\n";
    }
    qInfo() << "starting to execute " << softwareName
            << " with the following arguments:" << arguments << "\n";
    process.start(softwareCommand, arguments, QIODevice::ReadWrite);
    process.closeWriteChannel();
  }

  QString getStandardError() {
    waitForFinished();
    qInfo() << process.readAllStandardOutput() << "\n";
    return process.readAllStandardError();
  }

  ~ExternalSoftware() { process.close(); }
};
