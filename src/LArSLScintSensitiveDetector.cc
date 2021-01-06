#include "LArSLScintSensitiveDetector.hh"

#include <G4SystemOfUnits.hh>
#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>

#include <map>

using std::map;

//#include "LArSLScintSensitiveDetector.hh"

LArSLScintSensitiveDetector::LArSLScintSensitiveDetector(G4String hName): G4VSensitiveDetector(hName)
{
	collectionName.insert("LScintHitsCollection");
}

LArSLScintSensitiveDetector::~LArSLScintSensitiveDetector()
{
}

void LArSLScintSensitiveDetector::Initialize(G4HCofThisEvent* pHitsCollectionOfThisEvent)
{
	m_pLScintHitsCollection = new LArSLScintHitsCollection(SensitiveDetectorName, collectionName[0]);

	static G4int iHitsCollectionID = -1;

	if(iHitsCollectionID < 0)
		iHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	
	pHitsCollectionOfThisEvent->AddHitsCollection(iHitsCollectionID, m_pLScintHitsCollection);

	m_hParticleTypes.clear();
}

G4bool LArSLScintSensitiveDetector::ProcessHits(G4Step* pStep, G4TouchableHistory *)
{
	G4double dEnergyDeposited = pStep->GetTotalEnergyDeposit();
	G4double dEnergyDepositedBirksCorrected = BirksAttenuation(pStep);
	G4Track *pTrack = pStep->GetTrack();

	LArSLScintHit* pHit = new LArSLScintHit();

	pHit->SetTrackId(pTrack->GetTrackID());

	if(!m_hParticleTypes.count(pTrack->GetTrackID()))
		m_hParticleTypes[pTrack->GetTrackID()] = pTrack->GetDefinition()->GetParticleName();

	pHit->SetParentId(pTrack->GetParentID());
	pHit->SetParticleType(pTrack->GetDefinition()->GetParticleName());

	if(pTrack->GetParentID())
		pHit->SetParentType(m_hParticleTypes[pTrack->GetParentID()]);
	else
		pHit->SetParentType(G4String("none"));

	if(pTrack->GetCreatorProcess())
		pHit->SetCreatorProcess(pTrack->GetCreatorProcess()->GetProcessName());
	else
		pHit->SetCreatorProcess(G4String("Null"));

	pHit->SetDepositingProcess(pStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
	pHit->SetPosition(pStep->GetPostStepPoint()->GetPosition());
	pHit->SetEnergyDeposited(dEnergyDeposited);
	pHit->SetEnergyDepositedBirksCorrected(dEnergyDepositedBirksCorrected);
	pHit->SetKineticEnergy(pTrack->GetKineticEnergy());
	pHit->SetTime(pTrack->GetGlobalTime());

	m_pLScintHitsCollection->insert(pHit);

	return true;
}

void LArSLScintSensitiveDetector::EndOfEvent(G4HCofThisEvent *){
}


// DR 20160201 - Birks correction for the E_deposit in LScint
G4double LArSLScintSensitiveDetector::BirksAttenuation(const G4Step* aStep)
{
    G4double birks_e         = 0.124*mm/MeV;
    G4double birks_p         = 0.098*mm/MeV;
    G4double birks_alpha     = 0.071*mm/MeV;
    
    G4String particle    = aStep->GetTrack()->GetDefinition()->GetParticleName();
    G4double destep      = aStep->GetTotalEnergyDeposit();
    G4double stepl       = aStep->GetStepLength();  
    G4double charge      = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
    G4double response    = destep;
    
    if (destep*stepl*charge != 0.){
      if (particle=="e-" || particle=="e+")	response = destep/(1. + birks_e*destep/stepl);
      else if (particle=="proton")		response = destep/(1. + birks_p*destep/stepl);
      else if (particle=="alpha")		response = destep/(1. + birks_alpha*destep/stepl); 
    }
    
    return response;
}
