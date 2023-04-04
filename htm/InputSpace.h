#pragma once
#include "DataSpace.h"
#include <QtGui/QImage>
#include <QtGui/QPainter>

#include <ft2build.h>
#include FT_FREETYPE_H

enum PatternType {
    PATTERN_NONE,
    PATTERN_STRIPE,
    PATTERN_BOUNCING_STRIPE,
    PATTERN_BAR,
    PATTERN_BOUNCING_BAR,
    PATTERN_TEXT,
    PATTERN_BITMAP,
    PATTERN_IMAGE,
    PATTERN_SOCKET_INPUT,
    PATTERN_SOCKET_INTERACTIVE,    
    PATTERN_INPUT
};

enum PatternImageFormat {
    PATTERN_IMAGE_FORMAT_UNDEF,
    PATTERN_IMAGE_FORMAT_SPREADSHEET
};

enum PatternImageMotion {
    PATTERN_IMAGE_MOTION_NONE,
    PATTERN_IMAGE_MOTION_ACROSS,
    PATTERN_IMAGE_MOTION_ACROSS2
};

class ImageInfo {
 public:
    QString label;
    int width, height, contentX, contentY, contentWidth, contentHeight;
    float *data;
};

class PatternInfo {
 public:
    PatternInfo():type(PATTERN_NONE), startTime(-1), endTime(-1),
	minTrialDuration(1), maxTrialDuration(1), string(""),
	imageMotion(PATTERN_IMAGE_MOTION_NONE), trialCount(0),
	curTrialStartTime(-1), nextTrialStartTime(-1) {
    };
    PatternInfo(PatternType _type, int _startTime, int _endTime,
		int _minTrialDuration, int _maxTrialDuration,
		QString & _string, PatternImageMotion _imageMotion,
		std::vector < int *>&_bitmaps,
		std::vector < int >&_syms,
		std::vector < int >&_reflexidxs,
		std::vector < ImageInfo * >&_images):type(_type),
        startTime(_startTime), endTime(_endTime),
	minTrialDuration(_minTrialDuration),
	maxTrialDuration(_maxTrialDuration), string(_string),
	imageMotion(_imageMotion), trialCount(0), curTrialStartTime(-1),
    nextTrialStartTime(-1), bitmaps(_bitmaps), syms(_syms), reflexidxs(_reflexidxs), images(_images) {
    };
    PatternInfo(PatternInfo & _original) {
	type = _original.type;
	startTime = _original.startTime, endTime = _original.endTime;
	minTrialDuration = _original.minTrialDuration;
	maxTrialDuration = _original.maxTrialDuration;
	string = _original.string;
	imageMotion = _original.imageMotion;
	trialCount = 0;
	curTrialStartTime = -1;
	nextTrialStartTime = -1;
    }

    PatternType type;
    PatternImageFormat imageFormat;
    PatternImageMotion imageMotion;
    int startTime, endTime;
    int minTrialDuration, maxTrialDuration;
    int startX, startY, endX, endY;
    QString string;
    QString addressString;
    std::vector < int *>bitmaps;
    std::vector < int >syms;
    std::vector < int >reflexidxs;    
    std::vector < ImageInfo * >images;
    int *buffer;

    int trialCount, curTrialStartTime, nextTrialStartTime;
};

class InputSpace:public DataSpace {
 public:
    InputSpace(QString & _id, int _uid, int _sizeX, int _sizeY,
	       int _numValues, int _burstUntil,
	       std::vector < PatternInfo * >&_patterns,
	       bool outputColumnActivity, bool outputCellActivity,	       
	       int _proc, int _refproc, bool vert, FT_Face _ft_face);
    ~InputSpace(void);

    // Properties

    int sizeX, sizeY, numValues, burstUntil, testPatterns;
    int rowSize;
    int *data;        // input column, cell data input
                      // data value meaning (state) at current time t
                      // bit 0 - Is Active                 t
		      // bit 1 - Was Active                t-1
                      // bit 2 - Is Learning               t
                      // bit 3 - Was Learning              t-1
                      // bit 4 - Predicted                 t
                      // bit 5 - Was Predicted             t-1
                      // bit 6 - Segment Is Predicting     t
                      // bit 7 - Was Active From Learning  t-1
    int  *buffer;
    int time;

    bool vert;
    bool dataValid;
    int uid;
    int proc;			// process that created Region and owns it
    int refproc;		// if root process then ref to actural Region data process
    int node;
    FT_Face ft_face;
    int socket;
    char socketout;
    char socketout1;  
    int socketin;
    bool OutputColumnActivity;
    bool OutputCellActivity;

     std::vector < PatternInfo * >patterns;

    QImage *image;
    QPainter *painter;

    // Methods

    DataSpaceType GetDataSpaceType() {
	return DATASPACE_TYPE_INPUTSPACE;
    }
    int GetSizeX();
    int GetSizeY();
    int GetNumValues();
    int GetHypercolumnDiameter();

    int GetProcess() {
	return refproc;
    }
    int GetUID() {
	return uid;
    }

    void SocketRecvSend(char value1, char value2, int *reward);

    bool GetIsActive(int _x, int _y, int _index);
    bool GetWasActive(int _x, int _y, int _index);
    bool GetIsLearning(int _x, int _y, int _index);
    bool GetWasLearning(int _x, int _y, int _index);
    bool GetIsPredicting(int _x, int _y, int _index);
    bool GetWasPredicted(int _x, int _y, int _index);
    bool GetIsSegmentPredicting(int _x, int _y, int _index);  
    bool GetWasActiveFromLearning(int _x, int _y, int _index);
    int  GetAllStatus(int _x, int _y, int _index);
    bool ColumnActive(int _x, int _y);
  

    void SetIsActive(int _x, int _y, int _index, bool _active);
    void SetWasActive(int _x, int _y, int _index, bool _active);
    void SetIsLearning(int _x, int _y, int _index, bool _active);
    void SetWasLearning(int _x, int _y, int _index, bool _active);
    void SetIsPredicting(int _x, int _y, int _index, bool _active);
    void SetWasPredicted(int _x, int _y, int _index, bool _active);
    void SetIsSegmentPredicting(int _x, int _y, int _index, bool _active);
    void SetWasActiveFromLearning(int _x, int _y, int _index, bool _active);
  
    void DeactivateAll();

    void ApplyPatterns(int _time);
    void ApplyPattern(PatternInfo * _pattern, int _time);
    int Validate();
    void Check(void);
};
