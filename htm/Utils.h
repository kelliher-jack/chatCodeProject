#pragma once

#include <stddef.h>

typedef unsigned int UInt;
typedef short nValue;   // normall considered a value between 0 and 1
                        // and as a positive int between 0 and 32767 (16 bit)
                        // or between 0 & 1 with 0.000030519 increments.
typedef float fValue;



#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Max(a, b) ((a) > (b) ? (a) : (b))

struct Point {
    int X, Y;

     Point() {
	X = Y = 0;
    } Point(int x, int y) {
	X = x;
	Y = y;
    }
};

struct DataPoint {
    int X, Y, Index;

     DataPoint() {
	X = Y = Index = 0;
    } DataPoint(int x, int y, int index) {
	X = x;
	Y = y;
	Index = index;
    }
};

struct WeightedDataPoint:public DataPoint {
    float Weight, Distance;

     WeightedDataPoint():DataPoint() {
	Weight = 0.0f;
	Distance = 0.0f;
    } WeightedDataPoint(int x, int y, int index, float weight,
			float distance):DataPoint(x, y, index) {
	Weight = weight;
	Distance = distance;
    }
};

class Area {
 public:
    Area(void) {
	MinX = MaxX = MinY = MaxY = 0;
    };
    Area(int minX, int minY, int maxX, int maxY) {
	MinX = minX;
	MaxX = maxX;
	MinY = minY;
	MaxY = maxY;
    };

    /// Properties

    int MinX, MaxX, MinY, MaxY;
    int area;

    /// Methods

    int GetArea() {
	return (MaxX - MinX + 1) * (MaxY - MinY + 1);
    }
};
