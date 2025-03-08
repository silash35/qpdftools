#include "externalSoftware.hpp"

ExternalSoftware::ExternalSoftware(QString name, QString command)
    : softwareName(name), softwareCommand(command) {}

void ExternalSoftware::run(const QStringList &arguments, const QString &dir) {
  QProcess process;

  // Set working directory
  if (dir != "default") {
    process.setWorkingDirectory(dir);
    qInfo() << "Using working directory: " << dir << "\n";
  }

  // Start process
  qInfo() << "Executing " << softwareName << " with the arguments:" << arguments << "\n";
  process.start(softwareCommand, arguments, QIODevice::ReadWrite);

  process.closeWriteChannel();

  // Wait for process to finish
  process.waitForFinished();
  qInfo() << "finished to execute " + softwareName << "\n";

  // Check for errors
  QString error = process.readAllStandardError();
  if (!error.isEmpty()) {
    qCritical() << "Error in " + softwareName + ": " + error << "\n";
    throw "Error in " + softwareName + ": " + error;
  }

  qInfo() << "Finished executing " + softwareName;
}
