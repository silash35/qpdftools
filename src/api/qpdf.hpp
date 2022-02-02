#ifndef QPDF_H
#define QPDF_H

#include "externalSoftware.hpp"

class Qpdf : public ExternalSoftware {
public:
  Qpdf() {
    softwareName = "qpdf";
    softwareCommand = "qpdf";
  }
} qpdf;
#endif // QPDF_H
