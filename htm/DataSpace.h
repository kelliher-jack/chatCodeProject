#pragma once
#include <QtCore/qstring.h>

typedef int DataSpaceType;
const DataSpaceType DATASPACE_TYPE_INPUTSPACE = 0;
const DataSpaceType DATASPACE_TYPE_REGION = 1;
const DataSpaceType DATASPACE_TYPE_CLASSIFIER = 2;
const DataSpaceType DATASPACE_TYPE_MOTORCMD = 3;
const DataSpaceType DATASPACE_TYPE_LAYER = 4;
const DataSpaceType DATASPACE_TYPE_SPACE_REF = 5;
const DataSpaceType DATASPACE_TYPE_UNKNOWN = -1;

class InputData;

class DataSpace {
 public:

    DataSpace(QString & _id) {
	id = _id;
	index = -1;
    }
  //const QString & GetID() {
  //	return id;
  //}
    QString & GetID() {
	return id;
    }  
    void SetID(QString & _id) {
	id = _id;
    }

    void SetIndex(int _index) {
      index = _index;
    }
    int GetIndex() {
      return index;
    }

    virtual DataSpaceType GetDataSpaceType() = 0;

    virtual int GetSizeX() = 0;
    virtual int GetSizeY() = 0;
    virtual int GetNumValues() = 0;
    virtual int GetHypercolumnDiameter() = 0;
    virtual int GetProcess() = 0;
    virtual int GetUID() = 0;

    virtual bool GetIsActive(int _x, int _y, int _index) = 0;
    virtual int  GetAllStatus(int _x, int _y, int _index) = 0;  
    virtual int  Validate() = 0;

    QString id;
    int index;
};

class DataSpaceRef {
 public:

    DataSpaceRef(QString & _id) {
	id = _id;
	//	index = -1;
	activeRefData = NULL;
    }
    DataSpaceRef(QString & _id, int _proc, int _uid, DataSpaceType _type) {
	proc = _proc;
	uid = _uid;
	id = _id;
	dataspacetype = _type;
	activeRefData = NULL;
    }
    DataSpaceRef(QString & _id, int _proc, int _uid, DataSpaceType _type, InputData * _dataptr) {
	proc = _proc;
	uid = _uid;
	id =_id;
	dataspacetype = _type;
	dataptr = _dataptr;
	activeRefData = NULL;
    }

    const QString & GetID() {
	return id;
    }
    void SetID(QString & _id) {
	id = _id;
    }

  //    void SetIndex(int _index) {
  //	index = _index;
  //    }
  //    int GetIndex() {
  //	return index;
  //    }

    DataSpaceType GetDataSpaceType() {
	return dataspacetype;
    }
    int GetProcess() {
	return proc;
    }
    int GetUID() {
	return uid;
    }

    int GetSizeX(int sender);
    int GetSizeY(int sender);
    int GetNumValues(int sender);
    int GetHypercolumnDiameter(int sender);

    void Update(int sender);
    bool GetIsActive(int _x, int _y, int _index);
    int  GetAllStatus(int _x, int _y, int _index);
    bool ColumnActive(int _x, int _y);

    QString id;
  //    int index;
    int proc;
    int uid;
    DataSpaceType dataspacetype;
    InputData *dataptr;
    int SizeX;
    int SizeY;
    int SizeZ;
    unsigned char *activeRefData;
};
