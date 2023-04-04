#pragma once
#include "Utils.h"
#include "MemObject.h"
#include "FastList.h"
#include "MemManager.h"
#include "Neuron.h"

#include <vector>

typedef class TemporalSpace    TemporalSpace;

class nColumn:public MemObject {
 public:
  ~nColumn(void);
  nColumn(void);  
  nColumn(TemporalSpace * _space, SynapticParameters *_params,UInt xLoc, UInt yLoc, UInt size);
  nColumn(TemporalSpace * _space, UInt xLoc, UInt yLoc, UInt size);  
  MemObjectType GetMemObjectType() {
    return MOT_COLUMN;
  }

  void inhibitColumn(nValue strength);
    
  void addProximalSynapse(DataSpaceRef *inputSource,
			  DataPoint &inputPoint,
			  fValue permanence,
			  fValue distanceToInput);

  void createProximalSegments(std::vector<DataSpaceRef *> &refInputList, std::vector<int> &inputRadii,UInt sizeX,UInt sizeY);

  UInt computeStep(std::vector<DataSpaceRef *> &refInputList);
  UInt computeStep(std::vector<InputData *> InputList);  
  
  //    Segment *mGetProximalSegment();

  int SumInputVolume;
  double _minOverlap;
  float Overlap;
  float PredictedOverlap;
  float TotalOverlap;
  float WeightActive;
  float WeightPredictedActive;
      
  int Process;
  int RefProc;
  int uid;

  UInt xLoc;
  UInt yLoc;
  UInt size;

  UInt ActiveSynapses;
  nSegment *ProximalSegment;

  TemporalSpace *temporalSpace;

  Neuron **Cells;

  nValue inhibition;

  SynapticParameters *parameters;

  // TemporalSpace Column parameters
  fValue PctMinOverlap;
  fValue PctInputPerColumn;

  // ---------------- OTHER VARS -----------------
    
  float _overlapDutyCycle;
  float ActiveDutyCycle, FastActiveDutyCycle, maxDutyCycle, MinBoost,
    MaxBoost, Boost;
  bool IsActive, IsInhibited, IsPredicted;
  int prevBoostTime;

  //    std::vector < SegmentUpdateInfo * >matchingSegmentsCurrent;
  //    std::vector < SegmentUpdateInfo * >matchingSegmentsPrevious;  

  int DesiredLocalActivity;
  int MinOverlapToReuseSegment;

  //    std::vector < Segment * > GetDistalMatchingSegments();


  /// Methods

  float GetBoost() { return Boost; }

  //    void GetBestMatchingCell(int numPredictionSteps, bool previous,
  //    Cell * &bestCell, Segment * &bestSegment);
  void ComputeOverlap();
  void DetermineDesiredLocalActivity();
  void ComputeColumnInhibition(int type);
  void AdaptPermanences();
  void BoostPermanences(float scale);
  void UpdateDutyCycles();
  void PerformBoosting();
  fValue DetermineMaxDutyCycle();
  void UpdateActiveDutyCycle();
  void UpdateOverlapDutyCycle();
  Neuron *GetCellByIndex(UInt _idx);

  bool GetIsActive();
};
