#include "TemporalSpace.h" 
#include "MemManager.h"
#include "Columns.h"
#include "Segment.h"   // Temporary Include to be deleted JSK TODO

#include "Neuron.h"

#include <iostream>
using namespace std;

#include "mpi.h"

//#define CurDBG 1
//#define TDEBUG 1
//#define DEBUGMEMLEAK 1
//#define DEBUG 1
//#define STEPDEBUG
//#define COLBUG
extern int indent;


TemporalSpace::~TemporalSpace(void)
{
  // Delete all columns.
  for (int cy = 0; cy < Height; cy++) {
    for (int cx = 0; cx < Width; cx++)	{
      // Delete the current column.
      delete Columns[(cy * Width) + cx];
    }
  }

  // Delete the array of Column pointers.
  delete Columns;

  // Delete UnionOutputs
  for (int i = 0; i < previousUnionOutputs.size(); i++)	{
    delete(previousUnionOutputs.back());
    previousUnionOutputs.pop_back();
  }
  delete unionPersistence;
}

TemporalSpace::TemporalSpace(NetworkManager * manager,
	       QString & _id,
	       int _uid,
	       RegionType type,
	       Point colGridSize,
	       int hypercolumnDiameter,
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
	       int refProc, bool _vert, int _master)
    :DataSpace(_id)
{
  int i, j, k, idx, proc, sproc;
  Point GridStart(0, 0);
  Point GridEnd(0, 0);

  // REGION VALUES
  Manager = manager;
  Process = process;
  Master = _master;
  RefProc = refProc;
  uid = _uid;
  vert = _vert;
  regiontype = type;
  activeAttention = 0;

  HypercolumnDiameter = hypercolumnDiameter;
  ProximalSynapseParams = proximalSynapseParams;
  DistalSynapseParams = distalSynapseParams;
  PredictionRadius = predictionRadius;
  InhibitionType = inhibitionType;
  InhibitionRadius = inhibitionRadius;
  OverlapWeightRatio = overlapWeightRatio;
  BoostRate = boostRate;
  MaxBoost = maxBoost;
  SpatialLearningStartTime = spatialLearningStartTime;
  SpatialLearningEndTime = spatialLearningEndTime;
  TemporalLearningStartTime = temporalLearningStartTime;
  TemporalLearningEndTime = temporalLearningEndTime;
  BoostingStartTime = boostingStartTime;
  BoostingEndTime = boostingEndTime;

  CellsPerCol = cellsPerCol;
  SegActiveThreshold = segActiveThreshold;
  SegLearningThreshold = segLearningThreshold;    
  NewSynapsesCount = newSynapseCount;
  Min_MinOverlapToReuseSegment = min_MinOverlapToReuseSegment;
  Max_MinOverlapToReuseSegment = max_MinOverlapToReuseSegment;
  PctLocalActivity = pctLocalActivity;
  PctFullAttn = pctFullAttn;
  PctMinAttn  = pctMinAttn;    
  PctInputPerColumn = pctInputPerCol;
  PctMinOverlap = pctMinOverlap;
  HardcodedSpatial = hardcodedSpatial;
  OutputColumnActivity = outputColumnActivity;
  OutputCellActivity = outputCellActivity;

  // Determine number of output values.
  //NumOutputValues = (OutputColumnActivity ? 1 : 0) + (OutputCellActivity ? CellsPerCol : 0);
  NumOutputValues = CellsPerCol;
    
  datavalid = 0;
  Width = (int)(colGridSize.X);
  Height = (int)(colGridSize.Y);

  if(Process == Master) {
#ifdef CurDBG
    cout << Process << ":I'm a Master Temporal Space\n";
    cout << Process << ":TemporalSpace Type " << regiontype << "\n";
#endif
    // Master Region Initialization
    AveReceptiveFieldSemiphore=0;
    AveReceptiveFieldSum=0.0;
    StepDoneSemiphore=0;
    _vert = 1;
    RefProc = Master;

#ifdef CurDBG
    cout << Process << ":Width,Height,NumOutputValues " << Width << "," << Height << "," << NumOutputValues << "\n";
#endif      

    // must contain the columns with there correct RefProc MAYBE

    Columns = new nColumn *[Width * Height];
#ifdef CurDBG      
    cout << Process << ": TemporalSpace::TemporalSpace &Columns[0] "  << &Columns[0] << "\n";
#endif

      
    // initial all Column Output values to 0
    ColumnOutputs = new int [Width * Height * NumOutputValues];
    for(i=0;i<Width*Height*NumOutputValues;i++) {
      ColumnOutputs[i] = 0;
    }

    // initial UnionOutputs
    baseLinePersistence = 10;
    extraPersistence = 5;
    threshold = 5;
    for (int i = 0; i < MAXBACKWARDN; i++)	{
      unionOutputs = new int [Width * Height];
      for(j=0; j<Width*Height; j++) {
	unionOutputs[j] = 0;
      }	
      previousUnionOutputs.push_back(unionOutputs);
    }
    unionPersistence = new int [Width * Height];
    for(i=0; i<Width*Height; i++) {
      unionPersistence[i] = 0;
    }
      
#ifdef CurDBG
    cout << Process << ":Created TemporalSpace Column array ONLY " << Width*Height << " columns\n";       cout << Process << ":Created " << Width*Height << " Columns with INVALID process references!\n";
#endif      
  } else { // not a master region
#ifdef CurDBG
    cout << Process << ":my Master TemporalSpace is " << Master << "\n";
#endif

    Columns = new nColumn *[Width * Height];


#ifdef CurDBG
    cout << Process << ":Master defined as " << Master << "\n";
#endif

    // setup region data structures in process 0 
    //JSK Columns = new Column *[Width * Height];
#ifdef CurDBG
    cout << Process << ": &Columns[0] "  << &Columns[0] << "\n";
#endif
    
    for (int cy = 0; cy < Height; cy++) {
      for (int cx = 0; cx < Width; cx++) {
	Columns[(cy * Width) + cx] = NULL;
      }
    }
    
    // initial all Column Output values to 0  for process 0's shadow region
    ColumnOutputs = new int [Width * Height * NumOutputValues];
    for(i=0;i<Width*Height*NumOutputValues;i++) {
      ColumnOutputs[i] = 0;
    }
  }
#ifdef CurDBG
  cout << Process << ":TemporalSpace::TemporalSpace returning\n";
#endif
}

/// Run one time step iteration for this Region.
///
/// All cells will have their current (last run) state pushed back to be their 
/// new previous state and their new current state reset to no activity.  
/// Then SpatialPooling followed by TemporalPooling is performed for one time step.
void TemporalSpace::Step()
{
  int i, j,proc;
  int buf[10];

#ifdef CurDBG
  cout << Process << ":TemporalSpace::Step starting the Step() procedure\n";
#endif
  if (vert) {
    // if the region is virtual ie rank 0 then we need to call its
    // master region process

    datavalid = 0;
    buf[0] = 0;      // proc id of sending process virtual is rank 0
    buf[1] = 's';
    buf[2] = Master; //fill in uid/proc/rank below in loop
    buf[3] = 0;
    // Layer        id 0-255 norm: 6 horiz layers hippocampus 3
    buf[4] = DATASPACE_TYPE_SPACE_REF;
    buf[5] = 0;
    buf[6] = 0;
    buf[7] = 0;
    buf[8] = 0;		// Cell         id 0-255

    MPI::COMM_WORLD.Ssend(buf, 9, MPI::INT, Master, 0);
#ifdef TDEBUG
    cout << "0:Sent CMD Step to proc " << Master << "\n";
#endif
    return;
  } else {
    if(Process == Master) {
#ifdef TDEBUG
      cout << Process << ":We are the Master region space process\n";
#endif
      StepDoneSemiphore = 1;

      ProcessStep();
      
      StepFinished(Process);  // JSK TODO NEED TO ADD CALL TO REGION STEP
      return;
    }
  }
}

void TemporalSpace::ProcessStep()
{
  //    Column *col;
  //    Cell *cell;

#ifdef STEPDEBUG
    cout << Process << ":TemporalSpace::ProcessStep()\n";
#endif

    // Validate/Reload local copy of input data
#ifdef STEPDEBUG
    cout << Process << ": DataList size " << InputDataList.size() << "\n";
    for(int i =0; i < InputDataList.size(); i++) {
      cout << Process << ":[" << i <<  "]    Proc " << InputDataList[i]->Proc << "\n";
      cout << Process << ":[" << i <<  "]    RefProc " << InputDataList[i]->RefProc <<	"\n";
      cout << Process << ":[" << i <<  "]    uid " << InputDataList[i]->uid <<	", Input Type: ";
      switch(InputParams[i].Type) {
      case PROXIMAL_DENDRITE: cout << "PROXIMAL_DENDRITE\n"; break;
      case BASAL_DENDRITE:    cout << "BASAL_DENDRITE\n"; break;
      case APICAL_DENDRITE:   cout << "APICAL_DENDRITE\n"; break;
      }
    }
#endif

    for (unsigned int i = 0; i < InputDataList.size(); i++) {
#ifdef STEPDEBUG
      cout << Process << ":Region::RefreshData[" << i << "] Delayed " << InputParams[i].Delayed << "\n";
#endif    
      if(InputParams[i].Delayed == false) {
	InputDataList[i]->RefreshData();
      }
    }
#ifdef STEPDEBUG
    cout << Process << ":Region::Refresh Done\n";
#endif

  class actInfo {
  public:
    ~actInfo(void) {}
    actInfo(void) {}
    actInfo(UInt x, UInt y, float v) {
      xLoc  = x;
      yLoc  = y;
      value = v;
    }
    UInt xLoc;
    UInt yLoc;
    float value;
  };

  class actInfo *sortedArray[Width*Height];

  // Neupic calls this overlap
  for(UInt cy=0; cy<Height; cy++) {    //j y
    for(UInt cx=0; cx<Width; cx++) {   //i x
      float activation = Columns[cx+cy*Width]->Boost *
	(float)Columns[cx+cy*Width]->computeStep(InputDataList);      

      // insertion sort list largest value first   Is a list a better
      // implementation as just needs one insertion and can then terminate loop
      // except that list itteration is slower because must follow chain back-
      // word which takes about the same time as the bubble transfers. So No.
      // but could stop after the '24' needed top kth values!!!!
      int idx = cx+cy*Width - 1;

      while(idx >= 0 && activation >= sortedArray[idx]->value) {
	sortedArray[idx+1] = sortedArray[idx];
	idx--;
      }
      sortedArray[idx+1] = new actInfo(cx,cy,activation);
    }
  }

  cout << Process << ":TemporalSpace Step Sorted Array:\n";
  for(UInt i=0;i<Width*Height*NumOutputValues;i++) {
    ColumnOutputs[i] = 0;
  }

  int numActive = (int)(PctLocalActivity*Width*Height);
  cout << Process << ":TemporalSpace PctActivity: " << PctLocalActivity << " Active " << numActive << "\n";    
  for(UInt i=0; i<numActive; i++) {
    cout << Process << ": ";
    std::cout << sortedArray[i]->xLoc << "," << sortedArray[i]->yLoc << ": " << sortedArray[i]->value << "\n";
    ColumnOutputs[sortedArray[i]->yLoc * Width + sortedArray[i]->xLoc] = 1;
      //sortedArray[i]->value;
  }
  for(UInt i=0; i<Width; i++) {
    for(UInt j=0; j<Height; j++) {
      if(ColumnOutputs[i * Width + j] >= 1) {
	for(UInt k=0; k<CellsPerCol; k++) {
	  //Columns[i * Width + j]->Cells[k]->active = true;
	  Columns[i * Width + j]->Cells[k]->SetActive(true);
	}
	cout << "1 ";
      } else {
	for(UInt k=0; k<CellsPerCol; k++) {
	  //Columns[i * Width + j]->Cells[k]->active = false;
	  Columns[i * Width + j]->Cells[k]->SetActive(false);	  
	}
	cout << "0 ";
      }
    }
    cout << "\n";
  }
  cout << "\n";

  for(UInt i=0; i<Width; i++) {
    for(UInt j=0; j<Height; j++) {
      for(UInt k=0; k<1; k++) {
	//cout << Columns[i * Width + j]->Cells[k]->active;;
	nColumn *col = Columns[j + (i * Width)];
	cout << col->GetCellByIndex(k)->GetIsActive();
	//cout << col->Cells[k]->GetIsActive();
	//cout << col->Cells[k]->active;
      }
      cout << " ";
    }
    cout << "\n";
  }
  cout << "\n";  

  for(UInt i=0; i<Width; i++) {
    for(UInt j=0; j<Height; j++) {
      cout << IsCellActive(i,j,0) << " ";
    }
    cout << "\n";
  }  
}

void TemporalSpace::StepFinished(int procId)
{
  cout << Process << ":TemporalSpace " << procId << " StepFinished()\n";  
  if(Process == Master) {
    StepDoneSemiphore--;
#ifdef CurDBG
    cout << Process << ":Process " << procId << " has finished Step()\n";
#endif
    if(StepDoneSemiphore == 0) {
      int buf[10];
      MPI::Status status;

    // if region is used as an Input update column output data
    // before signaling the end of the step.
      
#ifdef CurDBG
      cout << Process << ":Notify head end step has finished\n";
#endif
      buf[0] = Process;          // Sending process rank/id
      buf[1] = 'e';
      buf[2] = 0;	 // Recieving process is the head end
      buf[4] = DATASPACE_TYPE_SPACE_REF;
      buf[5] = 0;
      buf[6] = 0;
      buf[7] = 0;
      buf[8] = 0;

      MPI::COMM_WORLD.Send(buf, 9, MPI::INT, 0, 0); 
    }
  }    
}

// Add an input DataSpaceRef to this Region
// Watch to see if it is an reference to itself
void TemporalSpace::AddInput(DataSpaceRef * _inputDataRef, InputData * _inputDataBuf)
{
    int i, j;
#ifdef CurDBG
    cout << Process << ":TemporalSpace::AddInput: DataSpaceRef Master " << Master << "\n";    
#endif

    if(Process == Master) {
      // Check if this reference is to itself?
      if(_inputDataRef->GetProcess() == Process) {
	//cout << Process << ": ** SELF ** AddInput: Master " << Master << "\n";
      } else {
	//cout << Process << ":AddInput MASTER pushing back DataSpaceRef on RefInputList: " <<
	//_inputDataRef->GetID().toLocal8Bit().constData() << "\n";      	
	RefInputList.push_back(_inputDataRef);
        //cout << Process << ":RefInputList x,y " << _inputDataRef->GetSizeX(Process) << "," << _inputDataRef->GetSizeY(Process) << "\n";
        //cout << Process << ":RefInputList x,y,z uid " << _inputDataRef->SizeX << "," << _inputDataRef->SizeY << "," << _inputDataRef->SizeZ << " " << _inputDataRef->uid << "\n";
	InputDataList.push_back(_inputDataBuf);
      }
    }

    //cout << Process << ":TemporalSpace::AddInput: DataSpaceRef Master " << Master << " returning\n"; fflush(stdout);
}

void TemporalSpace::Initialize()
{
    cout << Process << ":TemporalSpace::Initialize()\n"; fflush(stdout);
    cout << Process << ":RefInputList size " << RefInputList.size() << "\n"; fflush(stdout);  

    ProximalSynapticParams.ConnectedPermanence = ProximalSynapseParams.ConnectedPerm;
    ProximalSynapticParams.InitialPermanence   = ProximalSynapseParams.InitialPermanence;
    ProximalSynapticParams.PermanenceDec       = ProximalSynapseParams.PermanenceDec;
    ProximalSynapticParams.PermanenceInc       = ProximalSynapseParams.PermanenceInc;
    ProximalSynapticParams.PredictedDec        = ProximalSynapseParams.PredictedDec;

    for (int cy = 0; cy < Height; cy++) {
      for (int cx = 0; cx < Width; cx++) {
	Columns[(cy * Width) + cx] = new nColumn(this, &ProximalSynapticParams, cx, cy, CellsPerCol);
	Columns[(cy * Width) + cx]->createProximalSegments(RefInputList,InputRadii,Width,Height);	
      }
    }

//#ifdef COLBUG
    nColumn *c;
    TemporalSpace *ts;

    ts = this;
    cout << Process << ":TEMPORALSPACE - proc " << ts->Process << " ref " << ts->RefProc << " uid " << ts->uid << "\n";
    c = ts->Columns[0];
    cout << Process << ":Temporal Space - Column 0 proc " <<
      c->Process << " ref " << c->RefProc << "\n";
    cout << "W,H " <<
      ts->Width << "," <<
      ts->Height << "\n";
    for (UInt col = 0;
	 col <
	   ts->Width *
	   ts->Height;
	 col++) {
      c = ts->Columns[col];
      //cout << "Col x,y " << c->xLoc << "," << c->yLoc << ":\n";			  
      // only need the first neuron in the column they all have same connects
      Neuron *neuron = c->Cells[0];
      nSegment * seg = (nSegment *)neuron->ProximalBasalDendrite.Segments.GetFirst();

      FastListIter syn_iter(seg->Synapses);
      for (nSynapse * psyn = (nSynapse *) (syn_iter.Reset()); psyn != NULL;
	   psyn = (nSynapse *) (syn_iter.Advance())) {
	//cout << Process << ":syns\n";
	//out << psyn->RefSource->proc;
	//out << psyn->RefSource->uid;
	//out << (int)psyn->RefSource->dataspacetype;			   			    
	//cout << Process << ":s1\n";
	//cout << Process << ": syn coords " << psyn->InputPoint.X << "," << psyn->InputPoint.Y <<"\n";
	//cout << Process << ":s3\n";
      }
    }
//#endif
    
    cout << Process << ":TemporalSpace::Initialized\n"; fflush(stdout);
}


// Add an input DataSpace to this Region
void TemporalSpace::AddInput(DataSpace * _inputDataSpace)
{
    int i, j;

#ifdef CurDBG    
    cout << Process << ":TemporalSpace::AddInput: DataSpace\n";
#endif
    if(Process != Master) {
      // If HardcodedSpatial is true, then there can be only one input DataSpace,
      // and it must be the same size as this Region, and have only 1 value.
      //      _ASSERT((HardcodedSpatial == false)
      //	    || ((InputList.size() == 0)
      //		&& (_inputDataSpace->GetNumValues() == 1)
      //		&& (_inputDataSpace->GetSizeX() == Width)
      //		&& (_inputDataSpace->GetSizeY() == Height)));

      cout << Process << ":AddInput Not a Master pushing back inputDataSpace on InputList\n";      
      InputList.push_back(_inputDataSpace);
    }
#ifdef CurDBG
  cout << Process << ":TemporalSpace::AddInput returning ";
  cout << "data Width,Height " << _inputDataSpace->GetSizeX() << "," << _inputDataSpace->GetSizeY() << "  " << Width << "," << Height << "\n";
#endif
}

/********************************************************************************/
/********************************************************************************/
/********************************************************************************/


/// Methods

// DataSpace Methods

// SPECIAL NOTE - the routine assumes that the ColumnOuput data was updated
// prior to STEP being called and that it is the current updated data during
// a Step when this routine is used.  
bool TemporalSpace::GetIsActive(int _x, int _y, int _index)
{
    nColumn *col = Columns[_x + (_y * Width)];

    //cout << Process << ":TemporalSpace::GetIsActive(" << _x << "," << _y << "," << _index << ") " << col->GetCellByIndex(_index)->GetIsActive() << "\n";
    return col->GetCellByIndex(_index)->GetIsActive();
}

// SPECIAL NOTE - the routine assumes that the ColumnOuput data was updated
// prior to STEP being called and that it is the current updated data during
// a Step when this routine is used.  
int TemporalSpace::GetAllStatus(int _x, int _y, int _index)
{

    cout << Process << ":TemporalSpace::GetAllStatus(" << _x << "," << _y << "," << _index << ")\n";
    return false;
}

void TemporalSpace::GetColActivity(int *buffer, int _x, int _y, int _index)
{
  int x, y, z;
  int t;
#ifdef databug
  int rank = MPI::COMM_WORLD.Get_rank();
  cout << rank << ":GetColActivity\n";
#endif
  
  //cout << Process << ":GetColActivity\n";
  //  _ASSERT((_x >= 0) && (_x < Width));
  //  _ASSERT((_y >= 0) && (_y < Height));
  //  _ASSERT((_index >= 0) && (_index < NumOutputValues));

  for (z = 0; z < _index; z++) {
#ifdef databug
    cout << rank << ":z=" << z << "\n";
#endif
    for (y = 0; y < _y; y++) {
#ifdef databug
      cout << rank << ":R ";
#endif
      for (x = 0; x < _x; x++) {
	//cout << "z,y,x     " << z << "," << y << "," << x << "\n";
	t = ColumnOutputs[x+y*_x+z*_x*_y];
#ifdef databug
	cout << t << " ";
#endif
	buffer[x+y*_x+z*_x*_y] = t;
      }
#ifdef databug
      cout << "\n";
#endif
    }
#ifdef databug    
    cout << "\n";    
#endif
  }
#ifdef databug
  cout << rank << ":GetColActivity returning\n";
#endif
}  

extern MemManager mem_manager;

int TemporalSpace::Validate()
{
  // int i, j;
    if (vert != 1) {
#ifdef DEBUG
    cout << Process << ":Validate -- TemporalSpace not a vertual space return 1\n";
#endif      
      return 1;		// If not a vertual region then just return
    }
    if (datavalid) {
#ifdef DEBUG
      cout << Process << ":Validate -- TemporalSpace data was valid return 0\n";
#endif      
      return 0;		// If the copy of the data is still valid return
    }
#ifdef TRACE
    for(int i = 0; i<indent; i++)  std::cout << "  ";
    std::cout << Process << ": TemporalSpace::Validate() datavalid: " << datavalid << "\n";
    indent++;
#endif  
#ifdef DEBUG
    cout << Process << ":Validate -- TemporalSpace\n";
#endif
    datavalid = 1;

    // *************************************************************************

    // Caller of this routine should be proc 0 view will recieve the data.

    MPI::Status status;
    //  ProximalSynapse *pSyn;
    FastListIter synapse_iter;
    int ibuf[4], num;
    UInt i,j;
    char *cbuf;

#ifdef DEBUG    
    cout << Process << ":Validate vert " << vert << " RefProc " << RefProc << "\n";
#endif

    if (vert != 1)
	return 1;
    // This is only called when we need to update data.  It is
    // called from view or from Region when it is validated.

    int buf[10];
    buf[0] = 0;
    buf[1] = 'C';
    buf[2] = 0;			// Region/Input id 0-255
    // Layer        id 0-255 norm: 6 horiz layers hippocampus 3
    buf[4] = Process;
    buf[5] = RefProc;
    buf[6] = DATASPACE_TYPE_SPACE_REF;
    buf[7] = 0;
    buf[8] = 0;			// Cell         id 0-255
#ifdef TDEBUG
    cout << Process << ":TemporalSpace::Validate() -- mGetColumns\n";
#endif
    //  for (pSyn = (ProximalSynapse*)(synapse_iter.Reset()); pSyn != NULL; pSyn = (ProximalSynapse*)(synapse_iter.Advance())) {
    //    cout << "0:" << pSyn->InputSource << "\n";
    //  }

    MPI::COMM_WORLD.Send(buf, 9, MPI::INT, RefProc, 0);
#ifdef TDEBUG
    cout << "0:Sent 'C' CMD\n";  fflush(stdout);
#endif
    MPI::COMM_WORLD.Recv(ibuf, 2, MPI::INT, RefProc, 0, status);
#ifdef TDEBUG
    cout << "0:Recieved " << ibuf[0] << " elements " << ibuf[1] << " bytes\n";   fflush(stdout);
#endif
    cbuf = (char *)malloc((ibuf[1] + 1) * sizeof(char));
    MPI::COMM_WORLD.Recv(cbuf, ibuf[1] + 1, MPI::CHAR, RefProc, 0, status);
#ifdef DEBUG
    cout << "0:Recieved data\n";
#endif
    //  seg = new Segment();
    QByteArray buffer = QByteArray::fromRawData(cbuf, ibuf[1] + 1);
    QDataStream in(&buffer, QIODevice::ReadOnly);

#ifdef TDEBUGMEMLEAK
    cout << MPI::COMM_WORLD.Get_rank() << ":MOT_SEGMENT COUNT " << mem_manager.GetObjectCount(MOT_SEGMENT) << "\n";
    cout << MPI::COMM_WORLD.Get_rank() << ":MOT_PROXIMAL_SYNAPSE COUNT " << mem_manager.GetObjectCount(MOT_PROXIMAL_SYNAPSE) << "\n";
    cout << MPI::COMM_WORLD.Get_rank() << ":MOT_DISTAL_SYNAPSE COUNT " << mem_manager.GetObjectCount(MOT_DISTAL_SYNAPSE) << "\n";
    cout << MPI::COMM_WORLD.Get_rank() << ":MOT_CELL COUNT " << mem_manager.GetObjectCount(MOT_CELL) << "\n";
    cout << MPI::COMM_WORLD.Get_rank() << ":MOT_FAST_LIST_TRAY COUNT " << mem_manager.GetObjectCount(MOT_FAST_LIST_TRAY) << "\n";
    cout << MPI::COMM_WORLD.Get_rank() << ":mem use " << mem_manager.GetTotalMemUse() << "\n";
    cout << MPI::COMM_WORLD.Get_rank() << ":Columns " << ibuf[0] << "\n";    
#endif

    //#ifdef TRACE
    //    for(int i = 0; i<indent; i++)  std::cout << "  ";
    //    std::cout << Process << ": TemporalSpace::Validate() datavalid: " << datavalid << "\n";
    //#endif  
    

    // Iterate through each column.
    nColumn *column;
    Neuron *cell;
    for (i = 0; i < ibuf[0]; i++) {
      column = Columns[i];
      //cout << MPI::COMM_WORLD.Get_rank() << ":Cells " << GetCellsPerCol() << "\n";    
      // Clear the column's proximal segment.
      // ClearData_ProximalSegment(column->ProximalSegment);

      // Iterate through all cells...   (JSK)
      for (UInt idx = 0; idx < GetCellsPerCol(); idx++) {
	cell = column->GetCellByIndex(idx);
	cell->ProximalBasalDendrite.nOutput = 0;

	//cout << MPI::COMM_WORLD.Get_rank() << ":segments "<<cell->ProximalBasalDendrite.Segments.Count()<<"\n";

	// Clear all of this cell's distal segments...
	//while (cell->Segments.Count() > 0) {
	//  // Clear the column's distal segment.
	//  ClearData_DistalSegment((Segment *) (cell->Segments.GetFirst()));

	//  // Remove and release the current distal segment.
	//  mem_manager.ReleaseObject((Segment *) (cell->Segments.GetFirst()));
	//  cell->Segments.RemoveFirst();
	//}
      }
    }

    for (i = 0; i < ibuf[0]; i++) {
      in >> num;

      //cout << "0: " << num << " synapses in column[" << i << "]'s proximal segment\n";

      column = Columns[i];

      int tmp;
      //Columns[i]->ProximalSegment->Synapses.Clear();

      for (UInt idx = 0; idx < GetCellsPerCol(); idx++) {
	cell = column->GetCellByIndex(idx);
	nSegment *seg = (nSegment *)(cell->ProximalBasalDendrite.Segments.GetFirst());
	seg->Synapses.Clear();      
	//cout << Process << ":Syn start size " << seg->Synapses.Count() << "\n";
      }

      for (j = 0; j < num; j++) { // loop through number of synapses
	int proc, uid;
	float t1, t2;
	SynapticParameters *sp;
	DataSpaceRef *rsrc;
	DataPoint inputPoint;
	fValue distanceToInput;

	// Note ProximalSegments are static and synapses are in general
	// slowly changing
	
	nSynapse *pSyn = (nSynapse *) (mem_manager.GetObject(MOT_NSYNAPSE));
	
	in >> proc;
	in >> uid;
	in >> tmp;
	rsrc = new DataSpaceRef(GetID(), proc, uid, (DataSpaceType) tmp);
	sp = new SynapticParameters();
	// here we are always creating new DataSpaceRef & Parameters
	// I don't think they ever get unallocated which is a memory
	// leak.   Normally these should point to static structures
	// that never change.  
	pSyn->RefSource = rsrc;
	
	in >> inputPoint.X;
	in >> inputPoint.Y;
	in >> inputPoint.Index;
	in >> distanceToInput;
	
	// need Params and Permanence
	in >> t1;		//ConnectedPerm
	in >> t2;		//perminance

	sp->InitialPermanence = column->parameters->InitialPermanence;
	sp->PermanenceDec = column->parameters->PermanenceDec;
	sp->PermanenceInc = column->parameters->PermanenceInc;
	sp->PredictedDec  = column->parameters->PredictedDec;
	
	sp->ConnectedPermanence = t1;
	pSyn->Parameters = sp;
	//pSyn->SetPermanence(t2);
	pSyn->ConnectionStrength = (fValue)t2;
	pSyn->Permanence = (fValue)t2;
	pSyn->InputPoint.X = inputPoint.X;
	pSyn->InputPoint.Y = inputPoint.Y;
	pSyn->InputPoint.Index = inputPoint.Index;
	pSyn->DistanceToInput = distanceToInput;

	for (UInt idx = 0; idx < GetCellsPerCol(); idx++) {
	  cell = column->GetCellByIndex(idx);
	  nSegment *seg = (nSegment *)(cell->ProximalBasalDendrite.Segments.GetFirst());
	  //for(int i = 0; i<indent; i++)  std::cout << "  ";	
	  //cout << Process << ":Syn " << num << " loc " << inputPoint.X << "," <<
	  //  inputPoint.Y << "," << inputPoint.Index << "\n";
	  seg->Synapses.InsertAtEnd(pSyn);
	}
      }

      in >> column->IsActive;
      in >> column->IsInhibited;
      in >> column->MinBoost;
      in >> column->MaxBoost;
      in >> column->Boost;
      in >> column->Overlap;
      in >> column->ActiveDutyCycle;
      in >> column->FastActiveDutyCycle;
      in >> column->_overlapDutyCycle;
      in >> column->maxDutyCycle;
      // MinDutyCycle
      in >> column->_minOverlap;
      in >> column->prevBoostTime;
      in >> column->DesiredLocalActivity;
      in >> tmp; // CellsPerCol or size

      for (j = 0; j < column->size; j++) {	//Cell
	bool b;
	int SegmentCount;

	in >> b;
	//Columns[i]->Cells[j]->SetIsActive(b);
	//Columns[i]->Cells[j]->active = b;
	Columns[i]->Cells[j]->SetActive(b);
	
	in >> b;
	in >> tmp;
	//Columns[i]->Cells[j]->SetIsPredicting(b,tmp);
	//Columns[i]->Cells[j]->_isPredicting = b;
	//Columns[i]->Cells[j]->NumPredictionSteps = tmp;
	in >> b;
	//Columns[i]->Cells[j]->SetIsLearning(b);
	in >> b;
	//Columns[i]->Cells[j]->SetWasActive(b);
	in >> b; //in >> Columns[i]->Cells[j]->WasPredicted;
	in >> b;
	//Columns[i]->Cells[j]->SetWasLearning(b);
	in >> tmp; // in >> Columns[i]->Cells[j]->PrevActiveTime;
	//  NumDistalSegments

	// Need to create a new list of segments.
	in >> SegmentCount;
	//    Columns[i]->Cells[j]->Segments.Clear();
//#ifdef COMMENT_OUT_THIS	
	for (int k = 0; k < SegmentCount; k++) {	//Segment
		int SynapseCount, ActiveSynapseCount, PrevActiveSynapseCount;
		//cout << "0:newSegment count " << SegmentCount << "\n";
		Segment *newSegment =
		    (Segment *) (mem_manager.GetObject(MOT_SEGMENT));
		in >> newSegment->IsActive;
		in >> newSegment->WasActive;
		in >> newSegment->IsSequence;
		in >> newSegment->ActiveConnectedSynapsesCount;
		in >> newSegment->PrevActiveConnectedSynapsesCount;
		in >> newSegment->ActiveLearningSynapsesCount;
		in >> newSegment->PrevActiveLearningSynapsesCount;
		in >> newSegment->InactiveWellConnectedSynapsesCount;
		in >> newSegment->CreationTime;
		in >> newSegment->_numPredictionSteps;
		in >> newSegment->ConnectedSynapsesCount;
		in >> newSegment->PrevConnectedSynapsesCount;
		in >> newSegment->ActiveThreshold;
		in >> newSegment->LearningThreshold;		
		in >> SynapseCount;
		for (int m = 0; m < SynapseCount; m++) {	//Synapses
		    int X, Y, I;
		    DistalSynapse *newSyn =
			(DistalSynapse *) (mem_manager.GetObject
					   (MOT_DISTAL_SYNAPSE));
		    in >> newSyn->IsActive;
		    in >> newSyn->WasActive;
		    in >> newSyn->WasActiveFromLearning;
		    in >> newSyn->IsConnected;
		    in >> newSyn->Permanence;
		    SynapseParameters *newParam = new SynapseParameters();
		    in >> newParam->ConnectedPerm;
		    in >> newParam->InitialPermanence;
		    in >> newParam->PermanenceDec;
		    in >> newParam->PermanenceInc;
		    in >> X;
		    in >> Y;
		    in >> I;
		    // JSK TODO
	   	    //newSyn->InputSource = GetColumn(X,Y)->Cells[I];
		    //cout << "idx " << newSyn->InputSource->GetIndex() << "\n";
		    newSyn->Params = newParam;
		    newSegment->Synapses.InsertAtEnd(newSyn);
		}
		in >> ActiveSynapseCount;
		for (int m = 0; m < ActiveSynapseCount; m++) {	//Synapses
		    int X, Y, I;
		    DistalSynapse *newSyn =
			(DistalSynapse *) (mem_manager.GetObject
					   (MOT_DISTAL_SYNAPSE));
		    in >> newSyn->IsActive;
		    in >> newSyn->WasActive;
		    in >> newSyn->WasActiveFromLearning;
		    in >> newSyn->IsConnected;
		    in >> newSyn->Permanence;
		    SynapseParameters *newParam = new SynapseParameters();
		    in >> newParam->ConnectedPerm;
		    in >> newParam->InitialPermanence;
		    in >> newParam->PermanenceDec;
		    in >> newParam->PermanenceInc;
		    in >> X;
		    in >> Y;
		    in >> I;
		    // must create or get a pointer to a cell in a column [X,Y]
		    // we will only use the x,y positions JSK
		    //cout << "A:X,Y,Width,idx,I" << X << "," << Y  << "," << Width  << "," << X+Y*Width  << "," << I << "\n";

		    newSyn->Params = newParam;
		    newSegment->ActiveSynapses.InsertAtEnd(newSyn);
		}
		in >> PrevActiveSynapseCount;
		for (int m = 0; m < PrevActiveSynapseCount; m++) {	//Synapses
		    int X, Y, I;
		    DistalSynapse *newSyn =
			(DistalSynapse *) (mem_manager.GetObject
					   (MOT_DISTAL_SYNAPSE));
		    in >> newSyn->IsActive;
		    in >> newSyn->WasActive;
		    in >> newSyn->WasActiveFromLearning;
		    in >> newSyn->IsConnected;
		    in >> newSyn->Permanence;
		    SynapseParameters *newParam = new SynapseParameters();
		    in >> newParam->ConnectedPerm;
		    in >> newParam->InitialPermanence;
		    in >> newParam->PermanenceDec;
		    in >> newParam->PermanenceInc;
		    in >> X;
		    in >> Y;
		    in >> I;
		    // must create or get a pointer to a cell in a column [X,Y]
		    // we will only use the x,y positions JSK
		    //cout << "B:X,Y,Width,idx,I" << X << "," << Y  << "," << Width  << "," << X+Y*Width  << "," << I << "\n";

		    // JSK TODO
		    //newSyn->InputSource = GetColumn(X,Y)->Cells[I];
		    //cout << "P idx " << newSyn->InputSource->GetIndex() << "\n";
		    newSyn->Params = newParam;
		    newSegment->PrevActiveSynapses.InsertAtEnd(newSyn);
		}
		//Columns[i]->Cells[j]->Segments.InsertAtEnd(newSegment);
		//cout << "0:newSegment inserted synapse count "
		//     << SynapseCount << "\n";
	}
//#endif //COMMENT_OUT_THIS		
      }
      //cout << "0:Boost " << Columns[i]->Boost << " Active " << Columns[i]->IsActive << " Inhibited " << Columns[i]->IsInhibited <<"\n";
      //cout << "0:Overlap " << Columns[i]->Overlap << " ActiveDuty " << Columns[i]->ActiveDutyCycle << " minOverlap " << Columns[i]->_minOverlap <<"\n";
    }

    free(cbuf);

#ifdef TRACE
    indent--;
#endif      

    return 1;
}


void TemporalSpace::Check(void)
{
    MPI::Status status;
    int ibuf[4];
    int buf[10];

#ifdef TDEBUG
    cout << Process << ":TemporalSpace::Check to " << RefProc << "\n"; fflush(stdout);
#endif    

    if (vert) {
	datavalid = 0;
	buf[0] = Process; // id of sending process
	buf[1] = '?';
	buf[2] = RefProc; // id of recieving process
	buf[3] = 0;
	// Layer        id 0-255 norm: 6 horiz layers hippocampus 3
	buf[4] = DATASPACE_TYPE_SPACE_REF;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = 0;
	buf[8] = 0;		// Cell         id 0-255
	MPI::COMM_WORLD.Send(buf, 9, MPI::INT, RefProc, 0);
#ifdef TDEBUG
	cout << "0:Sent CHECK CMD to proc " << RefProc << "\n";
#endif
	MPI::COMM_WORLD.Recv(ibuf, 1, MPI::INT, RefProc, 0, status);
	return;
    } else {
#ifdef TDEBUG
      int i,j;
      if(Process != Master) {
#ifdef TDEBUG
	cout << Process << ":CHECK non-virtual region space\n";
#endif
      } else {
#ifdef TDEBUG
	cout << Process << ":CHECK CMD non-virtual master region space " << RefProc << "\n";
#endif
      }
#endif      
    }
}


bool TemporalSpace::IsCellActive(int _x, int _y, int _index)
{
    nColumn *col = Columns[_x + (_y * Width)];

    // Return value representing activity of the column's cell with the given _index.
    return col->GetCellByIndex(_index)->GetIsActive();
}

bool TemporalSpace::IsCellPredicted(int _x, int _y, int _index)
{
  //    nColumn *col = Columns[_x + (_y * Width)];

    // Return value representing prediction of the column's cell with the given _index.
    //return col->GetCellByIndex(_index)->GetIsPredicting();
  return 0;
}

bool TemporalSpace::IsCellLearning(int _x, int _y, int _index)
{
  //    nColumn *col = Columns[_x + (_y * Width)];

    // Return value representing prediction of the column's cell with the given _index.
    //return col->GetCellByIndex(_index)->GetIsLearning();
  return 0;
}

Neuron *TemporalSpace::GetCell(UInt _x, UInt _y, UInt _index)
{
    
    nColumn *col = Columns[_x + (_y * Width)];

    // Return pointer to the given column's cell with the given _index.
    return col->GetCellByIndex(_index);
}
