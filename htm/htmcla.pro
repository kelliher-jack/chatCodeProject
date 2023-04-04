#-------------------------------------------------
#
# Project created by QtCreator 2014-08-16T22:55:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
           Cell.cpp \
           Neuron.cpp \
	   Columns.cpp \
	   Normalization.cpp \
	   TemporalSpace.cpp \
	   InputSpace.cpp \
           InputData.cpp \
           Classifier.cpp \
           MemManager.cpp \
           Column.cpp \
           ColumnDisp.cpp \
           NetworkManager.cpp \
           NetworkTopology.cpp \
           DistalSynapse.cpp \
           ProximalSynapse.cpp \
           FastHash.cpp \
           Region.cpp \
           Layer.cpp \
           MotorCmd.cpp \
           FastList.cpp \
           Segment.cpp \
           SegmentUpdateInfo.cpp \
           Synapse.cpp \
           htm.cpp \
           ApicalTiebreakTemporalMemory.cpp \
           Connections.cpp \
           SpatialPooler.cpp \
           UnionTemporalPooler.cpp \
           TemporalSpace.cpp \
           Topology.cpp \
           LoggingException.cpp \
           LogItem.cpp \
           Random.cpp \
           App_Picking.cpp \
           View.cpp

HEADERS  += Column.h\
         DataSpace.h\
         NetworkManager.h\
	 NetworkTopology.h \         
         ColumnDisp.h\
         MemObjectType.h\
         MemManager.h\
         MemObject.h\
         Cell.h\
         Neuron.h \
         Normalization.h \
         TemporalSpace.h \
         Columns.h \
         InputSpace.h\
         Classifier.h\
         View.h\
         Utils.h\
         htm.h\
         targetver.h\
         Synapse.h\
         SegmentUpdateInfo.h\
         FastList.h\
         Segment.h\
         FastHash.h\
         Region.h\
         Layer.h\
         MotorCmd.h\
         TemporalSpace.h\         
         DistalSynapse.h\
         ProximalSynapse.h

FORMS    += htm.ui
