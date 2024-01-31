#pragma once

#include "externalSoftware.hpp"

class Qpdf : public ExternalSoftware {
public:
  Qpdf() {
    softwareName = "qpdf";
    softwareCommand = "qpdf";
  }
};

extern Qpdf qpdf;
