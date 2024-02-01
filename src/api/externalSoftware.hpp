#pragma once

#include <QDebug>
#include <QException>
#include <QProcess>

class ExternalSoftware {
protected:
  QString softwareName;
  QString softwareCommand;

  void run(QStringList arguments, QString dir = "default");

public:
  ExternalSoftware(QString name, QString command);
};
