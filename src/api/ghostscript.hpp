#pragma once

#include "externalSoftware.hpp"

#include <QDir>
#include <QFile>

class Ghostscript : public ExternalSoftware {
public:
  Ghostscript();

  enum CompressionMode { screen, ebook, printer, prepress };

  void compressPDF(const QString &input, const QString &output, CompressionMode mode);
  void generateThumbnail(const QString &input, const QString &output);
};

extern Ghostscript ghostscript;
