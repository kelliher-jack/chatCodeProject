#pragma once

enum SegmentType {
  PROXIMAL_DENDRITE = 0,
  BASAL_DENDRITE    = 1,
  APICAL_DENDRITE   = 2
};

enum GrowthType {
  STATIC_GROWTH     = 0,
  PREDICTIVE_GROWTH = 1,
  MIRRORED_GROWTH   = 2
};

typedef struct _Input {
  SegmentType Type;
  GrowthType Growth;
  int OffsetXinRegion;
  int OffsetYinRegion;
  int InputOffsetX;
  int InputOffsetY;
  int SizeX;
  int SizeY;
  bool Delayed;
} Input;
  
