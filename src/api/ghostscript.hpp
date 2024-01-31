#pragma once

#include "externalSoftware.hpp"

class Ghostscript : public ExternalSoftware {
public:
  Ghostscript() {
    softwareName = "Ghostscript";
    softwareCommand = "gs";
  }
};

extern Ghostscript ghostscript;
