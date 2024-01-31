#ifndef QPDF_H
#define QPDF_H

#include "externalSoftware.hpp"

class Qpdf : public ExternalSoftware {
public:
  Qpdf() {
    softwareName = "qpdf";
    softwareCommand = "qpdf";
  }
};

extern Qpdf qpdf;

#endif // QPDF_H
