#include "Columns.h"
#include "Neuron.h"
#include <math.h>
#include <random>
#include "TemporalSpace.h"

#include "mpi.h"

//#define CDBG 1
//#define BUG 1

//#define TRACE1 1
//#define TRACE 1
extern int indent;

#include <iostream>
using namespace std;

extern MemManager mem_manager;

double normalgDistribution (double mu, double sigma, int callertype, int process)
{
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand() / RAND_MAX) * 2;
      U2 = -1 + ((double) rand() / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}

nColumn::~nColumn(void)
{
}

nColumn::nColumn(void)
{
}

nColumn::nColumn(TemporalSpace * _space, SynapticParameters *_params, UInt _xLoc, UInt _yLoc, UInt _size)
{
#ifdef TRACE
    for(int i = 0; i<indent; i++)  std::cout << "  ";
    std::cout << MPI::COMM_WORLD.Get_rank() << ": nColumn::nColumn(_params) " << _xLoc << "," << _yLoc << "\n";
    indent++;
#endif  
  
  temporalSpace = _space;
  xLoc = _xLoc;
  yLoc = _yLoc;
  size = _size;

  //  Neuron *neuron;
  //  for(UInt i=0; i < _size; i++) {
    //    neuron = (Neuron *)mem_manager.GetObject(MOT_NEURON);
    //    neuron->initialize(xLoc,yLoc,i);
    //    Neurons.InsertAtEnd(neuron);    
  //  }

  // Create each of this Column's Neuron Cells.
  Cells = new Neuron *[_size];
  Neuron *neuron;
  for (int i = 0; i < _size; i++) {
    neuron = (Neuron *)mem_manager.GetObject(MOT_NEURON);
    neuron->initialize(this,xLoc,yLoc,i);    
    Cells[i] = neuron;
  }

  Process = _space->Process;
  RefProc = _space->RefProc;
  uid = _space->uid;

  parameters = _params;
#ifdef TRACE
    for(int i = 0; i<indent; i++)  std::cout << "  ";
    std::cout << MPI::COMM_WORLD.Get_rank() << ":params connected " <<
      parameters->ConnectedPermanence << " init " <<
      parameters->InitialPermanence << " Dec " <<
      parameters->PermanenceDec << " Inc " <<
      parameters->PermanenceInc << " Pred Dec " <<            
      parameters->PredictedDec << "\n";
#endif
  
  PctMinOverlap     = 0.1f;
  PctInputPerColumn = 0.5f;

  const float BoostVariance = 0.01f;

  Boost = 1.0f + ((float)rand() / (float)RAND_MAX) * BoostVariance;
  

#ifdef TRACE
  indent--;
#endif
}

nColumn::nColumn(TemporalSpace * _space, UInt _xLoc, UInt _yLoc, UInt _size)
{
  //  Neuron *neuron;
  //  for(UInt i=0; i < _size; i++) {
  //    neuron = (Neuron *)mem_manager.GetObject(MOT_NEURON);
  //    neuron->initialize(xLoc,yLoc,i);
  //    Neurons.InsertAtEnd(neuron);    
  //  }

#ifdef TRACE
    for(int i = 0; i<indent; i++)  std::cout << "  ";
    std::cout << MPI::COMM_WORLD.Get_rank() << ": nColumn::Column()\n";
    indent++;
#endif    

  // Create each of this Column's Neuron Cells.
  Cells = new Neuron *[_size];
  Neuron *neuron;
  for (int i = 0; i < _size; i++) {
    neuron = (Neuron *)mem_manager.GetObject(MOT_NEURON);
    neuron->initialize(this,xLoc,yLoc,i);    
    Cells[i] = neuron;
  }
  
  temporalSpace = _space;
  xLoc = _xLoc;
  yLoc = _yLoc;
  size = _size;

  PctMinOverlap     = 0.1f;
  PctInputPerColumn = 0.5f;

#ifdef TRACE
  indent--;
#endif
}

void nColumn::inhibitColumn(nValue strength)
{

}

void nColumn::addProximalSynapse(DataSpaceRef *inputSource,
			  DataPoint &inputPoint,
			  fValue permanence,
			  fValue distanceToInput)
{
#ifdef CDBG
  cout << MPI::COMM_WORLD.Get_rank() << ": AddProximalSynapse REF " << inputPoint.X << "," << inputPoint.Y << " permanence " << permanence << "\n";
#endif
  for (int i = 0; i < size; i++) {
    Cells[i]->addSynapse(PROXIMAL,0,parameters,inputSource,inputPoint,permanence,distanceToInput);
  }  
}


void nColumn::createProximalSegments(std::vector<DataSpaceRef *> &refInputList, std::vector<int> &inputRadii,UInt sizeX,UInt sizeY)
{
  DataSpaceRef *curInput;
  Area inputAreaHcols, inputAreaCols;
  int curInputVolume, synapsesPerSegment;
  int inputRadius;
  float dX, dY, distanceToInput_SrcSpace, distanceToInput_DstSpace;
  float srcHcolX, srcHcolY;

  // Initialize values.
  SumInputVolume = 0;
  _minOverlap = 0;

  // Determine this Column's hypercolumn coordinates.
  int destHcolX = xLoc;
  int destHcolY = yLoc;

#ifdef BUG
  //cout << "createProximalSegments: x,y loc " << xLoc << "," << yLoc << " x,y size " << sizeX << "," << sizeY << "\n";
#endif  

  // Determine the center of this Column's hypercolumn, in this Column's
  // Region's space.
  float inputCenterX = (((float)destHcolX) + 0.5f) / (float)sizeX;
  float inputCenterY = (((float)destHcolY) + 0.5f) / (float)sizeY;

  // Iterate through each input DataSpace, creating synapses for each one,
  // in each column's proximal segment.
  for (int inputIndex = 0; inputIndex < refInputList.size(); inputIndex++) {

    // Get a pointer to the current input DataSpace.
    curInput = refInputList[inputIndex];

    // Get the input radius corresponding to the current input space.
    inputRadius = inputRadii[inputIndex];

#ifdef BUG
    cout << "inputRadius: "<< inputRadius << "\n";
#endif

    // Determine the center of the receptive field, in the input space's
    // hypercolumn coordinates.
    srcHcolX = Min((int)(inputCenterX * (float)curInput->SizeX), (curInput->SizeX - 1));
    srcHcolY = Min((int)(inputCenterY * (float)curInput->SizeY), (curInput->SizeY - 1));
    if (inputRadius == -1) {
      // The input area will be the full input space.
      inputAreaHcols = Area(0, 0, curInput->SizeX - 1, curInput->SizeY - 1);
    } else {
      // Determine the input area in hypercolumns.
      inputAreaHcols = Area(Max(0, srcHcolX - inputRadius),
			    Max(0, srcHcolY - inputRadius),
			    Min(curInput->SizeX - 1, srcHcolX + inputRadius),
			    Min(curInput->SizeY - 1, srcHcolY + inputRadius));
    }
  
    // Determine the input area in columns.
    inputAreaCols = Area(inputAreaHcols.MinX, 
			 inputAreaHcols.MinY,
			 inputAreaHcols.MaxX,
			 inputAreaHcols.MaxY);

    // Compute volume (in input values) of current input area.
    curInputVolume = inputAreaCols.GetArea() * curInput->SizeZ;

    // Add the current input volume to the SumInputVolume (used by ComputeOverlap()).
    SumInputVolume += curInputVolume;

    // Proximal synapses per Column (input segment) for the current input.
    //cout << "curInputVolume,PctInputPerColumn: "<< curInputVolume << "," <<  PctInputPerColumn << "\n";          
    synapsesPerSegment = (int)(curInputVolume * PctInputPerColumn + 0.5f);

    // The minimum number of inputs that must be active for a column to be 
    // considered during the inhibition step. Sum for all input DataSpaces.
    _minOverlap +=	(int)ceil((float)synapsesPerSegment * PctMinOverlap);

    WeightedDataPoint *InputSpaceArray = new WeightedDataPoint[curInputVolume];
    float weight, sumWeight = 0.0f;

    // Fill the InputSpaceArray with coords of each data point in the input space, 
    // and a weight value inversely proportial to distance from the center of the
    // field.
    int pos = 0;
    for (int hy = inputAreaHcols.MinY; hy <= inputAreaHcols.MaxY; hy++)	{
      for (int hx = inputAreaHcols.MinX; hx <= inputAreaHcols.MaxX; hx++) {
	// Determine the distance of the current input hypercolumn from the center
	// of the field, in the source input space's coordinates.
	dX = srcHcolX - hx;
	dY = srcHcolY - hy;
	distanceToInput_SrcSpace = sqrt(dX * dX + dY * dY);

	// Determine the distance of the current input hypercolumn from the center of the field, in the destination region's coordinates.
	dX *= (float)sizeX / (float)(curInput->SizeX);
	dY *= (float)sizeY / (float)(curInput->SizeY);
	distanceToInput_DstSpace = sqrt(dX * dX + dY * dY);

	// Determine this input hypercolumn's weight based on its distance from
	// the input hypercolumn at the center of the receptive field.  There will
	// be zero probability of synapses to inputs beyond a distance of
	// inputRadius.
	//weight = pow(1.0 - Min(1.0, distanceToInput_InputSpace / (double)(inputRadius)), 0.5);

	// Each hypercolumn with distance from center of receptive field less than
	// inputRadius +1 has weight.
	weight = (distanceToInput_SrcSpace < (inputRadius + 1)) ? 1 : 0;

	for (int y = 0; y < 1; y++) {
	  for (int x = 0; x < 1; x++) {
	    for (int valueIndex = 0; valueIndex < curInput->SizeZ; valueIndex++) {
	      InputSpaceArray[pos].X = hx + x;
	      InputSpaceArray[pos].Y = hy + y;
	      InputSpaceArray[pos].Index = valueIndex;
	      InputSpaceArray[pos].Distance = distanceToInput_DstSpace;
	      InputSpaceArray[pos].Weight = weight;
	      sumWeight += weight;
	      pos++;
	    }
	  }
	}
      }
    }
    //    _ASSERT(pos == curInputVolume);
#ifdef BUG    
    cout << "pos: "<< pos << " curInputVolume " << curInputVolume << "\n";
    cout << "Connected permanence: "<< parameters->ConnectedPermanence  << " Inc " << parameters->PermanenceInc  << "\n";    
#endif
    // Initialize gaussian distribution random number generator. 
    std::default_random_engine generator;
    std::normal_distribution<double> gausianNormalDistribution(parameters->ConnectedPermanence, parameters->PermanenceInc); // Center value and standard deviation.
    //cout << "gausianNormalDistribution(" << parameters->ConnectedPermanence << "," << parameters->PermanenceInc << "0\n";

    // Generate synapsesPerSegment samples, moving thier WeightedDataPoint records
    // to the beginning of the InputSpaceArray.
    WeightedDataPoint tempPoint;
    float curSample, curSampleSumWeight;
    int curSamplePos, numSamples = 0;
    double permanence;

    while (numSamples < synapsesPerSegment) {
      // Determine a sample within the range of the sum weight of all points that
      // have not yet been selected as samples.
      curSample = ((float)rand() / (float)RAND_MAX) * sumWeight;
			
      // Iterate through all remaining points that have not yet been selected
      // as samples...
      curSampleSumWeight = 0.0f;
      for (curSamplePos = numSamples; curSamplePos < curInputVolume; curSamplePos++) {
	curSampleSumWeight += InputSpaceArray[curSamplePos].Weight;

	// If the random sample targets the current point, exit the loop.
	if (curSampleSumWeight >= curSample) {
	  break;
	}
      }

      // Subtract the weight of the sampled point from the sumWeight of all points
      // that haven't yet been selected as samples.
      sumWeight -= InputSpaceArray[curSamplePos].Weight;

      // Determine the permanence value for the new Syanpse.
      permanence = gausianNormalDistribution(generator);
      //permanence = normalgDistribution(parameters->ConnectedPermanence, parameters->PermanenceInc,12,2);

      // Create the proximal synapse for the current sample.
      //ProximalSegment->CreateProximalSynapse(&(region->ProximalSynapseParams), curInput, InputSpaceArray[curSamplePos], permanence, InputSpaceArray[curSamplePos].Distance);
      
      addProximalSynapse(curInput,InputSpaceArray[curSamplePos],permanence,InputSpaceArray[curSamplePos].Distance);

      if (curSamplePos != numSamples) {
	// Swap the Point values at the curSamplePos position with that at the
	// numSamples position.  This way, all samples are moved to the beginning
	// of the InputSpaceArray, below numSamples.
	tempPoint = InputSpaceArray[numSamples];
	InputSpaceArray[numSamples] = InputSpaceArray[curSamplePos];
	InputSpaceArray[curSamplePos] = tempPoint;
      }
    
      // Increment numSamples.
      numSamples++;
    }
#ifdef BUG
    cout << "numSamples: "<< numSamples << " synapsesPerSegment " << synapsesPerSegment << "\n";
#endif
    delete [] InputSpaceArray;
  }		   
  //cout << "minOverlap: "<< _minOverlap << "\n";          
  // Overlap must be at least 1.
  if (_minOverlap <= 0) {
    _minOverlap = 1;
  }
  ProximalSegment = (nSegment *)(Cells[0]->ProximalBasalDendrite.Segments.GetFirst());
  //cout << "Return\n";
}


UInt nColumn::computeStep(std::vector<DataSpaceRef *> &refInputList)
{
  DataSpaceRef *curInput;

#ifdef TRACE
  for(int i = 0; i<indent; i++)  std::cout << "  ";  
  std::cout << MPI::COMM_WORLD.Get_rank() << ": nColumn::computeStep(DataSpaceRef - size "<< refInputList.size() <<"): \n";
  indent++;
#endif

  ActiveSynapses = 0;
  Neuron *neuron = Cells[0];
  nSegment *seg = (nSegment *)neuron->ProximalBasalDendrite.Segments.GetFirst();

  for (int inputIndex = 0; inputIndex < refInputList.size(); inputIndex++) {
    // Get a pointer to the current input DataSpace.
    curInput = refInputList[inputIndex];  

    FastListIter syn_iter(seg->Synapses);
    for (nSynapse * syn = (nSynapse *) (syn_iter.Reset()); syn != NULL;
	 syn = (nSynapse *) (syn_iter.Advance())) {
      if(curInput->dataptr->GetIsActive(syn->InputPoint.X,syn->InputPoint.Y,syn->InputPoint.Index)) {
	ActiveSynapses++;
      }
    }  
  }
#ifdef TRACE
  for(int i = 0; i<indent; i++)  std::cout << "  ";
  std::cout << "returning - nColumn syn count: " << ActiveSynapses << "\n";
  indent--;
#endif
  return ActiveSynapses;
}

UInt nColumn::computeStep(std::vector<InputData *> InputList)
{
  InputData *curInput;
#ifdef TRACE1
  for(int i = 0; i<indent; i++)  std::cout << "  ";
  std::cout << MPI::COMM_WORLD.Get_rank() << ": nColumn::computeStep(InputData - size "<< InputList.size() <<"): \n";
  indent++;
#endif

  ActiveSynapses = 0;
  Neuron *neuron = Cells[0];
  //std::cout << "neuron " << neuron <<"\n";   fflush(stdout);         
  nSegment *seg = (nSegment *)neuron->ProximalBasalDendrite.Segments.GetFirst();
  //std::cout << "seg " << seg <<"\n";   fflush(stdout);         
  for (int inputIndex = 0; inputIndex < InputList.size(); inputIndex++) {
    // Get a pointer to the current input DataSpace.
    curInput = InputList[inputIndex];
    //std::cout << "curInput " << curInput <<"\n";   fflush(stdout);       
    //std::cout << "Input " << curInput->sizeX <<"\n";      

    FastListIter syn_iter(seg->Synapses);
    for (nSynapse * syn = (nSynapse *) (syn_iter.Reset()); syn != NULL;
	 syn = (nSynapse *) (syn_iter.Advance())) {
      if(curInput->GetIsActive(syn->InputPoint.X,syn->InputPoint.Y,syn->InputPoint.Index)) {
	ActiveSynapses++;
      }
    }  
  }

#ifdef TRACE1
  for(int i = 0; i<indent; i++)  std::cout << "  ";
  std::cout << "returning - nColumn syn count: " << ActiveSynapses << "\n";
  indent--;
#endif  
  return ActiveSynapses;
}

Neuron * nColumn::GetCellByIndex(UInt _idx)
{
  //std::cout << "Index " << _idx <<"\n";        
  return(Cells[_idx]);
}

bool nColumn::GetIsActive()
{
  //std::cout << "GetIsActive() " << xLoc << "," << yLoc << " size " << size;
  for(UInt i=0; i<size; i++) {
    //std::cout << ".";    
    if(Cells[i]->GetIsActive()) {
      //std::cout << " rtn true\n";
      return true;
    }
  }
  //std::cout << " rtn false\n";  
  return false;
}
