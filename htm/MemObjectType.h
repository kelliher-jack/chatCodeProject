#pragma once

typedef short MemObjectType;

const MemObjectType MOT_UNDEF = -1;
const MemObjectType MOT_FAST_HASH_TRAY = 0;
const MemObjectType MOT_FAST_LIST_TRAY = 1;
const MemObjectType MOT_PROXIMAL_SYNAPSE = 2;
const MemObjectType MOT_DISTAL_SYNAPSE = 3;
const MemObjectType MOT_SEGMENT = 4;
const MemObjectType MOT_CELL = 5;
const MemObjectType MOT_SEGMENT_UPDATE_INFO = 6;
const MemObjectType MOT_SYNAPSE = 7;
const MemObjectType MOT_COLUMN = 8;
const MemObjectType MOT_NEURON = 9;
const MemObjectType MOT_NSEGMENT = 10;
const MemObjectType MOT_NSYNAPSE = 11;
const short NUM_MEM_OBJECT_TYPES = 12;	// Update This!

// Object type chunk lengths
const int FAST_HASH_TRAY_CHUNK_LENGTH   = 10000;
const int FAST_LIST_TRAY_CHUNK_LENGTH   = 10000;
const int PROXIMAL_SYNAPSE_CHUNK_LENGTH = 10000;
const int DISTAL_SYNAPSE_CHUNK_LENGTH   = 10000;
const int SYNAPSE_CHUNK_LENGTH = 10000;

const int SEGMENT_CHUNK_LENGTH = 1000;
const int CELL_CHUNK_LENGTH    = 1000;
const int NEURON_CHUNK_LENGTH  = 1000;
const int COLUMN_CHUNK_LENGTH  = 1000;
const int SEGMENT_UPDATE_INFO_CHUNK_LENGTH = 1000;


