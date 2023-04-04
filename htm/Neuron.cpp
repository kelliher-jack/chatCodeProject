#include "Neuron.h"
#include "MemManager.h"

#include <iostream>
using namespace std;

//#define BUG
#ifdef BUG
#include "mpi.h"
#endif


extern MemManager mem_manager;

nSynapse::~nSynapse(void)
{
}

nSynapse::nSynapse(void)
{
}

nSegment::~nSegment(void)
{
}

nSegment::nSegment(void)
{
}

void nSegment::computeStep(void)
{
  fValue input;
  FastListIter synapses_iter(Synapses);
  for (nSynapse * syn = (nSynapse *) (synapses_iter.Reset()); syn != NULL;
       syn = (nSynapse *) (synapses_iter.Advance())) {
    int sizeX = syn->RefSource->dataptr->sizeX;
    int sizeY = syn->RefSource->dataptr->sizeY;
    input = syn->RefSource->dataptr->data[syn->InputPoint.X +  syn->InputPoint.Y * sizeX + syn->InputPoint.Index * sizeX * sizeY];
    //cout << "input value " << input << " ConnectionStrength " << syn->ConnectionStrength << "\n";
    bNormParams nParams = {syn->ConnectionStrength,syn->Parameters->ConnectedPermanence};
    //cout << "output value " << syn->Parameters->normalization(input,&nParams) << "\n";      
  }
}

Dendrite::~Dendrite(void)
{
}

Dendrite::Dendrite(void)
{
}

void Dendrite::computeStep(void)
{
    FastListIter segments_iter(Segments);
    for (nSegment * seg = (nSegment *) (segments_iter.Reset()); seg != NULL;
	 seg = (nSegment *) (segments_iter.Advance())) {
      seg->computeStep();
      cout << "DC\n";
    }
}

Neuron::Neuron(void)
{
}

Neuron::~Neuron(void)
{
}

Neuron::Neuron(UInt _x, UInt _y, UInt _z)
{
  xLoc = _x;
  yLoc = _y;
  zLoc = _z;

  SumaDepolarization       = 0;
  SumaPlateauTimeConstant  = 0;
  SumaResponceTimeConstant = 0;

  DendriticDepolarization       = 0;
  DendriticPlateauTimeConstant  = 0;
  DendriticResponceTimeConstant = 0;

  ProximalBasalDendrite.nOutput = 0;
  ProximalBasalDendrite.type = PROXIMAL;
  ProximalBasalDendrite.neuron = this;
  
  DistalBasalDendrites.nOutput = 0;
  DistalBasalDendrites.type = DISTAL;
  DistalBasalDendrites.neuron = this;

  ApicalDendrites.nOutput = 0;
  ApicalDendrites.type = APICAL;
  ApicalDendrites.neuron = this;

  addSegment(PROXIMAL, 0);
  
  active = false;
  /* IsActive = false;
     WasActive = false;
     _isPredicting = false;
     WasPredicted = false;
     IsLearning = false;
     WasLearning = false;
     NumPredictionSteps = 0;
     PrevNumPredictionSteps = 0;
     PrevActiveTime = -1;
  */
}

void Neuron::initialize(nColumn *col, UInt _x, UInt _y, UInt _z)
{
  xLoc = _x;
  yLoc = _y;
  zLoc = _z;

  //cout << "Neuron " << xLoc << "," << yLoc << "," << zLoc << "\n";

  nColumn *column          = col;

  SumaDepolarization       = 0;
  SumaPlateauTimeConstant  = 0;
  SumaResponceTimeConstant = 0;

  DendriticDepolarization       = 0;
  DendriticPlateauTimeConstant  = 0;
  DendriticResponceTimeConstant = 0;

  ProximalBasalDendrite.nOutput = 0;
  ProximalBasalDendrite.type = PROXIMAL;
  ProximalBasalDendrite.neuron = this;
  
  DistalBasalDendrites.nOutput = 0;
  DistalBasalDendrites.type = DISTAL;
  DistalBasalDendrites.neuron = this;

  ApicalDendrites.nOutput = 0;
  ApicalDendrites.type = APICAL;
  ApicalDendrites.neuron = this;

  addSegment(PROXIMAL, 0);
}

void Neuron::computeStep()
{
  /*
    WasPredicted = _isPredicting;
    WasSegmentPredicted = IsSegmentPredicting;
    WasActive = IsActive;
    WasLearning = IsLearning;
    _isPredicting = false;
    IsSegmentPredicting = false;
    IsActive = false;
    IsLearning = false;
    PrevNumPredictionSteps = NumPredictionSteps;
    NumPredictionSteps = 0;
  */

  ProximalBasalDendrite.computeStep();
  cout << "NC\n";

}

void Neuron::addSynapse(DendriteType type,
			SegmentIndex segmentIdx,
			SynParams *params,
			DataSpaceRef * inputSource,
			DataPoint & inputPoint,
			fValue permanence,
			fValue distanceToInput) {
#ifdef BUG
  std::cout << MPI::COMM_WORLD.Get_rank() << ":Neuron::addSynapse(" << type << " perm " << permanence << " parameter Connected " << params->ConnectedPermanence << "\n";
#endif
  switch(type) {
    case PROXIMAL:
      {
	if(ProximalBasalDendrite.Segments.Count() == 0) {
	  ProximalBasalDendrite.Segments.InsertAtEnd((nSegment *)(mem_manager.GetObject(MOT_NSEGMENT)));
	}
	nSegment * segment = (nSegment *)ProximalBasalDendrite.Segments.GetLast();
	nSynapse * synapse = (nSynapse *)(mem_manager.GetObject(MOT_NSYNAPSE));
	synapse->Parameters  = params;	
	synapse->RefSource   = inputSource;
	synapse->InputPoint  = inputPoint;
	//cout << "added syn " << synapse->InputPoint.X << "," << synapse->InputPoint.Y << "\n";
	//cout << "added syn connection " << synapse->Parameters->ConnectedPermanence << " inc " << synapse->Parameters->PermanenceInc << "\n";	
	synapse->ConnectionStrength = permanence;
	synapse->Permanence = permanence;	
	synapse->DistanceToInput    = distanceToInput;
	segment->Synapses.InsertAtEnd(synapse);
      }
      break;
    case DISTAL:
      {
	nSegment * segment =
	  (nSegment *)DistalBasalDendrites.Segments.GetByIndex(segmentIdx);
	nSynapse * synapse = (nSynapse *)(mem_manager.GetObject(MOT_NSYNAPSE));
	synapse->Parameters  = params;	
	synapse->RefSource   = inputSource;
	synapse->InputPoint  = inputPoint;
	synapse->ConnectionStrength = permanence;
	synapse->DistanceToInput    = distanceToInput;
	segment->Synapses.InsertAtEnd(synapse);
      }
      break;
    case APICAL:
      {
	nSegment * segment =
	  (nSegment *)ApicalDendrites.Segments.GetByIndex(segmentIdx);
	nSynapse * synapse = (nSynapse *)(mem_manager.GetObject(MOT_NSYNAPSE));
	synapse->Parameters  = params;	
	synapse->RefSource   = inputSource;
	synapse->InputPoint  = inputPoint;
	synapse->ConnectionStrength = permanence;
	synapse->DistanceToInput    = distanceToInput;
	segment->Synapses.InsertAtEnd(synapse);
      }
      break;
  }
}

SegmentIndex Neuron::addSegment(DendriteType type, UInt time)
{
  switch(type) {
    case PROXIMAL:
      if(ProximalBasalDendrite.Segments.Count() == 0) {
	ProximalBasalDendrite.Segments.InsertAtEnd((nSegment *)(mem_manager.GetObject(MOT_NSEGMENT)));
      }
      return(0);
    case DISTAL:
      DistalBasalDendrites.Segments.InsertAtEnd((nSegment *)(mem_manager.GetObject(MOT_NSEGMENT)));
      return(DistalBasalDendrites.Segments.Count() - 1);
    case APICAL:
      ApicalDendrites.Segments.InsertAtEnd((nSegment *)(mem_manager.GetObject(MOT_NSEGMENT)));
      return(ApicalDendrites.Segments.Count() - 1);
  }
}

bool Neuron::GetIsActive()
{
#ifdef BUG
  std::cout << MPI::COMM_WORLD.Get_rank() << ":GetIsActive " << active << " cell " << xLoc << "," << yLoc << "," << zLoc << "\n";
#endif
  return active;
}

bool Neuron::SetActive(bool value)
{
#ifdef BUG1
  std::cout << MPI::COMM_WORLD.Get_rank() << ":SetActive " << value << "\n";
#endif
  active = value;
}
