/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#include "GateBlurring.hh"

#include "GateBlurringMessenger.hh"
#include "GateTools.hh"
#include "GateConstants.hh"
#include "Randomize.hh"


GateBlurring::GateBlurring(GatePulseProcessorChain* itsChain,
      	      	      	      	 const G4String& itsName)
  : GateVPulseProcessor(itsChain,itsName)
{
  m_messenger = new GateBlurringMessenger(this);
  m_blurringLaw = new GateInverseSquareBlurringLaw(GetObjectName());
}


GateBlurring::~GateBlurring()
{
  delete m_messenger;
  delete m_blurringLaw;
}



void GateBlurring::ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList)
{
	G4double currentEnergy = inputPulse->GetEnergy();
	GatePulse* outputPulse = new GatePulse(*inputPulse);
	outputPulse->SetEnergy(G4RandGauss::shoot(currentEnergy,(m_blurringLaw->ComputeResolution(currentEnergy)*currentEnergy)/GateConstants::fwhm_to_sigma));
	outputPulseList.push_back(outputPulse);
}

void GateBlurring::DescribeMyself(size_t indent)
{
 G4cout << GateTools::Indent(indent) << "Blurring law:\t" << m_blurringLaw->GetObjectName() << Gateendl;
 m_blurringLaw->DescribeMyself();
}
