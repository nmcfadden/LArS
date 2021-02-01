#include "LArSEventData.hh"

LArSEventData::LArSEventData()
{
	//Event Info
	m_fTotalEnergyDeposited = 0.;
  m_nScintPhotons = 0;
  m_pTotalStepLength = 0;
  m_iEventId = 0;
  
  //step info 
  m_pVol = new vector<string>;
	m_pX = new vector<float>;
	m_pY = new vector<float>;
	m_pZ = new vector<float>;
	m_pEnergyDeposited = new vector<float>;
	m_pTime = new vector<float>;
	m_pKineticEnergy = new vector<float>;
	m_pTrackId = new vector<int>;
	m_pParentId = new vector<int>;
	m_pDepositingProcess = new vector<string>;
	m_pParticleType = new vector<int>;
	m_pCreatorProcess = new vector<string>;
  m_pStepLength = new vector<float>;

  //Primary info
  m_pVolPrim = new vector<string>;
  m_pXPrim = new vector<float>;
  m_pYPrim = new vector<float>;
  m_pZPrim = new vector<float>;
  m_pKEPrim = new vector<float>;

  //PMT Specific Info
	m_pPmtHits = 0;//new vector<int>;
	
 
}

LArSEventData::~LArSEventData()
{
  //Step info
  delete m_pVol;
	delete m_pX;
	delete m_pY;
	delete m_pZ;
	delete m_pEnergyDeposited;
	delete m_pTime;
	delete m_pKineticEnergy;
	delete m_pTrackId;
	delete m_pParentId;
	delete m_pDepositingProcess;
  delete m_pParticleType;
	delete m_pCreatorProcess;
  delete m_pStepLength;

  //Primary info
  delete m_pVolPrim;
  delete m_pXPrim; 
  delete m_pYPrim; 
  delete m_pZPrim;
  delete m_pKEPrim;
}

void
LArSEventData::Clear()
{
	m_fTotalEnergyDeposited = 0.0;
  m_nScintPhotons = 0;
	m_pTotalStepLength = 0;
	m_iEventId = 0;

  //Step info added by Neil
  m_pVol->clear();
	m_pX->clear();
	m_pY->clear();
	m_pZ->clear();
	m_pEnergyDeposited->clear();
	m_pTime->clear();
	m_pKineticEnergy->clear();
	m_pTrackId->clear();
	m_pParentId->clear();
	m_pDepositingProcess->clear();
	m_pParticleType->clear();
	m_pCreatorProcess->clear();
  m_pStepLength->clear();

  //Primary info
  m_pVolPrim->clear();
  m_pXPrim->clear();
  m_pYPrim->clear();
  m_pZPrim->clear();
  m_pKEPrim->clear();

  //PMT specific info
	m_pPmtHits = 0;

}
