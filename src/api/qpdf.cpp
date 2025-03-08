#include "qpdf.hpp"

Qpdf::Qpdf() : ExternalSoftware("qpdf", "qpdf") {}

void Qpdf::splitPDF(const QString &input, const QString &outputFolder) {
  QString output = QFileInfo(input).completeBaseName() + ".pdf";

  // qpdf input.pdf output.pdf --split-pages
  QStringList arguments = {input, output, "--split-pages"};

  run(arguments, outputFolder);
}

void Qpdf::splitPDF(const QString &input, const QString &output, int firstPage, int lastPage) {
  // qpdf input.pdf --pages . firstPage-lastPage -- output.pdf
  QStringList arguments = {
    input, "--pages", ".", QString::number(firstPage) + "-" + QString::number(lastPage)};

  if (input == output) {
    arguments << "--" << "--replace-input";
  } else {
    arguments << "--" << output;
  }

  run(arguments);
}

void Qpdf::mergePDF(const QStringList &inputs, const QString &output) {
  // Create a temp file if input and output are the same. Prevents file corruption
  QString qpdfOutput = (inputs.contains(output)) ? QDir::tempPath() + "/temp_output.pdf" : output;

  // qpdf --empty --pages inputs[0].pdf inputs[1].pdf -- qpdfOutput.pdf
  QStringList arguments = {"--empty", "--pages"};
  arguments.append(inputs);
  arguments << "--" << qpdfOutput;

  run(arguments);

  // Move temp file to the right place if needed
  if (qpdfOutput != output) {
    QFile::remove(output);
    QFile::rename(qpdfOutput, output);
  }
}

void Qpdf::rotatePDF(const QString &input, const QString &output, int angle) {
  // qpdf in.pdf out.pdf --rotate=angle
  QStringList arguments = {input};

  if (input == output) {
    arguments << "--replace-input";
  } else {
    arguments << output;
  }

  arguments << "--rotate=" + QString::number(angle);

  run(arguments);
}

Qpdf qpdf;