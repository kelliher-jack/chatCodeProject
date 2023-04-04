#include "Neuron.h"
#include "Columns.h"
#include "FastList.h"
#include "MemManager.h"

#include "InputData.h"
#include "DataSpace.h"
#include "TemporalSpace.h"

#include "Normalization.h"
#include "Utils.h"

#include "mpi.h"

#include <cstring>
#include <QtCore/QTextStream>

#include <iostream>
using namespace std;

#define DEBUG

int DataSpaceRef::GetSizeX(int sender)
{
  return(2);
}

int DataSpaceRef::GetSizeY(int sender)
{
  return(2);
}


InputData::InputData(int _proc, int _ref, int _uid, int _sizeX, int _sizeY,
		     int _sizeZ, DataSpaceType _type)
{
    OutputColumnActivity = 0;
    dataValid = 0;
    RefProc = _ref;
    Proc = _proc;
    uid = _uid;
    data = new int[_sizeX * _sizeY * _sizeZ];
    sizeX = _sizeX;
    sizeY = _sizeY;
    sizeZ = _sizeZ;
    Type = _type;
}

InputData::~InputData(void)
{
    delete[]data;
}

void InputData::RefreshData()
{
  // Don't need to do anything (Always is current)
}


void InputData::RefreshData(nValue dataMat[])
{
#ifdef DEBUG
    cout << Proc << ":RefreshData -- InputData\n";
#endif
    
    dataValid = 1;

    int x,y,z;

    for (z = 0; z < sizeZ; z++) {
      for (y = 0; y < sizeY; y++) {
	for (x = 0; x < sizeX; x++) {
	  data[x+y*sizeX+z*sizeX*sizeY] = dataMat[x+y*sizeX]==false ? 0 : 1;
	}
      }
    }
    cout << Proc << ":Recv DATA\n";    
#ifdef DEBUG

    cout << Proc << ":RefreshData() DATA\n";    
    for (z = 0; z < sizeZ; z++) {
      cout << Proc << ":z=" << z << "\n";
      for (y = 0; y < sizeY; y++) {
	cout << Proc << ":D ";
	for (x = 0; x < sizeX; x++) {
	  cout << data[x+y*sizeX+z*sizeX*sizeY] << " ";
	}
	cout << "\n";
      }
    }
#endif
}

bool InputData::GetIsActive(int _x, int _y, int _z)
{
    return data[_x + _y * sizeX + _z * sizeX * sizeY] > 0x00;    
}

unsigned int InputData::GetAllStatus(int _x, int _y, int _z)
{
    return data[_x + _y * sizeX + _z * sizeX * sizeY];    
}

bool InputData::ColumnActive(int _x, int _y)
{
  for(int z=0; z<sizeZ; z++) {
    if(data[_x + _y * sizeX + z * sizeX * sizeY] > 0x00) {
      return(true);
    }
  }
  return (false);
}

nValue pat1[12*12] = {1,1,1,1,1,1,1,1,1,0,0,0,
		      0,0,1,1,1,0,1,1,1,1,0,0,
		      0,0,1,1,1,0,0,1,1,1,0,0,
		      0,0,1,1,1,0,0,1,1,1,0,0,
		      0,0,1,1,1,0,0,1,1,1,0,0,
		      0,0,1,1,1,0,1,1,1,0,0,0,
		      0,0,1,1,1,1,1,1,0,0,0,0,
		      0,0,1,1,1,0,1,1,1,0,0,0,
		      0,0,1,1,1,0,1,1,1,0,0,0,
		      0,0,1,1,1,0,0,1,1,1,0,0,
		      0,0,1,1,1,0,0,1,1,1,0,0,
		      1,1,1,1,1,1,0,0,1,1,1,1};

nValue pat2[12*12] = {1,1,1,1,1,1,1,1,1,1,0,0,
		      0,0,1,1,1,0,0,0,1,1,0,0,
		      0,0,1,1,1,0,0,0,1,1,0,0,
		      0,0,1,1,1,0,0,0,0,0,0,0,
		      0,0,1,1,1,0,0,0,0,0,0,0,
		      0,0,1,1,1,1,1,1,1,0,0,0,
		      0,0,1,1,1,0,0,0,0,0,0,0,
		      0,0,1,1,1,0,0,0,0,0,0,0,
		      0,0,1,1,1,0,0,0,0,0,0,0,
		      0,0,1,1,1,0,0,0,1,1,0,0,
		      0,0,1,1,1,0,0,0,1,1,0,0,
		      1,1,1,1,1,1,1,1,1,1,0,0};

nValue pat3[12*12] = {0,0,0,1,1,1,1,1,1,0,0,0,
		      0,0,1,1,1,0,0,1,1,1,0,0,
		      0,1,1,1,0,0,0,0,1,1,0,0,
		      0,1,1,1,0,0,0,0,0,0,0,0,
		      0,1,1,1,0,0,0,0,0,0,0,0,
		      0,1,1,1,0,0,0,0,0,0,0,0,
		      0,1,1,1,0,0,0,0,0,0,0,0,
		      0,1,1,1,0,0,0,0,0,0,0,0,
		      0,1,1,1,0,0,0,0,0,0,0,0,
		      0,1,1,1,1,0,0,0,0,1,0,0,
		      0,0,1,1,1,1,1,1,1,1,0,0,
		      0,0,0,1,1,1,1,1,1,0,0,0};		      

nValue pat4[12*12] = {0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0,
		      0,0,0,0,0,0,0,0,0,0,0,0};

/* test - test compile
 * test.cpp compile with:
 * g++ `pkg-config --cflags gtk+-3.0` -I.. -I../include -o test test.cpp ../Neuron.cpp `pkg-config --libs gtk+-3.0`
 *
 */

MemManager mem_manager;

int indent = 0;

int main(int argc, char **argv)
{
  MPI::Init(argc, argv);
  
  nValue *patterns[4];
  patterns[0] = pat1;
  patterns[1] = pat2;
  patterns[2] = pat3;
  patterns[3] = pat4;

  QString id = "test1";
  QString input_id = "input1";
  
  SynapticParameters params_binary = {
			       binaryNorm,
			       0.2f,
			       0.22f,
			       0.01f,
			       0.015f,			       
			       0.025f
  };

  SynapticParameters params_linear = {
			       linearNorm,
			       0.2f,
			       0.22f,
			       0.01f,
			       0.015f,			       
			       0.025f
  };  

  InputData *dataptr = new InputData(1,1,1, 3, 3,2, DATASPACE_TYPE_INPUTSPACE);
  
  //InputSpace,region etc inherents DataSpace
  // only DataSpaceRef has a pointer to InputData
  DataSpaceRef *inputspace = new DataSpaceRef(input_id,1,1,DATASPACE_TYPE_INPUTSPACE,dataptr);

#ifdef COMMENTOUT
  DataPoint inputpoint0 = {0,2,0};
  DataPoint inputpoint1 = {1,2,0};
  DataPoint inputpoint2 = {2,2,0};

  DataPoint inputpoint3 = {0,0,1};
  DataPoint inputpoint4 = {0,1,1};
  DataPoint inputpoint5 = {0,2,1};
#endif // COMMENTOUT

  SynapseParameters sp;

  sp.InitialPermanence = params_binary.InitialPermanence;
  sp.ConnectedPerm     = params_binary.ConnectedPermanence;
  sp.PermanenceInc     = params_binary.PermanenceInc;
  sp.PermanenceDec     = params_binary.PermanenceDec;

  UInt width  = 12;
  UInt height = 12;

  TemporalSpace *ts = new TemporalSpace((NetworkManager *)NULL, id, 4, TEMPORAL_POOLING,
				Point(width,height),1,
				sp,sp, // prox parms, dist parms
				20.0f,10.0f, //%input/cell, %minOver,
				20,  // predictionRadius
				INHIBITION_TYPE_AUTOMATIC, 20, //inh Radius
				0.1f,0.05f,5.0f,
				0.2f,0.01f,0.1f,
				-1,-1,
				-1,-1,
				-1,-1,4, // boostStart, boostEnd, cellsPerCol
				5,5,
				6,
				3,
				3,false,
				true, false, 0,
				1, false, 0);

  nColumn *cols = new nColumn(ts,&params_binary,2,1,4);
  std::cout << "Column x,y,size: "<<cols->xLoc<<","<<cols->yLoc<<","<<cols->size<<"\n";

  dataptr = new InputData(1,1,1, 12,12,1, DATASPACE_TYPE_INPUTSPACE);

  inputspace->SizeX = 12;
  inputspace->SizeY = 12;
  inputspace->SizeZ = 1;

  dataptr->RefreshData(pat1);

  std::vector<DataSpaceRef *> input;
  std::vector<int> inputRadii;
  std::vector < Input >input_params;

  Input inputparams;
  inputparams.Type   = PROXIMAL_DENDRITE;
  inputparams.Growth = STATIC_GROWTH;
  inputparams.Delayed = false;
  inputparams.OffsetXinRegion = 0;
  inputparams.OffsetYinRegion = 0;
  inputparams.InputOffsetX = 0;
  inputparams.InputOffsetY = 0;    
  inputparams.SizeX = inputspace->SizeX;
  inputparams.SizeY = inputspace->SizeY;

  
  input.push_back(inputspace);
  inputRadii.push_back(20);
  input_params.push_back(inputparams);  

  ts->InputParams = input_params;
  ts->InputRadii = inputRadii;
    
  ts->AddInput(inputspace,dataptr);
  ts->Initialize();
  
  ts->ProcessStep();

  nColumn *columnSpace[width][height];

  std::cout << "input count: " << input.size() << "\n";
  for(UInt i=0; i<width; i++) {       // x
    for(UInt j=0; j<height; j++) {    // y
      //std::cout << i << "," << j << ": ";      
      columnSpace[i][j] = new nColumn(ts,&params_binary,i,j,9);
      columnSpace[i][j]->createProximalSegments(input,inputRadii,width,height);
    }
  }

  std::cout << "Test column input\n";
  std::cout << "Column x,y,size: "<< columnSpace[1][1]->xLoc<<","<<columnSpace[1][1]->yLoc<<","<<columnSpace[1][1]->size<<"\n";
  std::cout << "Column CP,PI: "<< columnSpace[0][0]->parameters->ConnectedPermanence<<","<<columnSpace[0][0]->parameters->PermanenceInc<<"\n";  fflush(stdout);

  std::cout << "TEST DONE\n";  
  return(1);
}

