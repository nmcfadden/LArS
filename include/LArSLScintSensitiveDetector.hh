#ifndef __XEBRALSCINTSENSITIVEDETECTOR_H__
#define __XEBRALSCINTSENSITIVEDETECTOR_H__

#include "LArSLScintHit.hh"

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class LArSLScintSensitiveDetector: public G4VSensitiveDetector
{
public:
	LArSLScintSensitiveDetector(G4String hName);
	~LArSLScintSensitiveDetector();

	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4double BirksAttenuation(const G4Step* aStep);

private:
	LArSLScintHitsCollection* m_pLScintHitsCollection;

	std::map<int,G4String> m_hParticleTypes;
};

#endif
