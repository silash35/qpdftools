#pragma once

#include <QDebug>
#include <QProcess>

class ExternalSoftware {
protected:
  QString softwareName;
  QString softwareCommand;

  QString run(QStringList arguments, QString dir = "default");

public:
  ExternalSoftware(QString name, QString command);
};
