#include "InputSpace.h"
#include "Utils.h"
#include <string.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#else
#define _ASSERT(expr) ((void)0)
#define _ASSERTE(expr) ((void)0)
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include<sys/socket.h>    //socket
#include<arpa/inet.h>     //inet_addr

using namespace std;
#include "mpi.h"

//#define TRACE 1
extern int indent;

//#define DEBUG 1
//#define NDEBUG 1
//#define MAPBUG 1
//#define RANDBUG 1

InputSpace::InputSpace(QString & _id, int _uid, int _sizeX, int _sizeY,
		       int _numValues, int _burstUntil, std::vector < PatternInfo * >&_patterns,
		       bool _outputColumnActivity,  bool _outputCellActivity,
		       int _proc, int _refproc, bool _vert, FT_Face _ft_face)
 : DataSpace(_id), image(NULL), patterns(_patterns)
{
    sizeX = _sizeX;
    sizeY = _sizeY;
    numValues = _numValues;
    burstUntil = _burstUntil;
    proc = _proc;
    refproc = _refproc;
    uid = _uid;
    vert = _vert;
    dataValid = 0;
    ft_face = _ft_face;
    socketout  = '0';
    socketout1 = ' ';
    OutputColumnActivity = _outputColumnActivity;
    OutputCellActivity   = _outputCellActivity;
    
    rowSize = sizeX * numValues;

    // Create data array.
    data = new int[_sizeX * _sizeY * _numValues];

    // Create image processing buffer.
    buffer = new int[_sizeX * _sizeY];

    // Initialize all values to 0.
    DeactivateAll();
    time = 0;
}

InputSpace::~InputSpace(void)
{
    // Delete data array.
    delete[]data;

    // Delete image processing buffer.
    delete[]buffer;

    // Delete all PatternInfo objects in patterns array.
    PatternInfo *curPattern;
    while (patterns.size() > 0) {
	curPattern = patterns.back();
	patterns.pop_back();
	delete curPattern;
    }
}

int InputSpace::GetSizeX()
{
    return sizeX;
}

int InputSpace::GetSizeY()
{
    return sizeY;
}

int InputSpace::GetNumValues()
{
    return numValues;
}

int InputSpace::GetHypercolumnDiameter()
{
    return 1;
}

bool InputSpace::GetIsActive(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    if(OutputColumnActivity) {
      int colval=0;
      for(int i=0; i < numValues; i++) {
	colval |= ((data[(_y * rowSize) + (_x * numValues) + i] & 0x01) != 0);
      }
      return colval;
    } else {
      return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x01) != 0);
    }
}

bool InputSpace::GetWasActive(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x02) != 0);
}

bool InputSpace::GetIsLearning(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x04) != 0);
}

bool InputSpace::GetWasLearning(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x08) != 0);
}

bool InputSpace::GetIsPredicting(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x10) != 0);
}

bool InputSpace::GetWasPredicted(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x20) != 0);
}

bool InputSpace::GetIsSegmentPredicting(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x40) != 0);
}

bool InputSpace::GetWasActiveFromLearning(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return ((data[(_y * rowSize) + (_x * numValues) + _index] & 0x80) != 0);
}

int  InputSpace::GetAllStatus(int _x, int _y, int _index)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    return (data[(_y * rowSize) + (_x * numValues) + _index]);
}

bool  InputSpace::ColumnActive(int _x, int _y)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));

    for(int i=0; i<numValues; i++) {
      if((data[(_y * rowSize) + (_x * numValues) + i] & 0x01)) {
	return(true);
      }
    }
    return (false);
}

void InputSpace::SetIsActive(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xFE;    
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x01 : 0);
}

void InputSpace::SetWasActive(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xFD; 
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x02 : 0);
}
void InputSpace::SetIsLearning(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xFB;
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x04 : 0);
}
void InputSpace::SetWasLearning(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xF7;    
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x08 : 0);
}
void InputSpace::SetIsPredicting(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xEF;    
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x10 : 0);
}
void InputSpace::SetWasPredicted(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xDF;    
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x20 : 0);
}
void InputSpace::SetIsSegmentPredicting(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0xBF;    
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x40 : 0);
}
void InputSpace::SetWasActiveFromLearning(int _x, int _y, int _index, bool _active)
{
    _ASSERT((_x >= 0) && (_x < sizeX));
    _ASSERT((_y >= 0) && (_y < sizeY));
    _ASSERT((_index >= 0) && (_index < numValues));

    data[(_y * rowSize) + (_x * numValues) + _index] &= 0x7F;    
    data[(_y * rowSize) + (_x * numValues) + _index] |= (_active ? 0x80 : 0);
}

void InputSpace::DeactivateAll()
{
    // Reset all values in data array to 0.
    memset(data, 0, sizeY * rowSize * sizeof(int));
}

int InputSpace::Validate()
{
    MPI::Status status;
    int ibuf[4];

    // cout << proc << ":InputSpace::Validate uid " << uid << " vert " << vert << " valid " << dataValid << "\n";    

    if (vert != 1)
	return (1);		// If not a vertual region then just return
    if (dataValid)
	return (0);		// If the copy of the data is still valid just return
#ifdef TRACE
    for(int i = 0; i<indent; i++)  std::cout << "  ";
    std::cout << proc << ": InputSpace::Validate() dataValid: " << dataValid << "\n";
    indent++;
#endif      
    int buf[10];
    buf[0] = 0;
    buf[1] = 'V';
    buf[2] = 0;			// Region/Input id 0-255
    // Layer        id 0-255 norm: 6 horiz layers hippocampus 3
    buf[4] = uid;
    buf[5] = 0;
    buf[6] = 0;
    buf[7] = 0;
    buf[8] = 0;			// Cell         id 0-255
#ifdef DEBUG
    cout << proc << ":Validate -- InputSpace\n";
#endif
    MPI::COMM_WORLD.Send(buf, 9, MPI::INT, refproc, 0);
#ifdef DEBUG
    cout << proc << ":Sent CMD\n";
#endif
    MPI::COMM_WORLD.Recv(ibuf, 2, MPI::INT, refproc, 0, status);
#ifdef DEBUG
    cout << proc << ":Recieved " << ibuf[0] << " elements " << ibuf[1] << " values\n";
#endif
    if (sizeX * sizeY * numValues != ibuf[0]) {
	cout << "0:ERROR size mismatch recieved " << ibuf[0] <<
	    " expected " << sizeX * sizeY * numValues << " bytes\n";
    }
    MPI::COMM_WORLD.Recv(data, ibuf[0], MPI::INT, refproc, 0, status);
    dataValid = 1;

#ifdef TRACE
    indent--;
#endif          
    return (1);
}

void InputSpace::Check(void)
{
    MPI::Status status;
    int ibuf[4];

    if (vert) {
	int buf[10];

	buf[0] = 0;
	buf[1] = '?';
	buf[2] = uid;
	buf[3] = 0;
	// Layer        id 0-255 norm: 6 horiz layers hippocampus 3
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = 0;
	buf[8] = 0;		// Cell         id 0-255
	MPI::COMM_WORLD.Ssend(buf, 9, MPI::INT, refproc, 0);
	MPI::COMM_WORLD.Recv(ibuf, 1, MPI::INT, refproc, 0, status);
#ifdef DEBUG
	cout << "0:Sent CHECK CMD to proc " << refproc <<
	    " time " << time++ << "\n";
#endif
	return;
    }
}

void InputSpace::SocketRecvSend(char value0, char value1, int *reward)
{
  socketout = value0;
  socketout1 = value1;  
  cout << proc << ":SocketRecvSend(" << socketout << "," << socketout1 << "," <<
    socketin << ")\n";
  *reward = socketin;
}

void InputSpace::ApplyPatterns(int _time)
{
    PatternInfo *curPattern;

    if (vert) {
	int buf[10];
	int ibuf[2];

	dataValid = 0;
	buf[0] = 0;
	buf[1] = 'A';
	buf[2] = uid;
	buf[3] = 0;
	// Layer        id 0-255 norm: 6 horiz layers hippocampus 3
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = 0;
	buf[8] = 0;		// Cell         id 0-255
	ibuf[0] = _time;
	MPI::COMM_WORLD.Send(buf, 9, MPI::INT, refproc, 0);
	MPI::COMM_WORLD.Send(ibuf, 1, MPI::INT, refproc, 0);
#ifdef DEBUG
	cout << "0:Sent CMD ApplyPatterns to uid " << uid << " time " <<
	    _time << "\n";
#endif
	return;
    }
#ifdef DEBUG
    cout << proc << ":APPLYING PATTERNS size " << patterns.size() << " _time "
	<< _time << "\n";
#endif
    for (int i = 0; i < patterns.size(); i++) {
	curPattern = patterns[i];

#ifdef DEBUG
	cout << proc << ":  " << i << " startTime " << curPattern->startTime <<
	    "\n";
	cout << proc << ":  " << i << " endTime " << curPattern->endTime <<
	    "\n";
#endif

	if (((curPattern->startTime == -1)
	     || (curPattern->startTime <= _time))
	    && ((curPattern->endTime == -1)
		|| (curPattern->endTime >= _time))) {
	    ApplyPattern(curPattern, _time);
	    break;
	}
    }

#ifdef CurDBG
      cout << refproc << ":Notify head end apply has finished\n";
#endif
      int buf[10];
    
      buf[0] = refproc;  // Sending process rank/id
      buf[1] = 'e';
      buf[2] = 0;	 // Recieving process is the head end
      buf[4] = 0;
      buf[5] = 0;
      buf[6] = 0;
      buf[7] = 0;
      buf[8] = 0;

      MPI::COMM_WORLD.Send(buf, 9, MPI::INT, 0, 0); 
}

void InputSpace::ApplyPattern(PatternInfo * _pattern, int _time)
{
    // If there is no pattern to apply, do nothing.
    if (_pattern->type == PATTERN_NONE) {
	cout << proc << ":  No pattern\n";
	return;
    }
    // Advance to next trial if necessary.
    if (_time >= _pattern->nextTrialStartTime) {
	_pattern->trialCount++;
	_pattern->curTrialStartTime = _time;

	if (_pattern->minTrialDuration == _pattern->maxTrialDuration) {
	    _pattern->nextTrialStartTime = _time + _pattern->minTrialDuration;
	} else {
	    int randVal = rand();
#ifdef RANDBUG
	    cout << proc << ":rand() " << randVal << "\n";
#endif
	    _pattern->nextTrialStartTime =
		_time + _pattern->minTrialDuration +
		(rand() %
		 (_pattern->maxTrialDuration - _pattern->minTrialDuration + 1));
	}
    }

    int x, y, x1, y1, i, numSteps, step;
    float scale;
    int *bitmap;
    ImageInfo *imageInfo;
#ifdef DEBUG
    cout << proc << ":   pattern type " << (int)_pattern->type << "\n";
#endif
    switch (_pattern->type) {
    case PATTERN_STRIPE:
#ifdef DEBUG
	cout << proc << ":    PATTERN_STRIPE\n";
#endif
	// Apply stripe test pattern.

	// If this isn't the start of a new trial, no need to update activity.
	if (_time != _pattern->curTrialStartTime) {
	    break;
	}
	// Start by clearing all activity.
	DeactivateAll();

	numSteps = (sizeX + sizeY - 1);
	step = (_pattern->trialCount - 1) % numSteps;

	for (x = 0; x < sizeX; x++) {
	    y = step - x;

	    if (y < 0)
		break;
	    if (y >= sizeY)
		continue;

	    for (i = 0; i < numValues; i++) {
		SetIsActive(x, y, i, true);
	    }
	}
	break;

    case PATTERN_BOUNCING_STRIPE:
#ifdef DEBUG
	cout << proc << ":    PATTERN_BOUNCING_STRIPE\n";
#endif
	// Apply stripe test pattern.

	// If this isn't the start of a new trial, no need to update activity.
	if (_time != _pattern->curTrialStartTime) {
	    break;
	}
	// Start by clearing all activity.
	DeactivateAll();

	numSteps = (sizeX + sizeY - 2);
	step = (_pattern->trialCount - 1) % (numSteps * 2);

	// Reverse direction of stripe if appropriate.
	if (step >= numSteps) {
	    step = numSteps - (step - numSteps);
	}

	for (x = 0; x < sizeX; x++) {
	    y = step - x;

	    if (y < 0)
		break;
	    if (y >= sizeY)
		continue;

	    for (i = 0; i < numValues; i++) {
		SetIsActive(x, y, i, true);
	    }
	}
	break;

    case PATTERN_BAR:
#ifdef DEBUG
	cout << proc << ":    PATTERN_BAR\n";
#endif
	// Apply bar test pattern.

	// If this isn't the start of a new trial, no need to update activity.
	if (_time != _pattern->curTrialStartTime) {
	    break;
	}
	// Start by clearing all activity.
	DeactivateAll();

	numSteps = sizeX;
	step = (_pattern->trialCount - 1) % numSteps;

	for (y = 0; y < sizeY; y++) {
	    for (i = 0; i < numValues; i++) {
		SetIsActive(step, y, i, true);
	    }
	}
	break;

    case PATTERN_BOUNCING_BAR:
#ifdef DEBUG
	cout << proc << ":    PATTERN_BOUNCING_BAR\n";
#endif
	// Apply bouncing bar test pattern.

	// If this isn't the start of a new trial, no need to update activity.
	if (_time != _pattern->curTrialStartTime) {
	    break;
	}
	// Start by clearing all activity.
	DeactivateAll();

	numSteps = sizeX - 1;
	step = (_pattern->trialCount - 1) % (numSteps * 2);

	// Reverse direction of bar if appropriate.
	if (step >= numSteps) {
	    step = numSteps - (step - numSteps);
	}

	for (y = 0; y < sizeY; y++) {
	    for (i = 0; i < numValues; i++) {
		SetIsActive(step, y, i, true);
	    }
	}
	break;

    case PATTERN_TEXT:
	{
#define FreeFont 1
#ifdef FreeFont
	    FT_Error error = FT_Err_Ok;
#ifdef DEBUG
	    cout << proc << ":    PATTERN_TEXT\n";
#endif
	    // Apply text test pattern.
	    // If this isn't the start of a new trial, no need to update activity.
	    if (_time != _pattern->curTrialStartTime) {
		break;
	    }
	    // Start by clearing all activity.
	    DeactivateAll();

	    numSteps = _pattern->string.length();
	    step = (numSteps > 0) ? ((_pattern->trialCount - 1) % numSteps) : 0;
	    scale = 0.8 * ((float)sizeY / 8.0f);

	    // Can't use QT drawText since requires
	    // an QT graphical application to be running
	    // within an windowed enviroment BUT nodes
	    // are text only systems with no XServer
	    // We will use FreeFont instead to render the font to a bitmap.

	    // Initialize image and painter if not yet done.
	    // cout << "    image: " << image << "\n";
	    if (image == NULL) {
		image = new QImage(sizeX, sizeY, QImage::Format_Mono);
	    }
	    // Draw the text to the image.
	    image->fill(0);
#ifdef MAPBUG
	    cout << proc << ":    Text " << _pattern->string.
		toLocal8Bit().constData() << "\n";
	    cout << proc << ":    Text " << _pattern->string.mid(step,
							1).toLocal8Bit().
		constData() << "\n";
	    cout << proc << ":    Draw " << sizeX << " " << scale << " " << sizeY << " "
		<< step << "\n";
	    cout << proc << ":    Font Face Size " << ft_face->size << "\n";
	    cout << proc << ":    Face fixed sizes " << ft_face->num_fixed_sizes << "\n";
#endif
	    error = FT_Set_Char_Size(ft_face, 64, 64, 64, 64);

	    if (error) {
		cout << proc << ":ERROR Could not set char size\n";
	    }
	    float s = (float)(sizeX*1.333333+.5);
	    // seems to be only way to scale it.
	    error = FT_Set_Pixel_Sizes(ft_face, (int)s, (int)s);

	    if (error) {
		cout << proc << ":ERROR Could not set char pixel size\n";
	    }

	    FT_UInt glyph_index = 0;
	    QChar character = _pattern->string.mid(step, 1).at(0);
	    glyph_index = FT_Get_Char_Index(ft_face, character.unicode());
#ifdef MAPBUG
	    cout << proc << ":  Char Index " << glyph_index << "\n";
	    cout << proc << ":  Char \'" << character.toLatin1() << "\'\n";
#endif
	    error = FT_Load_Glyph(ft_face, glyph_index, FT_LOAD_DEFAULT);
	    if (error) {
		cout << proc <<
		    ":ERROR Unable to load glyph for \'" <<
		    character.toLatin1() << "\'\n";
	    }

	    error = FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);
	    if (error) {
		cout << proc <<
		    ":ERROR Unable to Render Glyph for \'" <<
		    character.toLatin1() << "\'\n";
	    }
#ifdef MAPBUG
	    {
		int x, y;
		for (y = 0; y < ft_face->glyph->bitmap.rows; y++) {
		    for (x = 0; x < ft_face->glyph->bitmap.width; x++) {
			cout << (int)ft_face->glyph->bitmap.buffer[x +
								   y *
								   ft_face->glyph->
								   bitmap.width]
			    << " ";
		    }
		    cout << "\n";
		}
	    }
	    cout << proc << ":  Width " << ft_face->glyph->
		bitmap.width << " Rows " << ft_face->glyph->bitmap.rows << " ";
	    cout << x << "," << y << "\n";
#endif

	    cout << "    Create Pattern " << _time << "," << burstUntil << "\n";
	    for (y = 0; y < sizeY; y++) {
		for (x = 0; x < sizeX; x++) {
		    //cout << "pix " << x << "," << y << "\n";
		    if (x < ft_face->glyph->bitmap.width) {
			if (y < ft_face->glyph->bitmap.rows) {
			    if (ft_face->glyph->bitmap.buffer[x +
							      y *
							      ft_face->glyph->bitmap.width]
				>= 64) {
			      if(burstUntil == 0) {
				for (i = 0; i < numValues; i++) {
				    //cout << x << "," << y << "," << i << " Active\n";
				    SetIsActive(x, y, i, true);
				}
			      } else {
				if(_time < burstUntil) {
				  for (i = 0; i < numValues; i++) {
				    //cout << x << "," << y << "," << i << " Active\n";
				    SetIsActive(x, y, i, true);
				  }
				} else {
				  int t = (_time+x*2+y*2+x) % numValues;
				  if(t >= numValues) t = 0;
				  SetIsActive(x, y, t, true);
				}
			      } // else
			    } // >= 64
			}
		    }
		}
	    }
#else // use QT font
	    cout << proc << ": PATTERN_TEXT using QT\n";
		// Apply text test pattern.
	    
		// If this isn't the start of a new trial, no need to update activity.
		if (_time != _pattern->curTrialStartTime) {
			break;
		}

		// Start by clearing all activity.
		DeactivateAll();

		numSteps = _pattern->string.length();
		step = (numSteps > 0) ? ((_pattern->trialCount - 1) % numSteps) : 0;
		scale = 0.8 * ((float)sizeY / 8.0f);

		// Initialize image and painter if not yet done.
		if (image == NULL) 
		{
			image = new QImage(sizeX, sizeY, QImage::Format_Mono);
			painter = new QPainter(image);
			painter->setPen(QColor(255,255,255));
			painter->setFont(QFont("Times", 10, QFont::Bold));
			painter->scale(scale, scale);
		}

		// Draw the text to the image.
		image->fill(0);
		painter->drawText(QRect(0, 0, (float)sizeX / scale, (float)sizeY / scale), Qt::AlignCenter, _pattern->string.mid(step, 1)); 

		for (y = 0; y < sizeY; y++)
		{
			for (x = 0; x < sizeX; x++)
			{
				if (QColor(image->pixel(x,y)).lightness() >= 128) 
				{
					for (i = 0; i < numValues; i++) {
						SetIsActive(x, y, i, true);
					}
				}				
			}
		}
#endif
	}
	break;
    case PATTERN_SOCKET_INPUT:
        {
	  char message[1000] , server_reply[12000];
	  int idx;
	  char i,j,t;
	  int bufsize;
#ifdef NDEBUG
	  cout << proc << ":    PATTERN_SOCKET_BITMAP\n";
#endif
	  // Get net pattern
	  sprintf(message,"N ");
	  if( send(socket , message , strlen(message) , 0) < 0) {
	      cout << proc << ":Socket Send command failed/n";
              //  return 1;
          }
	  //Receive a reply from the server
	  if( recv(socket , server_reply , 12000 , 0) < 0) {
	      cout << proc << ":Socket recv ack failed/n";
              //break;
          }
	  if((sizeX*sizeY) % 8 == 0) {
	    bufsize = sizeX*sizeY/8;
	  } else {
	    bufsize = sizeX*sizeY/8+1;
	  }

#ifdef NDEBUG
	  cout << proc << ":bufsize " << bufsize <<"\n";
#endif
	  
	  // Clear active columns from the pattern
	  for (y = 0; y < sizeY; y++) {
	    for (x = 0; x < sizeX; x++) {
	      for (i = 0; i < numValues; i++) {	    
		SetIsActive(x, y, i, false);
	      }
	    }
	  }

	  x = y = 0;
	  for (idx=0; idx < bufsize; idx++) {
	    t = server_reply[idx];
#ifdef NDEBUG
	    cout << " " << (unsigned char)t;
#endif	    
	    for(j=0;j<8;j++) {
	      if((t&0x80) == 0x80) {
		if(burstUntil == 0) {
		  for (i = 0; i < numValues; i++) {
		    SetIsActive(x, y, i, true);
		  }
		} else {
		  if(_time < burstUntil) {
		    for (i = 0; i < numValues; i++) {
		      SetIsActive(x, y, i, true);
		    }
		  } else {
		    int t = (_time+x*2+y*2+x) % numValues;
		    if(t >= numValues) t = 0;
		    SetIsActive(x, y, t, true);
		  }
		} // else
	      }
	      t = t << 1;
	      x++;
	      if(x == sizeX) {
		x = 0;
		y++;
	      }
	    }
	  }
#ifdef NDEBUG
	    cout << "\n";
#endif	    
        }
	break;
    case PATTERN_SOCKET_INTERACTIVE:
        {
	  char message[1000] , server_reply[12000];
	  int idx;
	  char i,j,t;
	  int bufsize;
#ifdef NDEBUG
	  cout << proc << ":    PATTERN_SOCKET_INTERACTIVE\n";
#endif
	  // Get net pattern
	  //sprintf(message,"5");
	  sprintf(message,"%c%c",socketout,socketout1);
	  cout << proc << ":Socket Sending -" << message << "-\n";	  
	  if( send(socket , message , strlen(message) , 0) < 0) {
	      cout << proc << ":Socket Send command failed/n";
              //  return 1;
          }
	  //Receive a reply from the server
	  if( recv(socket , server_reply , 12000 , 0) < 0) {
	      cout << proc << ":Socket recv ack failed\n";
              //break;
          }
	  if((sizeX*sizeY) % 8 == 0) {
	    bufsize = sizeX*sizeY/8;
	  } else {
	    bufsize = sizeX*sizeY/8+1;
	  }

#ifdef NDEBUG
	  cout << proc << ":bufsize " << bufsize <<"\n";
#endif
	  
	  // Clear active columns from the pattern
	  for (y = 0; y < sizeY; y++) {
	    for (x = 0; x < sizeX; x++) {
	      for (i = 0; i < numValues; i++) {	    
		SetIsActive(x, y, i, false);
	      }
	    }
	  }

	  socketin = (int) server_reply[0];    // TBD JSK
#ifdef NDEBUG
	  cout << proc << "*** rewardValue = " << socketin <<" ***\n";
#endif	  
	  
	  x = y = 0;
	  for (idx=1; idx < bufsize+1; idx++) {
	    t = server_reply[idx];
#ifdef NDEBUG
	    cout << " " << (unsigned char)t;
#endif	    
	    for(j=0;j<8;j++) {
	      if((t&0x80) == 0x80) {
		if(burstUntil == 0) {
		  for (i = 0; i < numValues; i++) {
		    SetIsActive(x, y, i, true);
		  }
		} else {
		  if(_time < burstUntil) {
		    for (i = 0; i < numValues; i++) {
		      SetIsActive(x, y, i, true);
		    }
		  } else {
		    int t = (_time+x*2+y*2+x) % numValues;
		    if(t >= numValues) t = 0;
		    SetIsActive(x, y, t, true);
		  }
		} // else
	      }
	      t = t << 1;
	      x++;
	      if(x == sizeX) {
		x = 0;
		y++;
	      }
	    }
	  }
#ifdef NDEBUG
	  cout << "\n";
	  for (y = 0; y < sizeY; y++) {
	    for (x = 0; x < sizeX; x++) {
	      for (i = 0; i < numValues; i++) {	    
		if(GetIsActive(x, y, i) == true) {
		  cout << "1";
		} else {
		  cout << "0";
		}
	      }
	    }
	    cout << "\n";
	  }
#endif	    
        }
	break;
    case PATTERN_BITMAP:
#ifdef DEBUG
	cout << proc << ":    PATTERN_BITMAP\n";
#endif
	// Apply bitmap test pattern.

	// If this isn't the start of a new trial, no need to update activity.
	if (_time != _pattern->curTrialStartTime) {
	    break;
	}
	// Start by clearing all activity.
	DeactivateAll();

	// If there are no bitmaps given for this TestPattern, do nothing.
#ifdef DEBUG
	cout << proc << ":    size " << _pattern->bitmaps.size() << "\n";
#endif
	if (_pattern->bitmaps.size() == 0) {
	    break;
	}

	numSteps = (int)(_pattern->bitmaps.size());
	step = (numSteps > 0) ? ((_pattern->trialCount - 1) % numSteps) : 0;
#ifdef DEBUG
	cout << proc << ":    trialCount " << _pattern->trialCount << " step " << step <<
	    "\n";
#endif
	// Get a pointer to the current bitmap array.
	bitmap = _pattern->bitmaps[step];

	for (y = 0; y < sizeY; y++) {
	    for (x = 0; x < sizeX; x++) {
		if (bitmap[y * sizeX + x] != 0) {
		  if(burstUntil == 0) {
		    for (i = 0; i < numValues; i++) {
		      SetIsActive(x, y, i, true);
		    }
		  } else {
		    if(_time < burstUntil) {
		      for (i = 0; i < numValues; i++) {
			SetIsActive(x, y, i, true);
		      }
		    } else {
		      int t = (_time+x*2+y*2+x) % numValues;
		      if(t >= numValues) t = 0;
		      SetIsActive(x, y, t, true);
		    }
		  } // else
		}
	    }
	}
	break;
    case PATTERN_IMAGE:
#ifdef DEBUG
	cout << proc << ":    PATTERN_IMAGE\n";
	// Apply image test pattern.
	cout << proc << ":pattern start time " << _pattern->curTrialStartTime << "\n";
	cout << proc << ":images size " << _pattern->images.size() << "\n";
#endif
	// If there are no images given for this Pattern, do nothing.
	if (_pattern->images.size() == 0) {
	    break;
	}
	numSteps = (int)(_pattern->images.size());
	step = (numSteps > 0) ? ((_pattern->trialCount - 1) % numSteps) : 0;
	// Get a pointer to the current ImageInfo.
	imageInfo = _pattern->images[step];

	// If this is the start of a new trial...
	if (_time == _pattern->curTrialStartTime) {
	    if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS) {
		// Determine start and end coordinates.
		int randVal = rand();
#ifdef RANDBUG
		cout << proc << ":rand() " << randVal << " %2 "
		    << randVal % 2 << "\n";
#endif
		if ((randVal % 2) == 0) {
		    // Horizontal movement.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Left to right
			_pattern->startX = 0;
			_pattern->endX = sizeX - imageInfo->contentWidth;
		    } else {
			// Right to left
			_pattern->startX = sizeX - imageInfo->contentWidth;
			_pattern->endX = 0;
		    }

		    // Choose start and end Y positions.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Height " << randVal % (sizeY -
						  imageInfo->contentHeight)
			<< "\n";
#endif
		    _pattern->startY =
			(sizeY <=
			 imageInfo->contentHeight) ? 0 : (randVal %
							  (sizeY -
							   imageInfo->contentHeight));
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Height " << randVal % (sizeY -
						  imageInfo->contentHeight)
			<< "\n";
#endif
		    _pattern->endY =
			(sizeY <=
			 imageInfo->contentHeight) ? 0 : (randVal %
							  (sizeY -
							   imageInfo->contentHeight));
		} else {
		    // Vertical movement.
		    randVal = rand();
#ifdef RANDBUG
		    //randVal = 0;
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Top to bottom
			_pattern->startY = 0;
			_pattern->endY = sizeY - imageInfo->contentHeight;
		    } else {
			// Bottom to top
			_pattern->startY = sizeY - imageInfo->contentHeight;
			_pattern->endY = 0;
		    }

		    // Choose start and end X positions.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Width " << randVal % (sizeY -
						 imageInfo->contentWidth)
			<< "\n";
#endif
		    _pattern->startX =
			(sizeX <=
			 imageInfo->contentWidth) ? 0 : (randVal %
							 (sizeX -
							  imageInfo->contentWidth));
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Width " << randVal % (sizeY -
						 imageInfo->contentWidth)
			<< "\n";
#endif
		    _pattern->endX =
			(sizeX <=
			 imageInfo->contentWidth) ? 0 : (randVal %
							 (sizeX -
							  imageInfo->contentWidth));
		}
	    } else if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS2) {
		// Determine start and end coordinates.
		int randVal = rand();
#ifdef RANDBUG
		cout << proc << ":rand() " << randVal << " %2 "
		    << randVal % 2 << "\n";
#endif
		if ((randVal % 2) == 0) {
		    // Horizontal movement.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Left to right
			_pattern->startX = 0;
			_pattern->endX = sizeX - imageInfo->contentWidth;
		    } else {
			// Right to left
			_pattern->startX = sizeX - imageInfo->contentWidth;
			_pattern->endX = 0;
		    }

		    // Choose start and end Y position.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Height " << randVal % (sizeY -
						  imageInfo->contentHeight)
			<< "\n";
#endif
		    _pattern->startY = _pattern->endY =
			(sizeY <=
			 imageInfo->contentHeight) ? 0 : (randVal %
							  (sizeY -
							   imageInfo->contentHeight));
		} else {
		    // Vertical movement.
		    randVal = rand();
#ifdef RANDBUG
		    //randVal = 0;
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Top to bottom
			_pattern->startY = 0;
			_pattern->endY = sizeY - imageInfo->contentHeight;
		    } else {
			// Bottom to top
			_pattern->startY = sizeY - imageInfo->contentHeight;
			_pattern->endY = 0;
		    }

		    // Choose start and end X position.
		    randVal = rand();
#ifdef RANDBUG
		    // randVal = 5;
		    cout << proc << ":rand() " << randVal <<
			" %Width " << randVal % (sizeY -
						 imageInfo->contentWidth)
			<< "\n";
#endif
		    _pattern->startX = _pattern->endX =
			(sizeX <=
			 imageInfo->contentWidth) ? 0 : (randVal %
							 (sizeX -
							  imageInfo->contentWidth));
		}
	    } else {
		// Image doesn't move.
		_pattern->startX = _pattern->startY =
		    _pattern->endX = _pattern->endY = 0;
	    }
	}
	// Start by clearing all activity.
	DeactivateAll();

	// Clear the image processing buffer.
	memset(buffer, 0, sizeX * sizeY * sizeof(int));

	// Determine current image position.
	int posX, posY;
	if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS) {
	    posX = (int)(((float)(_pattern->endX - _pattern->startX)) / ((float)
									 (_pattern->nextTrialStartTime - _pattern->curTrialStartTime - 1)) * ((float)(_time - _pattern->curTrialStartTime)) + _pattern->startX + 0.5f);
	    posY = (int)(((float)(_pattern->endY - _pattern->startY)) / ((float)
									 (_pattern->nextTrialStartTime - _pattern->curTrialStartTime - 1)) * ((float)(_time - _pattern->curTrialStartTime)) + _pattern->startY + 0.5f);
	} else if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS2) {
	    if (_pattern->endX > _pattern->startX) {
		posY = _pattern->startY;
		posX = _pattern->startX + (_time - _pattern->curTrialStartTime);
		if (posX > _pattern->endX)
		    posX = _pattern->endX - (posX - _pattern->endX);
	    } else if (_pattern->endX < _pattern->startX) {
		posY = _pattern->startY;
		posX = _pattern->startX - (_time - _pattern->curTrialStartTime);
		if (posX < _pattern->endX)
		    posX = _pattern->endX + (_pattern->endX - posX);
	    }
	    if (_pattern->endY > _pattern->startY) {
		posX = _pattern->startX;
		posY = _pattern->startY + (_time - _pattern->curTrialStartTime);
		if (posY > _pattern->endY)
		    posY = _pattern->endY - (posY - _pattern->endY);
	    } else if (_pattern->endY < _pattern->startY) {
		posX = _pattern->startX;
		posY = _pattern->startY - (_time - _pattern->curTrialStartTime);
		if (posY < _pattern->endY)
		    posY = _pattern->endY + (_pattern->endY - posY);
	    }
	} else {
	    posX = _pattern->startX;
	    posY = _pattern->startY;
	}

	int destX, destY, srcX, srcY;

	for (y = 0; y < imageInfo->contentHeight; y++) {
	    destY = posY + y;

	    if (destY < 0)
		continue;
	    if (destY >= sizeY)
		break;

	    srcY = imageInfo->contentY + y;

	    for (x = 0; x < imageInfo->contentWidth; x++) {
		destX = posX + x;

		if (destX < 0)
		    continue;
		if (destX >= sizeX)
		    break;

		srcX = imageInfo->contentX + x;

		if (imageInfo->data[srcY * imageInfo->width + srcX] > 0) {
		    buffer[destX + (destY * sizeX)] = 1;
		}
		//cout << buffer[destX + (destY * sizeX)] << " ";
	    }
	    //cout << "\n";
	}

	bool cur_on, center_on;
	int surround_on_count, surround_off_count;

	for (x = 0; x < sizeX; x++) {
	    for (y = 0; y < sizeY; y++) {
		surround_on_count = 0;
		surround_off_count = 0;

		for (x1 = Max(0, x - 1); x1 < Min(sizeX, x + 2); x1++) {
		    for (y1 = Max(0, y - 1); y1 < Min(sizeY, y + 2); y1++) {
			cur_on = (buffer[x1 + (y1 * sizeX)]
				  == 1);

			if ((x1 == x) && (y1 == y)) {
			    center_on = cur_on;
			} else {
			    if (cur_on) {
				surround_on_count++;
			    } else {
				surround_off_count++;
			    }
			}
		    }
		}

		// On-center, off-surround in value 0.
		if (center_on && (surround_off_count >= 2)) {
		    SetIsActive(x, y, 0, true);
		}
		// Off-center, on-surround in value 1.
		if ((GetNumValues() > 1) && (center_on == false)
		    && (surround_on_count >= 2)) {
		    SetIsActive(x, y, 1, true);
		}
	    }
	}
	break;
    case PATTERN_INPUT:
#ifdef DEBUG
	cout << proc << ":    PATTERN_INPUT\n";
	// Apply image test pattern.
	cout << proc << ":pattern start time " << _pattern->curTrialStartTime << "\n";
	cout << proc << ":images size " << _pattern->images.size() << "\n";
#endif
	// If there are no images given for this Pattern, do nothing.
	if (_pattern->images.size() == 0) {
	    break;
	}
	numSteps = (int)(_pattern->images.size());
	step = (numSteps > 0) ? ((_pattern->trialCount - 1) % numSteps) : 0;
	// Get a pointer to the current ImageInfo.
	imageInfo = _pattern->images[step];

	// If this is the start of a new trial...
	if (_time == _pattern->curTrialStartTime) {
	    if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS) {
		// Determine start and end coordinates.
		int randVal = rand();
#ifdef RANDBUG
		cout << proc << ":rand() " << randVal << " %2 "
		    << randVal % 2 << "\n";
#endif
		if ((randVal % 2) == 0) {
		    // Horizontal movement.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Left to right
			_pattern->startX = 0;
			_pattern->endX = sizeX - imageInfo->contentWidth;
		    } else {
			// Right to left
			_pattern->startX = sizeX - imageInfo->contentWidth;
			_pattern->endX = 0;
		    }

		    // Choose start and end Y positions.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Height " << randVal % (sizeY -
						  imageInfo->contentHeight)
			<< "\n";
#endif
		    _pattern->startY =
			(sizeY <=
			 imageInfo->contentHeight) ? 0 : (randVal %
							  (sizeY -
							   imageInfo->contentHeight));
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Height " << randVal % (sizeY -
						  imageInfo->contentHeight)
			<< "\n";
#endif
		    _pattern->endY =
			(sizeY <=
			 imageInfo->contentHeight) ? 0 : (randVal %
							  (sizeY -
							   imageInfo->contentHeight));
		} else {
		    // Vertical movement.
		    randVal = rand();
#ifdef RANDBUG
		    //randVal = 0;
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Top to bottom
			_pattern->startY = 0;
			_pattern->endY = sizeY - imageInfo->contentHeight;
		    } else {
			// Bottom to top
			_pattern->startY = sizeY - imageInfo->contentHeight;
			_pattern->endY = 0;
		    }

		    // Choose start and end X positions.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Width " << randVal % (sizeY -
						 imageInfo->contentWidth)
			<< "\n";
#endif
		    _pattern->startX =
			(sizeX <=
			 imageInfo->contentWidth) ? 0 : (randVal %
							 (sizeX -
							  imageInfo->contentWidth));
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Width " << randVal % (sizeY -
						 imageInfo->contentWidth)
			<< "\n";
#endif
		    _pattern->endX =
			(sizeX <=
			 imageInfo->contentWidth) ? 0 : (randVal %
							 (sizeX -
							  imageInfo->contentWidth));
		}
	    } else if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS2) {
		// Determine start and end coordinates.
		int randVal = rand();
#ifdef RANDBUG
		cout << proc << ":rand() " << randVal << " %2 "
		    << randVal % 2 << "\n";
#endif
		if ((randVal % 2) == 0) {
		    // Horizontal movement.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Left to right
			_pattern->startX = 0;
			_pattern->endX = sizeX - imageInfo->contentWidth;
		    } else {
			// Right to left
			_pattern->startX = sizeX - imageInfo->contentWidth;
			_pattern->endX = 0;
		    }

		    // Choose start and end Y position.
		    randVal = rand();
#ifdef RANDBUG
		    cout << proc << ":rand() " << randVal <<
			" %Height " << randVal % (sizeY -
						  imageInfo->contentHeight)
			<< "\n";
#endif
		    _pattern->startY = _pattern->endY =
			(sizeY <=
			 imageInfo->contentHeight) ? 0 : (randVal %
							  (sizeY -
							   imageInfo->contentHeight));
		} else {
		    // Vertical movement.
		    randVal = rand();
#ifdef RANDBUG
		    //randVal = 0;
		    cout << proc << ":rand() " << randVal <<
			" %2 " << randVal % 2 << "\n";
#endif
		    if ((randVal % 2) == 0) {
			// Top to bottom
			_pattern->startY = 0;
			_pattern->endY = sizeY - imageInfo->contentHeight;
		    } else {
			// Bottom to top
			_pattern->startY = sizeY - imageInfo->contentHeight;
			_pattern->endY = 0;
		    }

		    // Choose start and end X position.
		    randVal = rand();
#ifdef RANDBUG
		    // randVal = 5;
		    cout << proc << ":rand() " << randVal <<
			" %Width " << randVal % (sizeY -
						 imageInfo->contentWidth)
			<< "\n";
#endif
		    _pattern->startX = _pattern->endX =
			(sizeX <=
			 imageInfo->contentWidth) ? 0 : (randVal %
							 (sizeX -
							  imageInfo->contentWidth));
		}
	    } else {
		// Image doesn't move.
		_pattern->startX = _pattern->startY =
		    _pattern->endX = _pattern->endY = 0;
	    }
	}
	// Start by clearing all activity.
	DeactivateAll();

	// Clear the image processing buffer.
	memset(buffer, 0, sizeX * sizeY * sizeof(int));

	// Determine current image position.
	//int posX, posY;
	if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS) {
	    posX = (int)(((float)(_pattern->endX - _pattern->startX)) / ((float)
									 (_pattern->nextTrialStartTime - _pattern->curTrialStartTime - 1)) * ((float)(_time - _pattern->curTrialStartTime)) + _pattern->startX + 0.5f);
	    posY = (int)(((float)(_pattern->endY - _pattern->startY)) / ((float)
									 (_pattern->nextTrialStartTime - _pattern->curTrialStartTime - 1)) * ((float)(_time - _pattern->curTrialStartTime)) + _pattern->startY + 0.5f);
	} else if (_pattern->imageMotion == PATTERN_IMAGE_MOTION_ACROSS2) {
	    if (_pattern->endX > _pattern->startX) {
		posY = _pattern->startY;
		posX = _pattern->startX + (_time - _pattern->curTrialStartTime);
		if (posX > _pattern->endX)
		    posX = _pattern->endX - (posX - _pattern->endX);
	    } else if (_pattern->endX < _pattern->startX) {
		posY = _pattern->startY;
		posX = _pattern->startX - (_time - _pattern->curTrialStartTime);
		if (posX < _pattern->endX)
		    posX = _pattern->endX + (_pattern->endX - posX);
	    }
	    if (_pattern->endY > _pattern->startY) {
		posX = _pattern->startX;
		posY = _pattern->startY + (_time - _pattern->curTrialStartTime);
		if (posY > _pattern->endY)
		    posY = _pattern->endY - (posY - _pattern->endY);
	    } else if (_pattern->endY < _pattern->startY) {
		posX = _pattern->startX;
		posY = _pattern->startY - (_time - _pattern->curTrialStartTime);
		if (posY < _pattern->endY)
		    posY = _pattern->endY + (_pattern->endY - posY);
	    }
	} else {
	    posX = _pattern->startX;
	    posY = _pattern->startY;
	}

	//int destX, destY, srcX, srcY;

	for (y = 0; y < imageInfo->contentHeight; y++) {
	    destY = posY + y;

	    if (destY < 0)
		continue;
	    if (destY >= sizeY)
		break;

	    srcY = imageInfo->contentY + y;

	    for (x = 0; x < imageInfo->contentWidth; x++) {
		destX = posX + x;

		if (destX < 0)
		    continue;
		if (destX >= sizeX)
		    break;

		srcX = imageInfo->contentX + x;

		if (imageInfo->data[srcY * imageInfo->width + srcX] > 0) {
		    buffer[destX + (destY * sizeX)] = 1;
		}
	    }
	}

	//bool cur_on, center_on;
	//int surround_on_count, surround_off_count;

	for (x = 0; x < sizeX; x++) {
	    for (y = 0; y < sizeY; y++) {
		surround_on_count = 0;
		surround_off_count = 0;

		for (x1 = Max(0, x - 1); x1 < Min(sizeX, x + 2); x1++) {
		    for (y1 = Max(0, y - 1); y1 < Min(sizeY, y + 2); y1++) {
			cur_on = (buffer[x1 + (y1 * sizeX)]
				  == 1);

			if ((x1 == x) && (y1 == y)) {
			    center_on = cur_on;
			} else {
			    if (cur_on) {
				surround_on_count++;
			    } else {
				surround_off_count++;
			    }
			}
		    }
		}

		// On-center, off-surround in value 0.
		if (center_on && (surround_off_count >= 2)) {
		    SetIsActive(x, y, 0, true);
		}
		// Off-center, on-surround in value 1.
		if ((GetNumValues() > 1) && (center_on == false)
		    && (surround_on_count >= 2)) {
		    SetIsActive(x, y, 1, true);
		}
	    }
	}

	break;
    }  // end switch(_pattern->type)
}
