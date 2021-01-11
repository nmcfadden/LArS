#ifndef __LARSLXESENSITIVEDETECTOR_H__
#define __LARSLXESENSITIVEDETECTOR_H__

#include "LArSLXeHit.hh"

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class LArSSensitiveDetector: public G4VSensitiveDetector
{
public:
        //Constructor
	LArSSensitiveDetector(G4String hName);
        //Destructor
	~LArSSensitiveDetector();

        //mandatory base class
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);

        //optional functions
	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);

private:
	LArSLXeHitsCollection *m_pLXeHitsCollection;
	std::map<int,G4String> m_hParticleTypes;
};

#endif
