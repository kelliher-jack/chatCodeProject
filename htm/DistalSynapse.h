#pragma once
#include "Synapse.h"
#include "MemObject.h"
#include "FastList.h"

class Cell;

/// A data structure representing a distal synapse. Contains a permanence value and the 
/// source input to a lower input cell.  
class DistalSynapse:public Synapse {
 public:
    DistalSynapse(void);
    ~DistalSynapse(void);

    /// Properties

 public:

    /// A single input from a neighbour Cell.
     Cell * InputSource;

 public:

     virtual MemObjectType GetMemObjectType() {
	return MOT_DISTAL_SYNAPSE;
    }
    Cell *GetInputSource() {
	return InputSource;
    }

    Cell *GetPresynapticCell() {
	return InputSource;
    }  

    /// Returns true if this DistalSynapse is active due to the current input.
    virtual bool GetIsActive();
    virtual bool ColumnActive();  

    /// Returns true if this DistalSynapse was active due to the previous input at t-1. 
    virtual bool GetWasActive();

    /// Returns true if this DistalSynapse was active due to the input
    /// previously being in a learning state. 
    virtual bool GetWasActiveFromLearning();

    virtual bool GetWasLearning();

    /// Returns true if this DistalSynapse is active due to the input
    /// curently being in a learning state. 
    virtual bool GetIsActiveFromLearning();

    /// Methods

    /// Initializes a new instance of the DistalSynapse class and 
    /// sets its input source and initial permanance values.
    /// inputSrc: An object providing source of the input to this synapse 
    /// (a Column's Cell).
    /// permanence: Initial permanence value.
    void Initialize(SynapseParameters * params, Cell * inputSrc,
		    float permanence);
    void Initialize(SynapseParameters * params);
};
