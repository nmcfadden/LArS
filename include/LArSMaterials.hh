#ifndef _LARSMATERIALS_HH
#define _LARSMATERIALS_HH

#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Material.hh"

#include "LArSOpticalMaterialProperties.hh"

//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//

class LArSMaterials
{
public:

  LArSMaterials();
  ~LArSMaterials();

  //public interface
  void BuildIsotopes();
  void BuildElements();
  void BuildMaterials();
  void BuildAll();

private:
  bool fIsotopesBuilt;
  bool fElementsBuilt;
  bool fMaterialsBuilt;

};
#endif
