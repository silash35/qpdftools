#include "ghostscript.hpp"

Ghostscript::Ghostscript() : ExternalSoftware("Ghostscript", "gs") {}

void Ghostscript::compressPDF(const QString &input, const QString &output, CompressionMode mode) {
  // Create a temp file if input and output are the same. Prevents file corruption
  QString gsOutput = (input == output) ? QDir::tempPath() + "/temp_output.pdf" : output;

  // gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/mode -dNOPAUSE -dBATCH
  // -sOutputFile=gsOutput.pdf input.pdf
  QStringList arguments = {"-sDEVICE=pdfwrite", "-dCompatibilityLevel=1.4"};

  if (mode == screen) {
    arguments << "-dPDFSETTINGS=/screen";
  } else if (mode == ebook) {
    arguments << "-dPDFSETTINGS=/ebook";
  } else if (mode == printer) {
    arguments << "-dPDFSETTINGS=/printer";
  } else if (mode == prepress) {
    arguments << "-dPDFSETTINGS=/prepress";
  }

  arguments << "-dNOPAUSE"
            << "-dBATCH" << "-sOutputFile=" + gsOutput << input;

  run(arguments);

  // Move temp file to the right place if needed
  if (gsOutput != output) {
    QFile::remove(output);
    QFile::rename(gsOutput, output);
  }
}

void Ghostscript::generateThumbnail(const QString &input, const QString &output) {
  // gs -q -o output.jpg -sDEVICE=jpeg -dLastPage=1 -dUseCropBox input.pdf
  QStringList arguments = {
    "-q", "-o", output, "-sDEVICE=jpeg", "-dLastPage=1", "-dUseCropBox", input};

  run(arguments);
}

Ghostscript ghostscript;
