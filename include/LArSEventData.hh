#ifndef __LARSEVENTDATA_H__
#define __LARSEVENTDATA_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

class LArSEventData
{
public:
	 LArSEventData();
	~LArSEventData();

public:
	void Clear();

public:
	//Event Info
	float m_fTotalEnergyDeposited = 0.;
  int   m_nScintPhotons = 0;
  float m_pTotalStepLength = 0;
  int   m_iEventId = 0;
  
  //step info
  vector<string> *m_pVol;
  vector<float>  *m_pX;					// position of the step
	vector<float>  *m_pY;
	vector<float>  *m_pZ;
	vector<float>  *m_pEnergyDeposited; 			// energy deposited in the step
	vector<float>  *m_pTime;					// time of the step
	vector<float>  *m_pKineticEnergy;			// particle kinetic energy after the step
	vector<int>    *m_pTrackId;				// id of the particle
	vector<int>    *m_pParentId;				// id of the parent particle
	vector<string> *m_pDepositingProcess;			// energy depositing process
  vector<int>    *m_pParticleType;
	vector<string> *m_pParentType;				// type of particle
  vector<string> *m_pCreatorProcess;
  vector<float>  *m_pStepLength;

  //primary info
  vector<string> *m_pVolPrim;
  vector<float>  *m_pXPrim;
  vector<float>  *m_pYPrim;
  vector<float>  *m_pZPrim;
  vector<float>  *m_pKEPrim;
	
  //PMT specific Info
  int m_pPmtHits;				// number of photon hits per pmt

};

#endif
