#pragma once
#include "DataSpace.h"
#include "Utils.h"

class InputData {
 public:
    ~InputData(void);
     InputData(int _proc, int _ref, int _uid, int _sizeX, int _sizeY,
	       int _sizeZ, DataSpaceType _type);
    bool GetIsActive(int _x, int _y, int _z);
    unsigned int GetAllStatus(int _x, int _y, int _z);  
    bool ColumnActive(int _x, int _y);
    void Invalidate(void) {
	dataValid = 0;
    }
    void RefreshData(void);
    void RefreshData(nValue dataptr[]);   // JSK TODO TEMPORARY ONLY

    int *data;			// data matrix
    DataSpaceType Type;
    int sizeX, sizeY, sizeZ;
    bool OutputColumnActivity;
    bool dataValid;
    int RefProc;
    int Proc;
    int uid;
};
