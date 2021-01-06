//XEBRA header files
#include "LArSPmtSensitiveDetector.hh"

#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>

#include <map>


using std::map;

LArSPmtSensitiveDetector::LArSPmtSensitiveDetector(G4String hName): G4VSensitiveDetector(hName)
{
	collectionName.insert("PmtHitsCollection");
}

LArSPmtSensitiveDetector::~LArSPmtSensitiveDetector()
{
}

void LArSPmtSensitiveDetector::Initialize(G4HCofThisEvent* pHitsCollectionOfThisEvent)
{
	m_pPmtHitsCollection = new LArSPmtHitsCollection(SensitiveDetectorName, collectionName[0]);

	static G4int iHitsCollectionID = -1;

	if(iHitsCollectionID < 0)
		iHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	
	pHitsCollectionOfThisEvent->AddHitsCollection(iHitsCollectionID, m_pPmtHitsCollection); 
}


G4bool LArSPmtSensitiveDetector::ProcessHits(G4Step* pStep, G4TouchableHistory *)
{
	G4Track *pTrack = pStep->GetTrack();

	if(pTrack->GetDefinition()->GetParticleName() == "opticalphoton")
	{
		LArSPmtHit* pHit = new LArSPmtHit();
		//G4cout << "PMT hit" << pTrack->GetTouchable()->GetVolume(0)->GetCopyNo() << G4endl;

		pHit->SetPosition(pStep->GetPreStepPoint()->GetPosition());
		pHit->SetTime(pTrack->GetGlobalTime());
		pHit->SetPmtNb(pTrack->GetTouchable()->GetVolume(0)->GetCopyNo()); 

		m_pPmtHitsCollection->insert(pHit);
		
		pHit->Print();


		return true;
	}
	else
	{
		return false;
	}
}

void LArSPmtSensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
}

