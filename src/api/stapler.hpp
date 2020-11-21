#ifndef STAPLER_H
#define STAPLER_H

#include "externalSoftware.hpp"

class Stapler: public ExternalSoftware{
public:
  Stapler(){
    softwareName = "Stapler";
    softwareCommand = "stapler";
  }
}stapler;
#endif // STAPLER_H
