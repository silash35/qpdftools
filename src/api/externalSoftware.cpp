#include "externalSoftware.hpp"

ExternalSoftware::ExternalSoftware(QString name, QString command)
    : softwareName(name), softwareCommand(command) {}

void ExternalSoftware::run(QStringList arguments, QString dir) {
  QProcess process;

  if (dir != "default") {
    process.setWorkingDirectory(dir);
    qInfo() << dir << "\n";
  }
  qInfo() << "starting to execute " << softwareName << " with the following arguments:" << arguments
          << "\n";
  process.start(softwareCommand, arguments, QIODevice::ReadWrite);
  process.closeWriteChannel();

  process.waitForFinished();
  qInfo() << "finished to execute " + softwareName << "\n";

  QString error = process.readAllStandardError();

  if (!error.isEmpty()) {
    qCritical() << "Error in " + softwareName + ": " + error << "\n";
    throw "Error in " + softwareName + ": " + error;
  }
}
