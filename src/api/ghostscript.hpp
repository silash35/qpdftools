#pragma once

#include "externalSoftware.hpp"

class Ghostscript : public ExternalSoftware {
public:
  Ghostscript();

  enum CompressionMode { screen, ebook, printer, prepress };

  QString compressPDF(QString input, QString output, CompressionMode mode);
  QString generateThumbnail(QString input, QString output);
};

extern Ghostscript ghostscript;
