#pragma once

#include "externalSoftware.hpp"

class Ghostscript : public ExternalSoftware {
public:
  Ghostscript();

  enum CompressionMode { screen, ebook, printer, prepress };

  void compressPDF(QString input, QString output, CompressionMode mode);
  void generateThumbnail(QString input, QString output);
};

extern Ghostscript ghostscript;
