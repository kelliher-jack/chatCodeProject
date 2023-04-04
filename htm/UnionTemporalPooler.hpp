#include <cstring>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <list>

#include <nupic/math/SparseBinaryMatrix.hpp>
#include <nupic/math/SparseMatrix.hpp>
#include <nupic/proto/SpatialPoolerProto.capnp.h>
#include <nupic/types/Serializable.hpp>
#include <nupic/types/Types.hpp>

#include "SpatialPooler.hpp"

#define TIE_BREAKER_FACTOR 0.0001
#define TARGET_EXC_LEVEL 10.0

namespace nupic
{

  namespace algorithms
  {

    namespace union_temporal_pooler
    {

      using namespace std;

      class UnionTemporalPooler :
        public nupic::algorithms::spatial_pooler::SpatialPooler
      {
      public:
	UnionTemporalPooler();
	UnionTemporalPooler(vector<UInt> inputDimensions,
			    vector<UInt> columnDimensions,
			    UInt potentialRadius=16,
			    Real potentialPct=0.5,
			    bool globalInhibition=true,
			    Real localAreaDensity=-1.0,
			    UInt numActiveColumnsPerInhArea=10,
			    UInt stimulusThreshold=0,
			    Real synPermInactiveDec=0.008,
			    Real synPermActiveInc=0.05,
			    Real synPermConnected=0.1,
			    Real minPctOverlapDutyCycles=0.001,
			    UInt dutyCyclePeriod=1000,
			    Real boostStrength=0.0,
			    Int seed=1,
			    UInt spVerbosity=0,
			    bool wrapAround=true,
			    Real activeOverlapWeight=1.0,
			    Real predictedActiveOverlapWeight=0.0,
			    Real maxUnionActivity=0.20,
			    //exciteFunctionType='Fixed',
			    //decayFunctionType='NoDecay',
			    Real decayTimeConst=20.0,
			    Real synPermPredActiveInc=0.0,
			    Real synPermPreviousPredActiveInc=0.0);

	void initialize(vector<UInt> inputDimensions,
			vector<UInt> columnDimensions,
			UInt potentialRadius=16,
			Real potentialPct=0.5,
			bool globalInhibition=true,
			Real localAreaDensity=-1.0,
			UInt numActiveColumnsPerInhArea=10,
			UInt stimulusThreshold=0,
			Real synPermInactiveDec=0.01,
			Real synPermActiveInc=0.1,
			Real synPermConnected=0.1,
			Real minPctOverlapDutyCycles=0.001,
			UInt dutyCyclePeriod=1000,
			Real boostStrength=0.0,
			Int seed=1,
			UInt spVerbosity=0,
			bool wrapAround=true,
			Real activeOverlapWeight=1.0,
			Real predictedActiveOverlapWeight=0.0,
			Real maxUnionActivity=0.20,
			Real decayTimeConst=20.0,
			Real synPermPredActiveInc=0.0,
			Real synPermPreviousPredActiveInc=0.0,
			UInt historyLength=0,
			UInt minHistory=0 );
	

	void compute(UInt activeInput[], UInt predictedActiveInput[], bool learn);
	vector<UInt> getUnionSDR();

	void exciteInit(UInt xMidpoint=5, UInt minValue=10, UInt maxValue=20, UInt steepness=1);

	void decayInit(Real time_constant=10.0);

      protected:

	Real _lambda_constant;
	UInt _xMidpoint;
	UInt _maxValue;
	UInt _minValue;
	UInt _steepness;

	vector<Real> excite(vector<Real> &currentActivation, vector<UInt> inputs, vector<UInt> indices);
	vector<Real> _decayFunction(vector<Real> initActivationLevel, vector<UInt> timeSinceActivation);
	
	void _decayPoolingActivation();
	vector<Real> _addToPoolingActivation(vector<UInt> activeCells, vector<UInt> overlaps);
	vector<UInt> _getMostActiveCells();
	void _adaptSynapses(UInt inputVector[], vector<UInt> activeColumns, Real synPermActiveInc, Real synPermInactiveDec);

	vector<UInt> _overlapsActive;
	vector<UInt> _overlapsPredictedActive;

	UInt _maxUnionCells;
	vector<Real> _poolingActivation;
	vector<Real>  _poolingActivation_tieBreaker;
	vector<Real>  _poolingActivationInitLevel;
	vector<UInt>  _poolingTimer;
	vector<UInt>  _unionSDR;
	vector<UInt>  _preActiveInput;
	vector<UInt>  _activeCells;

	list<UInt *> _prePredictedActiveInput;
	vector<UInt>  _predictedActiveInput;	
	
	Real _poolingActivationlowerBound;
	Real _activeOverlapWeight;
	Real _predictedActiveOverlapWeight;
	Real _maxUnionActivity;
	//_exciteFunctionType;
	//_decayFunctionType;
	Real  _synPermPredActiveInc;
	Real  _synPermPreviousPredActiveInc;
	UInt _historyLength;
	UInt _minHistory;
	
      };
    }
  }
}
