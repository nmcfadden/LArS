#ifndef __XEBRAMATERIALS_H__
#define __XEBRAMATERIALS_H__

// Additional Header Files
#include <globals.hh>
#include <map>
#include <vector>

using std::vector;
using std::map;

// Root Header Files
#include "TDirectory.h"
#include "TFile.h"

// G4 Header Files
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <math.h>


class LArSMaterials {
 public:
  LArSMaterials();
  ~LArSMaterials();
    
  void DefineMaterials();

 private:
};

#endif
