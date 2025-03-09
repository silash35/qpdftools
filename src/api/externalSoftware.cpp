#include "externalSoftware.hpp"

ExternalSoftware::ExternalSoftware(QString name, QString command)
    : softwareName(name), softwareCommand(command) {}

void ExternalSoftware::run(const QStringList &arguments, const QString &dir) {
  QProcess process;

  // Set working directory
  if (dir != "default") {
    process.setWorkingDirectory(dir);
    qInfo() << "Using working directory: " << dir;
  }

  // Start process
  qInfo() << "Executing " << softwareName << " with the arguments:" << arguments;
  process.start(softwareCommand, arguments, QIODevice::ReadWrite);

  process.closeWriteChannel();

  // Wait for process to finish
  process.waitForFinished(120 * 1000); // Increase wait time to 2 minutes, for large files

  // Check for errors
  QString error = process.readAllStandardError();
  if (!error.isEmpty()) {
    qCritical() << "Error in " + softwareName + ": " + error;
    throw "Error in " + softwareName + ": " + error;
  }

  qInfo() << "Finished executing " + softwareName << "\n";
}
