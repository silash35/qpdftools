#ifndef EXTERNALSOFTWARE_H
#define EXTERNALSOFTWARE_H

#include <QProcess>
#include <QDebug>

class ExternalSoftware{
protected:

  QProcess process;
  QString softwareName = "";
  QString softwareCommand = "";

  void waitForFinished(){
    process.waitForFinished();
    qDebug() << "finished to execute " + softwareName << "\n";
  }

public:

  void start(QStringList arguments){
    qDebug() << "starting to execute " << softwareName << " with the folowing arguments:" << arguments << "\n";
    process.start(softwareCommand, arguments, QIODevice::ReadWrite);
    process.closeWriteChannel();
  }

  QString getStandardError(){
    waitForFinished();
    qDebug() << process.readAllStandardOutput() << "\n";
    return process.readAllStandardError();
  }

  ~ExternalSoftware(){
    process.close();
  }

};
#endif // EXTERNALSOFTWARE_H
