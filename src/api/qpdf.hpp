#pragma once

#include "externalSoftware.hpp"

class Qpdf : public ExternalSoftware {
public:
  Qpdf();

  void splitPDF(QString input, QString outputFolder);
  void splitPDF(QString input, QString output, int firstPage, int lastPage);

  void mergePDF(QStringList inputs, QString output);

  void rotatePDF(QString input, QString output, int angle);
};

extern Qpdf qpdf;
