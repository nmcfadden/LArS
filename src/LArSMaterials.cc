//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                         MaGe Simulation                                   //
//                                                                           //
//      This code implementation is the intellectual property of the         //
//      MAJORANA and Gerda Collaborations. It is based on Geant4, an         //
//      intellectual property of the RD44 GEANT4 collaboration.              //
//                                                                           //
//                        *********************                              //
//                                                                           //
//    Neither the authors of this software system, nor their employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
//
// $Id: MJcodeTemplate.cc,v 1.3 2005-02-15 23:26:55 akbarm Exp $
//
// CLASS IMPLEMENTATION:  LArSMaterials.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 *
 * See .hh file for description.
 *
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: R.Henning
 * CONTACT:
 * FIRST SUBMISSION: Sat Jul  6 18:18:00 EDT 2013
 *
 * REVISION:
 *
 * 07-06-13, Created from PSQL database dump. R. Henning
 * 07-11-17, Duplicated from MJ materials table for LGND, M. Green
 * 06-2018, Added Material needed for Calibration system, R. Massarczyk
 */
//---------------------------------------------------------------------------//
//


//---------------------------------------------------------------------------//

#include "LArSMaterials.hh"

using namespace CLHEP;

//---------------------------------------------------------------------------//

LArSMaterials::LArSMaterials():
  fIsotopesBuilt(false), fElementsBuilt(false), fMaterialsBuilt(false)
{}

//---------------------------------------------------------------------------//

LArSMaterials::~LArSMaterials()
{}

//---------------------------------------------------------------------------//

void LArSMaterials::BuildIsotopes()
{
  if(!fIsotopesBuilt) {
    G4cout << "Building LGND-related isotopes." << G4endl;
    new G4Isotope("Hydrogen1", 1, 1, 1.00782 * g / mole);
    new G4Isotope("Hydrogen2", 1, 2, 2.0141 * g / mole);
    new G4Isotope("Boron10", 5, 10, 10.0129 * g / mole);
    new G4Isotope("Boron11", 5, 11, 11.0093 * g / mole);
    new G4Isotope("Carbon12", 6, 12, 12 * g / mole);
    new G4Isotope("Carbon13", 6, 13, 13.0034 * g / mole);
    new G4Isotope("Nitrogen14", 7, 14, 14.0031 * g / mole);
    new G4Isotope("Nitrogen15", 7, 15, 15.0001 * g / mole);
    new G4Isotope("Oxygen16", 8, 16, 15.9949 * g / mole);
    new G4Isotope("Oxygen17", 8, 17, 16.9991 * g / mole);
    new G4Isotope("Oxygen18", 8, 18, 17.9992 * g / mole);
    new G4Isotope("Fluorine19", 9, 19, 18.9984 * g / mole);
    new G4Isotope("Neon20", 10, 20, 19.9924 * g / mole);
    new G4Isotope("Neon21", 10, 21, 20.9938 * g / mole);
    new G4Isotope("Neon22", 10, 22, 21.9914 * g / mole);
    new G4Isotope("Sodium23", 11, 23, 22.9898 * g / mole);
    new G4Isotope("Magnesium24", 12, 24, 23.985 * g / mole);
    new G4Isotope("Magnesium25", 12, 25, 24.9858 * g / mole);
    new G4Isotope("Magnesium26", 12, 26, 25.9826 * g / mole);
    new G4Isotope("Aluminum27", 13, 27, 26.9815 * g / mole);
    new G4Isotope("Silicon28", 14, 28, 27.9769 * g / mole);
    new G4Isotope("Silicon29", 14, 29, 28.9765 * g / mole);
    new G4Isotope("Silicon30", 14, 30, 29.9738 * g / mole);
    new G4Isotope("Chlorine35", 17, 35, 34.9689 * g / mole);
    new G4Isotope("Chlorine37", 17, 37, 36.9659 * g / mole);
    new G4Isotope("Argon36", 18, 36, 35.9675 * g / mole);
    new G4Isotope("Argon38", 18, 38, 37.9627 * g / mole);
    new G4Isotope("Argon40", 18, 40, 39.9624 * g / mole);
    new G4Isotope("Xenon124", 54, 124, 123.9058 * g / mole); //0.09
    new G4Isotope("Xenon126", 54, 126, 125.904 * g / mole); //0.09
    new G4Isotope("Xenon128", 54, 128, 127.9035 * g / mole);//1.92
    new G4Isotope("Xenon129", 54, 129, 128.9047 * g / mole); //26.44
    new G4Isotope("Xenon130", 54, 130, 129.9035 * g / mole); //4.08
    new G4Isotope("Xenon131", 54, 131, 130.9050 * g / mole); //21.18
    new G4Isotope("Xenon132", 54, 132, 131.9041 * g / mole); //26.89
    new G4Isotope("Xenon134", 54, 134, 133.9053 * g / mole); //10.44
    new G4Isotope("Xenon136", 54, 136, 135.9072 * g / mole); //8.87/
    new G4Isotope("Titanium46", 22, 46, 45.9526 * g / mole);
    new G4Isotope("Titanium47", 22, 47, 46.9518 * g / mole);
    new G4Isotope("Titanium48", 22, 48, 47.9479 * g / mole);
    new G4Isotope("Titanium49", 22, 49, 48.9479 * g / mole);
    new G4Isotope("Titanium50", 22, 50, 49.9448 * g / mole);
    new G4Isotope("Chromium50", 24, 50, 49.946 * g / mole);
    new G4Isotope("Chromium52", 24, 52, 51.9405 * g / mole);
    new G4Isotope("Chromium53", 24, 53, 52.9407 * g / mole);
    new G4Isotope("Chromium54", 24, 54, 53.9389 * g / mole);
    new G4Isotope("Iron54", 26, 54, 53.9396 * g / mole);
    new G4Isotope("Iron56", 26, 56, 55.9349 * g / mole);
    new G4Isotope("Iron57", 26, 57, 56.9354 * g / mole);
    new G4Isotope("Iron58", 26, 58, 57.9333 * g / mole);
    new G4Isotope("Nickel58", 28, 58, 57.9353 * g / mole);
    new G4Isotope("Nickel60", 28, 60, 59.9308 * g / mole);
    new G4Isotope("Nickel61", 28, 61, 60.9311 * g / mole);
    new G4Isotope("Nickel62", 28, 62, 61.9283 * g / mole);
    new G4Isotope("Nickel64", 28, 64, 63.928 * g / mole);
    new G4Isotope("Copper63", 29, 63, 62.9296 * g / mole);
    new G4Isotope("Copper65", 29, 65, 64.9278 * g / mole);
    new G4Isotope("Germanium70", 32, 70, 69.9243 * g / mole);
    new G4Isotope("Germanium72", 32, 72, 71.9221 * g / mole);
    new G4Isotope("Germanium73", 32, 73, 72.9235 * g / mole);
    new G4Isotope("Germanium74", 32, 74, 73.9212 * g / mole);
    new G4Isotope("Germanium76", 32, 76, 75.9214 * g / mole);
    new G4Isotope("Cadmium106", 48, 106, 105.906 * g / mole);
    new G4Isotope("Cadmium108", 48, 108, 107.904 * g / mole);
    new G4Isotope("Cadmium110", 48, 110, 109.903 * g / mole);
    new G4Isotope("Cadmium111", 48, 111, 110.904 * g / mole);
    new G4Isotope("Cadmium112", 48, 112, 111.903 * g / mole);
    new G4Isotope("Cadmium113", 48, 113, 112.904 * g / mole);
    new G4Isotope("Cadmium114", 48, 114, 113.903 * g / mole);
    new G4Isotope("Cadmium116", 48, 116, 115.905 * g / mole);
    new G4Isotope("Lead204", 82, 204, 203.973 * g / mole);
    new G4Isotope("Lead206", 82, 206, 205.974 * g / mole);
    new G4Isotope("Lead207", 82, 207, 206.976 * g / mole);
    new G4Isotope("Lead208", 82, 208, 207.977 * g / mole);
    new G4Isotope("Indium113", 49, 113, 112.904 * g / mole);
    new G4Isotope("Indium115", 49, 115, 114.904 * g / mole);
    new G4Isotope("Iodine127", 53, 127, 126.904 * g / mole);
    new G4Isotope("Gold197", 79, 197, 196.967 * g / mole);
    new G4Isotope("Zinc64", 30, 64, 63.929 * g / mole);
    new G4Isotope("Zinc66", 30, 66, 65.926 * g / mole);
    new G4Isotope("Zinc67", 30, 67, 66.927 * g / mole);
    new G4Isotope("Zinc68", 30, 68, 67.924 * g / mole);
    new G4Isotope("Zinc70", 30, 70, 69.925 * g / mole);
    new G4Isotope("Silver107", 47, 107, 106.905 * g / mole);
    new G4Isotope("Silver109", 47, 109, 108.904 * g / mole);
    new G4Isotope("Tin112", 50, 112, 111.904 * g / mole);
    new G4Isotope("Tin114", 50, 114, 113.902 * g / mole);
    new G4Isotope("Tin115", 50, 115, 114.903 * g / mole);
    new G4Isotope("Tin116", 50, 116, 115.901 * g / mole);
    new G4Isotope("Tin117", 50, 117, 116.902 * g / mole);
    new G4Isotope("Tin118", 50, 118, 117.901 * g / mole);
    new G4Isotope("Tin119", 50, 119, 118.903 * g / mole);
    new G4Isotope("Tin120", 50, 120, 119.902 * g / mole);
    new G4Isotope("Tin122", 50, 122, 121.903 * g / mole);
    new G4Isotope("Tin124", 50, 124, 123.905 * g / mole);
    new G4Isotope("Tantalum180", 73, 180, 179.947 * g / mole);
    new G4Isotope("Tantalum181", 73, 181, 180.948 * g / mole);
    new G4Isotope("Manganese55", 25, 55, 54.938 * g / mole);
    G4cout << "Built LGND-related isotopes." << G4endl;
    fIsotopesBuilt = true;
  } else
    G4cout << "Cannot build isotopes more than once!" << G4endl;
}

//---------------------------------------------------------------------------//

void LArSMaterials::BuildElements()
{
  // Note:
  // As of 7/7/13 all elements are built from individual isotopes. This may not be
  // the best method for neutron scattering and cosmic-ray simulations because
  // the cross-section data for the naturally occuring element may be better than for
  // the individual isotopes.
  // For these simulations each element needs to be evaluated individually.
  // R. Henning (rhenning@unc.edu)

  if(!fElementsBuilt) {
    G4Element *LGNDElement;

    G4cout << "Building LGND-related Elements." << G4endl;

    LGNDElement = new G4Element("Gold", "Au", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Gold197"), 1);

    LGNDElement = new G4Element("Carbon", "C", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Carbon12"), 0.989);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Carbon13"), 0.011);

    LGNDElement = new G4Element("Hydrogen", "H", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Hydrogen1"), 0.99985);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Hydrogen2"), 0.00015);

    LGNDElement = new G4Element("Oxygen", "O", 3);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Oxygen16"), 0.9976);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Oxygen17"), 0.0004);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Oxygen18"), 0.002);

    LGNDElement = new G4Element("Copper", "Cu", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Copper63"), 0.6917);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Copper65"), 0.3083);

	//https://mjdoc.npl.washington.edu/record/1847/files/IsotopeAbundance.pdf
	// sum is 100.821 so I scaled all so the sum is 100
    LGNDElement = new G4Element("Germanium-Enr86", "Ge", 5);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium70"), 0.00004/1.00821);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium72"), 0.00009/1.00821);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium73"), 0.00028/1.00821);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium74"), 0.1268/1.00821);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium76"), 0.8810/1.00821);

    LGNDElement = new G4Element("Germanium-Nat", "Ge", 5);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium70"), 0.2124);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium72"), 0.2766);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium73"), 0.0772);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium74"), 0.3594);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Germanium76"), 0.0744);

    LGNDElement = new G4Element("Silicon", "Si", 3);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Silicon28"), 0.9223);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Silicon29"), 0.0467);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Silicon30"), 0.031);

    LGNDElement = new G4Element("Sodium", "Na", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Sodium23"), 1);

    LGNDElement = new G4Element("Chlorine", "Cl", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Chlorine35"), 0.7577);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Chlorine37"), 0.2423);

    LGNDElement = new G4Element("Nitrogen", "N", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nitrogen14"), 0.9963);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nitrogen15"), 0.0037);

    LGNDElement = new G4Element("Aluminum", "Al", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Aluminum27"), 1);

    LGNDElement = new G4Element("Iodine", "I", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Iodine127"), 1);

    LGNDElement = new G4Element("Indium", "In", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Indium113"), 0.0429);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Indium115"), 0.9571);

    LGNDElement = new G4Element("Boron", "B", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Boron11"), 0.8);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Boron10"), 0.2);

    LGNDElement = new G4Element("Iron", "Fe", 4);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Iron54"), 0.058);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Iron56"), 0.9172);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Iron57"), 0.022);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Iron58"), 0.0028);

    LGNDElement = new G4Element("Chromium", "Cr", 4);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Chromium50"), 0.04345);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Chromium52"), 0.83789);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Chromium53"), 0.09501);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Chromium54"), 0.02365);

    LGNDElement = new G4Element("Magnesium", "Mg", 3);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Magnesium24"), 0.7899);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Magnesium25"), 0.1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Magnesium26"), 0.1101);

    LGNDElement = new G4Element("Titanium", "Ti", 5);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Titanium46"), 0.08);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Titanium47"), 0.073);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Titanium48"), 0.738);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Titanium49"), 0.055);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Titanium50"), 0.054);

    LGNDElement = new G4Element("Cadmium", "Cd", 8);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium106"), 0.0089);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium108"), 0.0089);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium110"), 0.1249);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium111"), 0.128);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium112"), 0.2413);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium113"), 0.1222);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium114"), 0.2873);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Cadmium116"), 0.0749);

    LGNDElement = new G4Element("Lead", "Pb", 4);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Lead204"), 0.014);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Lead206"), 0.241);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Lead207"), 0.221);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Lead208"), 0.524);

    LGNDElement = new G4Element("Flourine", "F", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Fluorine19"), 1);

    LGNDElement = new G4Element("Nickel", "Ni", 5);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nickel58"), 0.68077);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nickel60"), 0.26233);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nickel61"), 0.0114);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nickel62"), 0.03634);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Nickel64"), 0.00926);

    LGNDElement = new G4Element("Neon", "Ne", 3);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Neon20"), 0.9048);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Neon21"), 0.0027);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Neon22"), 0.0925);

    LGNDElement = new G4Element("Argon", "Ar", 3);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Argon36"), 0.00337);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Argon38"), 0.00063);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Argon40"), 0.996);

    LGNDElement = new G4Element("Xenon","Xe",9);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon124"),0.090);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon126"),0.090);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon128"),1.920);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon129"),26.44);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon130"),4.080);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon131"),21.18);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon132"),26.89);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon134"),10.44);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Xenon136"),8.870);

    LGNDElement = new G4Element("Zinc", "Zn", 5);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Zinc64"), 0.4863);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Zinc66"), 0.2790);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Zinc67"), 0.0410);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Zinc68"), 0.1875);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Zinc70"), 0.0062);

    LGNDElement = new G4Element("Silver", "Ag", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Silver107"), 0.5183);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Silver109"), 0.4816);

    LGNDElement = new G4Element("Tin", "Sn", 10);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin112"), 0.0097);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin114"), 0.0066);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin115"), 0.0034);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin116"), 0.1454);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin117"), 0.0768);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin118"), 0.2422);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin119"), 0.0859);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin120"), 0.3258);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin122"), 0.0463);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tin124"), 0.0579);

	  LGNDElement = new G4Element("Tantalum", "Ta", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tantalum180"), 0.00012);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Tantalum181"), 0.99988);

	  LGNDElement = new G4Element("Manganese", "Mn", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Manganese55"), 1);

    //Added by Neil 8-1-2021
    /*
 	  LGNDElement = new G4Element("Phosphorus", "P", 1);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Phosphorus31"), 1);

    LGNDElement = new G4Element("Sulfur", "S", 4);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Sulfur32"), 0.9484);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Sulfur33"), 0.0075);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Sulfur34"), 0.0421);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Sulfur36"), 0.002);

    LGNDElement = new G4Element("Potassium", "K", 2);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Potassium39"), 0.933);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Potassium41"), 0.067);

    LGNDElement = new G4Element("Calcium", "Ca", 5);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Calcium40"), 0.96941);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Calcium42"), 0.00647);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Calcium43"), 0.00135);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Calcium44"), 0.02086);
    LGNDElement->AddIsotope(G4Isotope::GetIsotope("Calcium46"), 0.0004);
    */

    G4cout << "LGND-related materials built." << G4endl;
    fElementsBuilt = true;
  } else
    G4cout << "Cannot build elements more than once!" << G4endl;
}

//---------------------------------------------------------------------------//

void LArSMaterials::BuildMaterials()
{
  if(!fMaterialsBuilt) {
    G4cout << "Building LGND-related materials." << G4endl;

    G4Material *LGNDMaterial;

    LGNDMaterial = new G4Material("MgF2",3.15 *g /cm3,2);
    LGNDMaterial->AddElement(G4Element::GetElement("Magnesium"),1);
    LGNDMaterial->AddElement(G4Element::GetElement("Flourine"),2);
    
    LGNDMaterial = new G4Material("Gold", 19.3 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Gold"), 1);

    LGNDMaterial = new G4Material("Silicon", 2.328 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Silicon"), 1);

    LGNDMaterial = new G4Material("Acrylic", 1.18 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 5);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 8);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 2);

    LGNDMaterial = new G4Material("Copper-EF", 8.96 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Copper"), 1);

    LGNDMaterial = new G4Material("Copper-OFHC", 8.96 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Copper"), 1);

    LGNDMaterial = new G4Material("Delrin", 1.41 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 1);

    LGNDMaterial = new G4Material("Germanium-Enr", 5.545 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Germanium-Enr86"), 1);

    LGNDMaterial = new G4Material("Germanium-Nat", 5.323 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Germanium-Nat"), 1);

    LGNDMaterial = new G4Material("Polyethylene", 0.948 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 2);

    LGNDMaterial = new G4Material("Rock", 2.6 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Silicon"), 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 2);

    LGNDMaterial = new G4Material("Salt", 2.165 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Sodium"), 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Chlorine"), 1);

    LGNDMaterial = new G4Material("Scintillator-Liq", 0.876 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 9);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 12);

    LGNDMaterial = new G4Material("Vacuum", 6.24151e-07 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 2);

    LGNDMaterial = new G4Material("Aluminum", 2.705 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Aluminum"), 1);

    LGNDMaterial = new G4Material("NaI", 3.667 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Sodium"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Iodine"), 2);

    LGNDMaterial = new G4Material("Indium", 7.31 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Indium"), 1);

    LGNDMaterial = new G4Material("Borated-Poly-10%", 1.03 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 433);
    LGNDMaterial->AddElement(G4Element::GetElement("Boron"), 31);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 214);

    LGNDMaterial = new G4Material("Scintillator-Pla", 1.03 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 2);

    LGNDMaterial = new G4Material("Iron", 7.87 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Iron"), 1);

    LGNDMaterial = new G4Material("Chromium", 7.19 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Chromium"), 1);

    LGNDMaterial = new G4Material("Magnesium", 1.738 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Magnesium"), 1);

    LGNDMaterial = new G4Material("Titanium", 4.506 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Titanium"), 1);

    LGNDMaterial = new G4Material("Cadmium", 8.64 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Cadmium"), 1);

    LGNDMaterial = new G4Material("Lead-Ain", 11.36 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Lead"), 1);

    LGNDMaterial = new G4Material("Lead-Mod", 11.36 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Lead"), 1);

    LGNDMaterial = new G4Material("Teflon", 2.18 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Flourine"), 4);

    LGNDMaterial = new G4Material("SS303", 8.027 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Iron"), 113);
    LGNDMaterial->AddElement(G4Element::GetElement("Chromium"), 346);
    LGNDMaterial->AddElement(G4Element::GetElement("Nickel"), 153);

    LGNDMaterial = new G4Material("Nickel", 8.912 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Nickel"), 1);

    LGNDMaterial = new G4Material("Carbon", 2.267 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 1);

    LGNDMaterial = new G4Material("Neon", 0.0009 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Neon"), 1);

    LGNDMaterial = new G4Material("Argon", 0.00178 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Argon"), 1);

    LGNDMaterial = new G4Material("Xenon", 0.00576 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Xenon"), 1);

    LGNDMaterial = new G4Material("Neon-Liq", 1.224 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Neon"), 1);

    LGNDMaterial = new G4Material("Argon-Liq", 1.401 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Argon"), 1);

    LGNDMaterial = new G4Material("Xenon-Liq", 2.942 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Xenon"), 1);

    LGNDMaterial = new G4Material("Xenon-Doped-Argon-Liq",1.401 * g / cm3,2);
    LGNDMaterial->AddElement(G4Element::GetElement("Argon"), 1.-1.e-6);
    LGNDMaterial->AddElement(G4Element::GetElement("Xenon"), 1.e-6);

    LGNDMaterial = new G4Material("Hydrogen", 9e-05 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 1);

    LGNDMaterial = new G4Material("Oxygen", 0.00143 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 1);

    LGNDMaterial = new G4Material("Nitrogen-Liq", 0.807 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 1);

    LGNDMaterial = new G4Material("Nitrogen-Gas", 0.001251 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 1);

    LGNDMaterial = new G4Material("Air", 0.001161 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 76);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 23);
    LGNDMaterial->AddElement(G4Element::GetElement("Argon"), 1);

    LGNDMaterial = new G4Material("PEEK", 1.3 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 19);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 18);

    LGNDMaterial = new G4Material("Parylene-N", 1.11 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 8);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 10);

    LGNDMaterial = new G4Material("Parylene-C", 1.289 * g / cm3, 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 8);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 10);
    LGNDMaterial->AddElement(G4Element::GetElement("Chlorine"), 1);

    LGNDMaterial = new G4Material("Silica", 2.634 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Silicon"), 1);

    LGNDMaterial = new G4Material("Vespel", 1.43 * g /cm3, 4);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 22);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 10);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 5);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 2);

    LGNDMaterial = new G4Material("Brass", 8.49 * g / cm3, 5);
    LGNDMaterial->AddElement(G4Element::GetElement("Copper"), 613);
    LGNDMaterial->AddElement(G4Element::GetElement("Zinc"), 353);
    LGNDMaterial->AddElement(G4Element::GetElement("Lead"), 30);
    LGNDMaterial->AddElement(G4Element::GetElement("Iron"), 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Gold"), 1);

    LGNDMaterial = new G4Material("Solder", 7.37 * g / cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Tin"), 965);
    LGNDMaterial->AddElement(G4Element::GetElement("Silver"), 35);

    LGNDMaterial = new G4Material("Nylon", 1.15 * g / cm3, 4);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 3);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 13);

		LGNDMaterial = new G4Material("MetalTantalum", 16.69 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Tantalum"), 1);

  	// modify density in order to have the equivalent of two 2x2cm gold foils, with 20 um thickness
		LGNDMaterial = new G4Material("CapsGold", 4.825 * g / cm3, 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Gold"), 1);

	  //stainless steel (from GERDA table)
    LGNDMaterial = new G4Material("Steel", 7.9 * g / cm3, 5);
    LGNDMaterial->AddElement(G4Element::GetElement("Silicon"), 1);
    LGNDMaterial->AddElement(G4Element::GetElement("Chromium"), 20);
    LGNDMaterial->AddElement(G4Element::GetElement("Manganese"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Iron"), 67);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 10);

    LGNDMaterial = new G4Material("VM2000", 0.9*g/cm3, 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"), 2);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"), 4);

    LGNDMaterial = new G4Material("PEN",1.3*g/cm3,3);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"),14);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"),10);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"),4);

   /* LGNDMaterial = new G4Material("Tetratex_TPB",density=0.401*g/cm3,2);
    LGNDMaterial->AddElement(C, 0.240183);
    LGNDMaterial->AddElement(F, 0.759817);*/

    LGNDMaterial = new G4Material("Ultem", 1.27*g/cm3, 4);
    LGNDMaterial->AddElement(G4Element::GetElement("Carbon"),37);
    LGNDMaterial->AddElement(G4Element::GetElement("Hydrogen"),24);
    LGNDMaterial->AddElement(G4Element::GetElement("Oxygen"), 6);
    LGNDMaterial->AddElement(G4Element::GetElement("Nitrogen"), 2);

    G4cout << "LGND-related materials built." << G4endl;
  } else
    G4cout << "Cannot build materials more than once!" << G4endl;
}

//---------------------------------------------------------------------------//

void LArSMaterials::BuildAll()
{
  BuildIsotopes();
  BuildElements();
  BuildMaterials();
  //Register optical Materials
  LArSOpticalMaterialProperties * opticalMaterials = new LArSOpticalMaterialProperties();
  opticalMaterials->ConstructionOpticalProperties();
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
