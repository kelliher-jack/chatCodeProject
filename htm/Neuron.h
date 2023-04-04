#pragma once
#include "MemObject.h"
#include "FastList.h"
#include "InputData.h"
#include "DataSpace.h"
#include "Normalization.h"

#include "Utils.h"
#include <vector>

// DO NOT USE! using namespace std;  // Breaks App_Picking

enum DendriteType {
  PROXIMAL = 0,
  DISTAL   = 1,
  APICAL   = 2
};

typedef class  Neuron     Neuron;
typedef class  Dendrite   Dendrite;
typedef class  nSegment   nSegment;
typedef class  nSynapse   nSynapse;
typedef class  nColumn    nColumn;
typedef struct SynParams  SynapticParameters;

typedef unsigned int SegmentIndex;


struct SynParams {
  nValue (*normalization)(nValue, bNormParams *params);   // normalization function
  fValue ConnectedPermanence;  // 0.0 to 1.0
  fValue InitialPermanence;    // 0.0 to 1.0
  fValue PermanenceDec;        // 0.0 to 1.0
  fValue PermanenceInc;        // 0.0 to 1.0
  fValue PredictedDec;         // 0.0 to 1.0
};  

class nSynapse:public MemObject {
public:
  ~nSynapse(void);
  nSynapse(void);  
  
  MemObjectType GetMemObjectType() {
    return MOT_SYNAPSE;
  }

  fValue GetPermanence() {
    return Permanence;
  }

  // The DataSpace for this synapse's input.
  DataSpace *InputSource;
  DataSpaceRef *RefSource;

  // A single input value point from an input DataSource.
  DataPoint InputPoint;

  // Distance, in this synapse's Region's space, to its input DataPoint.
  fValue DistanceToInput;
  
  nValue nOutput;               // equals input * weight
  fValue ConnectionStrength;    // Connection Weight in Neuro nets
  Neuron   *PresynapticCell;
  Dendrite *PresynapticDendrite;
  nSynapse *PresynapticSynapse;

  // Parameters
  SynParams *Parameters;

  // Status
  nValue CurrentActivity;
  nValue PreviousActivity;
  fValue Permanence;
};

class nSegment:public MemObject {
public:
  ~nSegment(void);
  nSegment(void);  
  
  MemObjectType GetMemObjectType() {
    return MOT_SEGMENT;
  }

  void computeStep(void);  
  
  nValue nOutput;            // equals function applied to sum of weighted synapses
                             // normally normilized from 0 to 1
  Dendrite *dendrite;
  FastList Synapses;

  // Parameters
  nValue (*normalization)(nValue,const void *params);   // normalization function f  
};

class Dendrite {
public:  
  ~Dendrite(void);
  Dendrite(void);  
  void computeStep(void);

  nValue nOutput;           // equals f(sum of segments + bias) normally from 0 to 1
  DendriteType type;
  Neuron *neuron;

  FastList Segments;

  // Parameters
  nValue (*normalization)(nValue,const void *params);   // normalization function f
  nValue bias;
};

class Neuron:public MemObject {

  public:
  ~Neuron(void);
  Neuron(void);  
  Neuron(UInt _x, UInt _y, UInt _z);
  
  MemObjectType GetMemObjectType() {
    return MOT_NEURON;
  }

  void initialize(nColumn *col, UInt _x, UInt _y, UInt _z);
  void computeStep(void);

  void addSynapse(DendriteType type,
		  SegmentIndex segmentIdx,		  
		  SynapticParameters *params,
		  DataSpaceRef * inputSource,
		  DataPoint & inputPoint,
		  fValue permanence,
		  fValue distanceToInput = 0);
  
  SegmentIndex addSegment(DendriteType type, UInt time);

 
  nValue  nOutput;

  UInt xLoc;
  UInt yLoc;
  UInt zLoc;

  // Status vars subject to change
  bool active;

  Dendrite ProximalBasalDendrite;
  Dendrite DistalBasalDendrites;
  Dendrite ApicalDendrites;

  // Soma Parameters
  nValue SumaDepolarization;
  nValue SumaPlateauTimeConstant;
  nValue SumaResponceTimeConstant;

  nValue (*SumaFunction)(const void *params, void *output);

  // Basal Dendritic Parameters
  nValue DendriticDepolarization; 
  nValue DendriticPlateauTimeConstant;
  nValue DendriticResponceTimeConstant;
  nValue (*BasalFuntion)(const void *params, void *output);

  // Gets or sets a value indicating whether this Cell is active.
  bool GetIsActive();
  bool SetActive(bool value);
  //{
  //    return active;
  //  }
  bool GetWasActive() {
    return false;
  }
  bool GetIsLearning() {
    return false;
  }
  bool GetWasLearning() {
    return false;
  }
  bool GetIsPredicting() {
    return false;
  }
  bool GetWasPredicted() {
    return false;
  }
  int GetNumPredictionSteps() {
    return 0;
  }
  int GetPrevActiveTme() {
    return 0;
  }
  
};



