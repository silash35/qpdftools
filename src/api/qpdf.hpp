#pragma once

#include "externalSoftware.hpp"

class Qpdf : public ExternalSoftware {
public:
  Qpdf();

  QString splitPDF(QString input, QString outputFolder);
  QString splitPDF(QString input, QString output, int firstPage, int lastPage);

  QString mergePDF(QStringList inputs, QString output);
  QString rotatePDF(QString input, QString output, int angle);
};

extern Qpdf qpdf;
