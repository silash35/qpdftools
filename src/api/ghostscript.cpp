#include "ghostscript.hpp"

Ghostscript::Ghostscript() : ExternalSoftware("Ghostscript", "gs") {}

QString Ghostscript::compressPDF(QString input, QString output, CompressionMode mode) {

  QStringList arguments;
  arguments << "-sDEVICE=pdfwrite"
            << "-dCompatibilityLevel=1.4";

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
            << "-dBATCH";

  arguments << "-sOutputFile=" + output;
  arguments << input;

  return run(arguments);
}

QString Ghostscript::generateThumbnail(QString input, QString output) {
  QStringList arguments;

  arguments << "-q"
            << "-o" << output << "-sDEVICE=jpeg"
            << "-dLastPage=1"
            << "-dUseCropBox" << input;

  return run(arguments);
}

Ghostscript ghostscript;
