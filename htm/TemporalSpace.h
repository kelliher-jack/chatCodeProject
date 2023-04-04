#pragma once
#include <QtCore/QStringList>
#include "Columns.h"
#include "InputSpace.h"
#include "SegmentUpdateInfo.h"
#include "DataSpace.h"
#include "Synapse.h"
#include "InputData.h"
#include "Input.h"
#include "Region.h"

#include <list>

#include <nupic/types/Types.hpp>
#include "SpatialPooler.hpp"
#include "ApicalTiebreakTemporalMemory.hpp"

#define APICALTIEBREAK 1

#define MAXBACKWARDN 10

//using namespace nupic;
//using namespace nupic::algorithms::spatial_pooler;
//using namespace nupic::experimental::apical_tiebreak_temporal_memory;

class NetworkManager;
class Cell;

//enum InhibitionTypeEnum
//{
//      INHIBITION_TYPE_AUTOMATIC = 0,
//      INHIBITION_TYPE_RADIUS = 1
//};

//enum RegionType {
//  TEMPORAL_POOLING = 0,
//  SPACIAL_POOLING  = 1,
//  SEQUENCE_POOLING = 2,
//  UNION_POOLING = 3  
//};


class TemporalSpace:public DataSpace {
//class TemporalSpace {
  public:
    ~TemporalSpace(void);

    /// Properties

    int AveReceptiveFieldSemiphore;
    int StepDoneSemiphore;
    float AveReceptiveFieldSum;
    RegionType regiontype;

    NetworkManager *Manager;

    Input input;

    nColumn **Columns;
    int *ColumnOutputs;

    int CellsPerCol;

    int SegActiveThreshold;
    int SegLearningThreshold;  

    bool HardcodedSpatial;
    bool SpatialLearning;
    bool TemporalLearning;

    // Determines whether InhibitionRadius uses a set given radius,
    // or is automatcially determined based on average receptive field size.
    InhibitionTypeEnum InhibitionType;

    // spatial pooling inhibition radius determines how many columns to include
    float InhibitionRadius;

    // Furthest number of columns away (in this Region's Column grid space) to allow new distal 
    // synapse connections.  If set to 0 then there is no restriction and connections
    // can form between any two columns in the region.
    int PredictionRadius;

    // The number of new distal synapses added to segments if no matching ones are found 
    // during learning.
    int NewSynapsesCount;

    // This parameter determines whether a segment will be considered a match to activity. It may be considered a match if at least
    // this number of the segment's synapses match the actvity. The segment will then be re-used to represent that activity, with new syanpses
    // added to fill out the pattern. The lower this number, the more patterns will be added to a single segment, which can be very bad because
    // the same cell is thus used to represent an input in diffrent contexts, and also if the ratio of PermanenceInc to PermanenceDec
    // is such that multiple patterns cannot be supported on one synapse, so all but 1 will generally remain disconnected, so predictions are never made.
    // These are the minimum and maximum values of a range. Each individual column is given a different MinOverlapToReuseSegment value from within this range.
    int Min_MinOverlapToReuseSegment, Max_MinOverlapToReuseSegment;

    // Percent of input bits each Column will have potential proximal (spatial) 
    // synapses for.
    float PctInputPerColumn;

    // Minimum percent of column's proximal synapses that must be active for column 
    // to be considered during spatial pooling inhibition.  This value helps set the
    // minimum column overlap value during region run.
    float PctMinOverlap;

    // Approximate percent of Columns within average receptive field radius to be 
    // winners after spatial pooling inhibition.
    float PctLocalActivity;

    // The maximum allowed Boost value. Setting a max Boost value prevents competition
    // for activation from continuing indefinitely, and so facilitates stabilization of representations.
    float MaxBoost;

    // The amount that is added to a Column's Boost value in a single time step, when it is being boosted.
    float BoostRate;

    // ration of active overlap weight to predicted overlap weight in union pooling
    float OverlapWeightRatio;

    float PctFullAttn;
    float PctMinAttn;

    // Start and end times for learning  -1 for from beginning or to end
    // 0 for end time means no learning of that type will take place
    int SpatialLearningStartTime, SpatialLearningEndTime,
	TemporalLearningStartTime, TemporalLearningEndTime,
	BoostingStartTime, BoostingEndTime;

    // Whether this Region will output the activity of the column as a whole, and of each Cell individually.
    bool OutputColumnActivity, OutputCellActivity;

    // The dimensions of the Region's Column grid, Width x Height.
    int Width, Height;

    // The diameter of a hypercolumn in this Region. Defaults to 1.
    int HypercolumnDiameter;

    // This Region's synapse parameters.(old style) & synaptic (new)
    SynapseParameters ProximalSynapseParams, DistalSynapseParams;
    SynapticParameters ProximalSynapticParams, DistalSynapticParams;  

    // The number of output values per column of this Region. If OutputCellActivity is true,
    // then this number will include the number of cells. If OutputColumnActivity is true, then
    // this number will include one value representing the activity of the column as a whole.
    int NumOutputValues;

    // The ID strings of each of this Region's input DataSpaces.
    std::vector < QString > InputIDs;

     // The input radius corresponding to each input DataSpace.
     // Furthest number of hypercolumns away (in the input DataSpace's grid space) to allow proximal 
     // synapse connections from the corresponding input DataSpace. If set to -1 then there is no restriction 
     // and connections can form from any input value.
     std::vector < int >InputRadii;
     std::vector < Input >InputParams;     

     // A list of pointers to each of this Region's input DataSpaces.
     std::vector < DataSpace * >InputList;
     std::vector < DataSpaceRef * >RefInputList;	// Process Refs only
     std::vector < InputData * >InputDataList;	// local input data bufs

     // New temporal mem algo numenta vars
     std::vector < Cell * >activeCellsCurrent;
     std::vector < Cell * >activeCellsPrevious;
     std::vector < Cell * >winnerCellsCurrent;
     std::vector < Cell * >winnerCellsPrevious;
     std::vector < SegmentUpdateInfo * >activeSegmentsCurrent;  
     std::vector < SegmentUpdateInfo * >activeSegmentsPrevious;  
  

     bool activeAttention;

     // Union Pooler algo vars
     int * unionOutputs;
     int * unionPersistence;
     int * overlapPredictedActive;
     std::vector <int *> previousUnionOutputs;
     int baseLinePersistence;
     int extraPersistence;
     int threshold;

    // Statistics

    // Increments at every time step.
    float StepCounter;

    // For recording feature detector statistics.
    int fd_numActiveCols, fd_missingSynapesCount, fd_extraSynapsesCount;

    // Constructor

    // Initializes a new instance of the Region class.
    //
    // colGridSize: Point structure that represents the 
    //     region size in columns (ColumnSizeX * ColumnSizeY).
    // pctInputPerCol: The percent of input bits each column has potential
    //     synapses for (PctInputCol).
    // pctMinOverlap: The minimum percent of column's proximal synapses
    //     that must be active for a column to be even be considered during spatial 
    //     pooling.
    // predictionRadius: Furthest number of columns away to allow
    //     distal synapses from each column/cell.
    // pctLocalActivity: Approximate percent of Columns within inhibition
    //     radius to be winners after spatial inhibition.
    // maxBoost: The maximum allowed Boost value. Setting a max Boost value prevents 
    //     competition for activation from continuing indefinitely, and so 
    //     facilitates stabilization of representations.
    // cellsPerCol: The number of context learning cells per column.
    // segActiveThreshold: The minimum number of synapses that must be 
    //     active for a segment to fire.
    // newSynapseCount: The number of new distal synapses added if
    //     no matching ones found during learning.
    //
    // Prior to receiving any inputs, the region is initialized by computing a list of
    // initial potential synapses for each column. This consists of a random set of 
    // inputs selected from the input space. Each input is represented by a synapse 
    // and assigned a random permanence value. The random permanence values are chosen 
    // with two criteria. First, the values are chosen to be in a small range around 
    // connectedPerm (the minimum permanence value at which a synapse is considered 
    // "connected"). This enables potential synapses to become connected (or 
    // disconnected) after a small number of training iterations. Second, each column 
    // has a natural center over the input region, and the permanence values have a bias
    // towards this center (they have higher values near the center).
    // 
    // In addition to this Uwe added a concept of Input Radius, which is an 
    // additional parameter to control how far away synapse connections can be made 
    // instead of allowing connections anywhere.  The reason for this is that in the
    // case of video images I wanted to experiment with forcing each Column to only
    // learn on a small section of the total input to more effectively learn lines or 
    // corners in a small section without being 'distracted' by learning larger patterns
    // in the overall input space (which hopefully higher hierarchical Regions would 
    // handle more successfully).  Passing in -1 for input radius will mean no restriction.

    TemporalSpace(NetworkManager * manager,
	    QString & _id,
	    int uid, RegionType type,
	    Point colGridSize, int hypercolumnDiameter,
	    SynapseParameters proximalSynapseParams,
	    SynapseParameters distalSynapseParams, float pctInputPerCol,
	    float pctMinOverlap, int predictionRadius,
	    InhibitionTypeEnum inhibitionType, int inhibitionRadius,
	    float overlapWeightRatio, float pctFullAttn, float pctMinAttn,
	    float pctLocalActivity, float boostRate, float maxBoost,
	    int spatialLearningStartTime, int spatialLearningEndTime,
	    int temporalLearningStartTime, int temporalLearningEndTime,
	    int boostingStartTime, int boostingEndTime, int cellsPerCol,
	    int segActiveThreshold, int segLearningThreshold,
	    int newSynapseCount,
	    int min_MinOverlapToReuseSegment,
	    int max_MinOverlapToReuseSegment, bool hardcodedSpatial,
	    bool outputColumnActivity, bool outputCellActivity, int process,
	    int refProc, bool _vert, int _master);

    /// Methods

    // DataSpace Methods

    DataSpaceType GetDataSpaceType() {
	return DATASPACE_TYPE_SPACE_REF;
    }
    int GetSizeX() {
	return Width;
    }
    int GetSizeY() {
	return Height;
    }
    int GetNumValues() {
	return NumOutputValues;
    }
    int GetHypercolumnDiameter() {
	return HypercolumnDiameter;
    }

    int GetProcess() {
	return RefProc;
    }
    int GetUID() {
	return uid;
    }

    bool GetIsActive(int _x, int _y, int _index);
    int  GetAllStatus(int _x, int _y, int _index);
    void GetColActivity(int *buffer, int _x, int _y, int _index);
    int Validate();

    // Add an input DataSpace to this Region
    void AddInput(DataSpace * _inputDataSpace);
    void AddInput(DataSpaceRef * _inputDataRef, InputData * DataBuf);

    NetworkManager *GetManager() {
	return Manager;
    }

    bool vert;
    bool datavalid;
    bool regionIsAnInput;
    int uid;
    int Process;		// process that created Region and owns it
    int RefProc;		// if root process then ref to actural Region data process
    int Master;                 // process that contains the Master Region

    int Node;

    int sindent;

    float GetMaxBoost() {
	return MaxBoost;
    }
    float GetBoostRate() {
	return BoostRate;
    }
    int GetSpatialLearningStartTime() {
	return SpatialLearningStartTime;
    }
    int GetSpatialLearningEndTime() {
	return SpatialLearningEndTime;
    }
    int GetTemporalLearningStartTime() {
	return TemporalLearningStartTime;
    }
    int GetTemporalLearningEndTime() {
	return TemporalLearningEndTime;
    }
    int GetBoostingStartTime() {
	return BoostingStartTime;
    }
    int GetBoostingEndTime() {
	return BoostingEndTime;
    }

    // Determine whether a particular cell in this Region is active, predicted or learning.
    bool IsCellActive(int _x, int _y, int _index);
    bool IsCellPredicted(int _x, int _y, int _index);
    bool IsCellLearning(int _x, int _y, int _index);

    Neuron *GetCell(UInt _x, UInt _y, UInt _index);

    int GetStepCounter() {
	return StepCounter;
    }

    // Called after adding all inputs to this Region.
    void Initialize();

    // Performs spatial pooling for the current input in this Region.
    //
    // The result will be a subset of Columns being set as active as well
    // as (proximal) synapses in all Columns having updated permanences and boosts, and 
    // the Region will update inhibitionRadius.

    void PerformSpatialPooling(bool learn);

    // Modified SpatialPooling for temporal union pooling layers
    //     change so inputs to each column are a weight average of active and
    //     predictedactive inputs:   overlapActive = calculateOverlap(activeInput)
    //     overlapPredictedActive = calculateOverlap(predictedActiveInput)
    //     totalOverlap = overlapActive * weightActive + overlapPredictedActive *
    //       weightPredictedActive

    void PerformUnionPooling(bool learn);

    // Performs temporal pooling based on the current spatial pooler output.
    //
    // From the Numenta white paper:
    // The input to this code is activeColumns(t), as computed by the spatial pooler. 
    // The code computes the active and predictive state for each cell at the current 
    // timestep, t. The boolean OR of the active and predictive states for each cell 
    // forms the output of the temporal pooler for the next level.
    // 

  //    void activatePredictedColumn(Column *column);
  //    void burstColumn(Column *column);
  //    void punishPredictedColumn(Column *column);
  //    Cell *leastUsedCell(Column *column);
  //    SegmentUpdateInfo *bestMatchingSegment(Column *column);
    void growSynapses(SegmentUpdateInfo *segment, int newSynapseCount);
  
    void PerformTemporalMemory();

    void PerformSequencePrediction();

    // Get a pointer to the Column at the specified column grid coordinate.
    nColumn *GetColumn(int x, int y) {return Columns[x+y*Width];}
    int GetCellsPerCol() {return CellsPerCol;}

    // The radius of the average connected receptive field size of all the columns. 
    // The connected receptive field size of a column includes only the connected 
    // synapses (those with permanence values >= connectedPerm). This is used to 
    // determine the extent of lateral inhibition between columns.

    float AverageReceptiveFieldSize();

    // Return true if the given Column has an overlap value that is at least the
    // k'th largest amongst all neighboring columns within inhibitionRadius.
    // This function is effectively determining which columns are to be inhibited 
    // during the spatial pooling procedure of the region.
  //    bool IsWithinKthScore(Column * col, int k);

    // Update the values of the inputData for this <see cref="Region"/> by copying row 
    // references from the specified newInput parameter.
    // inputArray: 2d Array used for next Region time step. 
    // The newInput array must have the same shape as the original inputData.
    void SetInput(int *inputArray, int width, int height);

    // Run one time step iteration for this Region.
    void Step();
    void ProcessStep();
    void OutputData();
    void Check(void);

    void ClearData_ProximalSegment(Segment * _segment);
    void ClearData_DistalSegment(Segment * _segment);

    // Statistics

    // Sets statistics values to 0.
    void InitializeStatisticParameters();

    // Updates statistics values.
    void ComputeBasicStatistics();
    void ComputeColumnAccuracy();
    void LoadData(char *buffer, int startX, int endX, int startY, int endY, int idx);
    void StepFinished(int procId);
};
