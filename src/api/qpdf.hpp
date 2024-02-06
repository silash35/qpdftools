#pragma once

#include "externalSoftware.hpp"

class Qpdf : public ExternalSoftware {
public:
  Qpdf();

  void splitPDF(const QString &input, const QString &outputFolder);
  void splitPDF(const QString &input, const QString &output, int firstPage, int lastPage);

  void mergePDF(const QStringList &inputs, const QString &output);

  void rotatePDF(const QString &input, const QString &output, int angle);
};

extern Qpdf qpdf;
