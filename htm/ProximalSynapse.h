#pragma once
#include "Synapse.h"
#include "MemObject.h"
#include "FastList.h"
#include "Utils.h"
#include "DataSpace.h"

/// Represents a synapse that receives feed-forward input from an input cell.
/// The ProximalSynapse is abstracted to connect to a column output or
/// an input layer's output even if represented with multiple output values
/// The abstraction is refered to as a Proximal Columnar Synapse
class ProximalSynapse:public Synapse {
 public:
    ProximalSynapse(void);
    ~ProximalSynapse(void);

    /// Properties

 public:

     virtual MemObjectType GetMemObjectType() {
	return MOT_PROXIMAL_SYNAPSE;
    }
    // The DataSpace for this synapse's input.
    DataSpace *InputSource;
    DataSpaceRef *RefSource;

    // A single input value point from an input DataSource.
    DataPoint InputPoint;

    // Distance, in this synapse's Region's space, to its input DataPoint.
    float DistanceToInput;

    /// Returns true if this ProximalSynapse is active due to the current input.
    virtual bool GetIsActive();

    bool GetWasPredicted();  
    bool ColumnActive();  

    /// Methods

    /// Initializes a new instance of the ProximalSynapse class and 
    /// sets its input source and initial permanance values.
    /// inputSource: A DataSource (external data source, or another Region) providing source of the input to this synapse.
    /// inputPoint: Coordinates and value index of this synapse's input within the inputSource. 
    /// permanence: Initial permanence value.
    /// distanceToInput: In the Region's coordinates; used by Region::AverageReceptiveFieldSize().
    void Initialize(SynapseParameters * params, DataSpace * inputSource,
		    DataPoint & inputPoint, float permanence,
		    float distanceToInput);
    void Initialize(SynapseParameters * params, DataSpaceRef * inputSource,
		    DataPoint & inputPoint, float permanence,
		    float distanceToInput);
    void Initialize(SynapseParameters * params);
};
