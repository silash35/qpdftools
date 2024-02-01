#include "qpdf.hpp"

Qpdf::Qpdf() : ExternalSoftware("qpdf", "qpdf") {}

QString Qpdf::splitPDF(QString input, QString outputFolder) {
  // qpdf in.pdf out.pdf --split-pages

  QStringList arguments;
  arguments << input << "out.pdf"
            << "--split-pages";

  return run(arguments, outputFolder);
}

QString Qpdf::splitPDF(QString input, QString output, int firstPage, int lastPage) {
  // qpdf in.pdf --pages . start-end -- out.pdf

  QStringList arguments;
  arguments << input;
  arguments << "--pages";
  arguments << ".";
  arguments << firstPage + "-" + lastPage;
  arguments << "--";
  arguments << output;

  return run(arguments);
}

QString Qpdf::mergePDF(QStringList inputs, QString output) {
  // qpdf --empty --pages in1.pdf in2.pdf -- out.pdf
  QStringList arguments;

  arguments << "--empty"
            << "--pages";

  for (int i = 0; i < inputs.size(); ++i)
    arguments << inputs[i];

  arguments << "--" << output;

  return run(arguments);
}

QString Qpdf::rotatePDF(QString input, QString output, int angle) {
  // qpdf in.pdf out.pdf --rotate=angle

  QStringList arguments;

  arguments << input;
  arguments << output;
  arguments << "--rotate=" + angle;

  run(arguments);
}

Qpdf qpdf;