#ifndef __XEBRAPMTSENSITIVEDETECTOR_H__
#define __XEBRAPMTSENSITIVEDETECTOR_H__

//XEBRA header files
#include "LArSPmtHit.hh"

//G4 header files
#include <G4VSensitiveDetector.hh>
#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>
#include <G4SystemOfUnits.hh>
#include <G4HCofThisEvent.hh>
//Additional Header Files
#include <map>

class G4Step;
class G4HCofThisEvent;

class LArSPmtSensitiveDetector: public G4VSensitiveDetector
{
public:
	LArSPmtSensitiveDetector(G4String hName);
	 ~LArSPmtSensitiveDetector();

	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	LArSPmtHitsCollection* pPmtHitsCollection;

private:
	LArSPmtHitsCollection* m_pPmtHitsCollection;
//	LArSPmtHitsCollection* pPmtSD;
	std::map<int,G4String> m_hParticleTypes;

};

#endif
