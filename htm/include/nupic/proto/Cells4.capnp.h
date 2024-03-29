// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: Cells4.capnp

#ifndef CAPNP_INCLUDED_d5c4908fa0384eda_
#define CAPNP_INCLUDED_d5c4908fa0384eda_

#include <capnp/generated-header-support.h>

#if CAPNP_VERSION != 6001
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif

#include <nupic/proto/Cell.capnp.h>
#include <nupic/proto/RandomProto.capnp.h>
#include <nupic/proto/Segment.capnp.h>
#include <nupic/proto/SegmentUpdate.capnp.h>

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(f05a853537bc6df0);

}  // namespace schemas
}  // namespace capnp


struct Cells4Proto {
  Cells4Proto() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(f05a853537bc6df0, 14, 7)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class Cells4Proto::Reader {
public:
  typedef Cells4Proto Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::uint16_t getVersion() const;

  inline bool getOwnsMemory() const;

  inline bool hasRng() const;
  inline  ::RandomProto::Reader getRng() const;

  inline  ::uint32_t getNColumns() const;

  inline  ::uint32_t getNCellsPerCol() const;

  inline  ::uint32_t getActivationThreshold() const;

  inline  ::uint32_t getMinThreshold() const;

  inline  ::uint32_t getNewSynapseCount() const;

  inline  ::uint32_t getNIterations() const;

  inline  ::uint32_t getNLrnIterations() const;

  inline  ::uint32_t getSegUpdateValidDuration() const;

  inline float getInitSegFreq() const;

  inline float getPermInitial() const;

  inline float getPermConnected() const;

  inline float getPermMax() const;

  inline float getPermDec() const;

  inline float getPermInc() const;

  inline float getGlobalDecay() const;

  inline bool getDoPooling() const;

  inline  ::uint32_t getPamLength() const;

  inline  ::uint32_t getMaxInfBacktrack() const;

  inline  ::uint32_t getMaxLrnBacktrack() const;

  inline  ::uint32_t getMaxSeqLength() const;

  inline  ::uint32_t getLearnedSeqLength() const;

  inline float getAvgLearnedSeqLength() const;

  inline  ::uint32_t getMaxAge() const;

  inline  ::uint8_t getVerbosity() const;

  inline  ::uint32_t getMaxSegmentsPerCell() const;

  inline  ::uint32_t getMaxSynapsesPerSegment() const;

  inline bool getCheckSynapseConsistency() const;

  inline bool getResetCalled() const;

  inline float getAvgInputDensity() const;

  inline  ::uint32_t getPamCounter() const;

  inline bool hasLearnActiveStateT() const;
  inline  ::CStateProto::Reader getLearnActiveStateT() const;

  inline bool hasLearnActiveStateT1() const;
  inline  ::CStateProto::Reader getLearnActiveStateT1() const;

  inline bool hasLearnPredictedStateT() const;
  inline  ::CStateProto::Reader getLearnPredictedStateT() const;

  inline bool hasLearnPredictedStateT1() const;
  inline  ::CStateProto::Reader getLearnPredictedStateT1() const;

  inline bool hasCells() const;
  inline  ::capnp::List< ::CellProto>::Reader getCells() const;

  inline bool hasSegmentUpdates() const;
  inline  ::capnp::List< ::SegmentUpdateProto>::Reader getSegmentUpdates() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Cells4Proto::Builder {
public:
  typedef Cells4Proto Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::uint16_t getVersion();
  inline void setVersion( ::uint16_t value);

  inline bool getOwnsMemory();
  inline void setOwnsMemory(bool value);

  inline bool hasRng();
  inline  ::RandomProto::Builder getRng();
  inline void setRng( ::RandomProto::Reader value);
  inline  ::RandomProto::Builder initRng();
  inline void adoptRng(::capnp::Orphan< ::RandomProto>&& value);
  inline ::capnp::Orphan< ::RandomProto> disownRng();

  inline  ::uint32_t getNColumns();
  inline void setNColumns( ::uint32_t value);

  inline  ::uint32_t getNCellsPerCol();
  inline void setNCellsPerCol( ::uint32_t value);

  inline  ::uint32_t getActivationThreshold();
  inline void setActivationThreshold( ::uint32_t value);

  inline  ::uint32_t getMinThreshold();
  inline void setMinThreshold( ::uint32_t value);

  inline  ::uint32_t getNewSynapseCount();
  inline void setNewSynapseCount( ::uint32_t value);

  inline  ::uint32_t getNIterations();
  inline void setNIterations( ::uint32_t value);

  inline  ::uint32_t getNLrnIterations();
  inline void setNLrnIterations( ::uint32_t value);

  inline  ::uint32_t getSegUpdateValidDuration();
  inline void setSegUpdateValidDuration( ::uint32_t value);

  inline float getInitSegFreq();
  inline void setInitSegFreq(float value);

  inline float getPermInitial();
  inline void setPermInitial(float value);

  inline float getPermConnected();
  inline void setPermConnected(float value);

  inline float getPermMax();
  inline void setPermMax(float value);

  inline float getPermDec();
  inline void setPermDec(float value);

  inline float getPermInc();
  inline void setPermInc(float value);

  inline float getGlobalDecay();
  inline void setGlobalDecay(float value);

  inline bool getDoPooling();
  inline void setDoPooling(bool value);

  inline  ::uint32_t getPamLength();
  inline void setPamLength( ::uint32_t value);

  inline  ::uint32_t getMaxInfBacktrack();
  inline void setMaxInfBacktrack( ::uint32_t value);

  inline  ::uint32_t getMaxLrnBacktrack();
  inline void setMaxLrnBacktrack( ::uint32_t value);

  inline  ::uint32_t getMaxSeqLength();
  inline void setMaxSeqLength( ::uint32_t value);

  inline  ::uint32_t getLearnedSeqLength();
  inline void setLearnedSeqLength( ::uint32_t value);

  inline float getAvgLearnedSeqLength();
  inline void setAvgLearnedSeqLength(float value);

  inline  ::uint32_t getMaxAge();
  inline void setMaxAge( ::uint32_t value);

  inline  ::uint8_t getVerbosity();
  inline void setVerbosity( ::uint8_t value);

  inline  ::uint32_t getMaxSegmentsPerCell();
  inline void setMaxSegmentsPerCell( ::uint32_t value);

  inline  ::uint32_t getMaxSynapsesPerSegment();
  inline void setMaxSynapsesPerSegment( ::uint32_t value);

  inline bool getCheckSynapseConsistency();
  inline void setCheckSynapseConsistency(bool value);

  inline bool getResetCalled();
  inline void setResetCalled(bool value);

  inline float getAvgInputDensity();
  inline void setAvgInputDensity(float value);

  inline  ::uint32_t getPamCounter();
  inline void setPamCounter( ::uint32_t value);

  inline bool hasLearnActiveStateT();
  inline  ::CStateProto::Builder getLearnActiveStateT();
  inline void setLearnActiveStateT( ::CStateProto::Reader value);
  inline  ::CStateProto::Builder initLearnActiveStateT();
  inline void adoptLearnActiveStateT(::capnp::Orphan< ::CStateProto>&& value);
  inline ::capnp::Orphan< ::CStateProto> disownLearnActiveStateT();

  inline bool hasLearnActiveStateT1();
  inline  ::CStateProto::Builder getLearnActiveStateT1();
  inline void setLearnActiveStateT1( ::CStateProto::Reader value);
  inline  ::CStateProto::Builder initLearnActiveStateT1();
  inline void adoptLearnActiveStateT1(::capnp::Orphan< ::CStateProto>&& value);
  inline ::capnp::Orphan< ::CStateProto> disownLearnActiveStateT1();

  inline bool hasLearnPredictedStateT();
  inline  ::CStateProto::Builder getLearnPredictedStateT();
  inline void setLearnPredictedStateT( ::CStateProto::Reader value);
  inline  ::CStateProto::Builder initLearnPredictedStateT();
  inline void adoptLearnPredictedStateT(::capnp::Orphan< ::CStateProto>&& value);
  inline ::capnp::Orphan< ::CStateProto> disownLearnPredictedStateT();

  inline bool hasLearnPredictedStateT1();
  inline  ::CStateProto::Builder getLearnPredictedStateT1();
  inline void setLearnPredictedStateT1( ::CStateProto::Reader value);
  inline  ::CStateProto::Builder initLearnPredictedStateT1();
  inline void adoptLearnPredictedStateT1(::capnp::Orphan< ::CStateProto>&& value);
  inline ::capnp::Orphan< ::CStateProto> disownLearnPredictedStateT1();

  inline bool hasCells();
  inline  ::capnp::List< ::CellProto>::Builder getCells();
  inline void setCells( ::capnp::List< ::CellProto>::Reader value);
  inline  ::capnp::List< ::CellProto>::Builder initCells(unsigned int size);
  inline void adoptCells(::capnp::Orphan< ::capnp::List< ::CellProto>>&& value);
  inline ::capnp::Orphan< ::capnp::List< ::CellProto>> disownCells();

  inline bool hasSegmentUpdates();
  inline  ::capnp::List< ::SegmentUpdateProto>::Builder getSegmentUpdates();
  inline void setSegmentUpdates( ::capnp::List< ::SegmentUpdateProto>::Reader value);
  inline  ::capnp::List< ::SegmentUpdateProto>::Builder initSegmentUpdates(unsigned int size);
  inline void adoptSegmentUpdates(::capnp::Orphan< ::capnp::List< ::SegmentUpdateProto>>&& value);
  inline ::capnp::Orphan< ::capnp::List< ::SegmentUpdateProto>> disownSegmentUpdates();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Cells4Proto::Pipeline {
public:
  typedef Cells4Proto Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::RandomProto::Pipeline getRng();
  inline  ::CStateProto::Pipeline getLearnActiveStateT();
  inline  ::CStateProto::Pipeline getLearnActiveStateT1();
  inline  ::CStateProto::Pipeline getLearnPredictedStateT();
  inline  ::CStateProto::Pipeline getLearnPredictedStateT1();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline  ::uint16_t Cells4Proto::Reader::getVersion() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t Cells4Proto::Builder::getVersion() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setVersion( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Cells4Proto::Reader::getOwnsMemory() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<16>() * ::capnp::ELEMENTS);
}

inline bool Cells4Proto::Builder::getOwnsMemory() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<16>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setOwnsMemory(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<16>() * ::capnp::ELEMENTS, value);
}

inline bool Cells4Proto::Reader::hasRng() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasRng() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::RandomProto::Reader Cells4Proto::Reader::getRng() const {
  return ::capnp::_::PointerHelpers< ::RandomProto>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::RandomProto::Builder Cells4Proto::Builder::getRng() {
  return ::capnp::_::PointerHelpers< ::RandomProto>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::RandomProto::Pipeline Cells4Proto::Pipeline::getRng() {
  return  ::RandomProto::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void Cells4Proto::Builder::setRng( ::RandomProto::Reader value) {
  ::capnp::_::PointerHelpers< ::RandomProto>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::RandomProto::Builder Cells4Proto::Builder::initRng() {
  return ::capnp::_::PointerHelpers< ::RandomProto>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::adoptRng(
    ::capnp::Orphan< ::RandomProto>&& value) {
  ::capnp::_::PointerHelpers< ::RandomProto>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::RandomProto> Cells4Proto::Builder::disownRng() {
  return ::capnp::_::PointerHelpers< ::RandomProto>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::uint32_t Cells4Proto::Reader::getNColumns() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getNColumns() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setNColumns( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getNCellsPerCol() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getNCellsPerCol() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setNCellsPerCol( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getActivationThreshold() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getActivationThreshold() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setActivationThreshold( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMinThreshold() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMinThreshold() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMinThreshold( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getNewSynapseCount() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getNewSynapseCount() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setNewSynapseCount( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getNIterations() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getNIterations() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setNIterations( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getNLrnIterations() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getNLrnIterations() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setNLrnIterations( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getSegUpdateValidDuration() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getSegUpdateValidDuration() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setSegUpdateValidDuration( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getInitSegFreq() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getInitSegFreq() {
  return _builder.getDataField<float>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setInitSegFreq(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getPermInitial() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getPermInitial() {
  return _builder.getDataField<float>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPermInitial(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getPermConnected() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<11>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getPermConnected() {
  return _builder.getDataField<float>(
      ::capnp::bounded<11>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPermConnected(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<11>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getPermMax() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<12>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getPermMax() {
  return _builder.getDataField<float>(
      ::capnp::bounded<12>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPermMax(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<12>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getPermDec() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<13>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getPermDec() {
  return _builder.getDataField<float>(
      ::capnp::bounded<13>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPermDec(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<13>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getPermInc() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<14>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getPermInc() {
  return _builder.getDataField<float>(
      ::capnp::bounded<14>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPermInc(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<14>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getGlobalDecay() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<15>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getGlobalDecay() {
  return _builder.getDataField<float>(
      ::capnp::bounded<15>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setGlobalDecay(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<15>() * ::capnp::ELEMENTS, value);
}

inline bool Cells4Proto::Reader::getDoPooling() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<17>() * ::capnp::ELEMENTS);
}

inline bool Cells4Proto::Builder::getDoPooling() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<17>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setDoPooling(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<17>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getPamLength() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<16>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getPamLength() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<16>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPamLength( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<16>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMaxInfBacktrack() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<17>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMaxInfBacktrack() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<17>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMaxInfBacktrack( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<17>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMaxLrnBacktrack() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<18>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMaxLrnBacktrack() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<18>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMaxLrnBacktrack( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<18>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMaxSeqLength() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<19>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMaxSeqLength() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<19>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMaxSeqLength( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<19>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getLearnedSeqLength() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<20>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getLearnedSeqLength() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<20>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setLearnedSeqLength( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<20>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getAvgLearnedSeqLength() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<21>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getAvgLearnedSeqLength() {
  return _builder.getDataField<float>(
      ::capnp::bounded<21>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setAvgLearnedSeqLength(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<21>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMaxAge() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<22>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMaxAge() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<22>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMaxAge( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<22>() * ::capnp::ELEMENTS, value);
}

inline  ::uint8_t Cells4Proto::Reader::getVerbosity() const {
  return _reader.getDataField< ::uint8_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint8_t Cells4Proto::Builder::getVerbosity() {
  return _builder.getDataField< ::uint8_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setVerbosity( ::uint8_t value) {
  _builder.setDataField< ::uint8_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMaxSegmentsPerCell() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<23>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMaxSegmentsPerCell() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<23>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMaxSegmentsPerCell( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<23>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getMaxSynapsesPerSegment() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<24>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getMaxSynapsesPerSegment() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<24>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setMaxSynapsesPerSegment( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<24>() * ::capnp::ELEMENTS, value);
}

inline bool Cells4Proto::Reader::getCheckSynapseConsistency() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<18>() * ::capnp::ELEMENTS);
}

inline bool Cells4Proto::Builder::getCheckSynapseConsistency() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<18>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setCheckSynapseConsistency(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<18>() * ::capnp::ELEMENTS, value);
}

inline bool Cells4Proto::Reader::getResetCalled() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<19>() * ::capnp::ELEMENTS);
}

inline bool Cells4Proto::Builder::getResetCalled() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<19>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setResetCalled(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<19>() * ::capnp::ELEMENTS, value);
}

inline float Cells4Proto::Reader::getAvgInputDensity() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<25>() * ::capnp::ELEMENTS);
}

inline float Cells4Proto::Builder::getAvgInputDensity() {
  return _builder.getDataField<float>(
      ::capnp::bounded<25>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setAvgInputDensity(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<25>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Cells4Proto::Reader::getPamCounter() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<26>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Cells4Proto::Builder::getPamCounter() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<26>() * ::capnp::ELEMENTS);
}
inline void Cells4Proto::Builder::setPamCounter( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<26>() * ::capnp::ELEMENTS, value);
}

inline bool Cells4Proto::Reader::hasLearnActiveStateT() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasLearnActiveStateT() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::CStateProto::Reader Cells4Proto::Reader::getLearnActiveStateT() const {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::CStateProto::Builder Cells4Proto::Builder::getLearnActiveStateT() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::CStateProto::Pipeline Cells4Proto::Pipeline::getLearnActiveStateT() {
  return  ::CStateProto::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void Cells4Proto::Builder::setLearnActiveStateT( ::CStateProto::Reader value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::CStateProto::Builder Cells4Proto::Builder::initLearnActiveStateT() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::adoptLearnActiveStateT(
    ::capnp::Orphan< ::CStateProto>&& value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::CStateProto> Cells4Proto::Builder::disownLearnActiveStateT() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline bool Cells4Proto::Reader::hasLearnActiveStateT1() const {
  return !_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasLearnActiveStateT1() {
  return !_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline  ::CStateProto::Reader Cells4Proto::Reader::getLearnActiveStateT1() const {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline  ::CStateProto::Builder Cells4Proto::Builder::getLearnActiveStateT1() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::CStateProto::Pipeline Cells4Proto::Pipeline::getLearnActiveStateT1() {
  return  ::CStateProto::Pipeline(_typeless.getPointerField(2));
}
#endif  // !CAPNP_LITE
inline void Cells4Proto::Builder::setLearnActiveStateT1( ::CStateProto::Reader value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline  ::CStateProto::Builder Cells4Proto::Builder::initLearnActiveStateT1() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::init(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::adoptLearnActiveStateT1(
    ::capnp::Orphan< ::CStateProto>&& value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::adopt(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::CStateProto> Cells4Proto::Builder::disownLearnActiveStateT1() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::disown(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}

inline bool Cells4Proto::Reader::hasLearnPredictedStateT() const {
  return !_reader.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasLearnPredictedStateT() {
  return !_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS).isNull();
}
inline  ::CStateProto::Reader Cells4Proto::Reader::getLearnPredictedStateT() const {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_reader.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}
inline  ::CStateProto::Builder Cells4Proto::Builder::getLearnPredictedStateT() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::CStateProto::Pipeline Cells4Proto::Pipeline::getLearnPredictedStateT() {
  return  ::CStateProto::Pipeline(_typeless.getPointerField(3));
}
#endif  // !CAPNP_LITE
inline void Cells4Proto::Builder::setLearnPredictedStateT( ::CStateProto::Reader value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::set(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS), value);
}
inline  ::CStateProto::Builder Cells4Proto::Builder::initLearnPredictedStateT() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::init(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::adoptLearnPredictedStateT(
    ::capnp::Orphan< ::CStateProto>&& value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::adopt(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::CStateProto> Cells4Proto::Builder::disownLearnPredictedStateT() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::disown(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}

inline bool Cells4Proto::Reader::hasLearnPredictedStateT1() const {
  return !_reader.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasLearnPredictedStateT1() {
  return !_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS).isNull();
}
inline  ::CStateProto::Reader Cells4Proto::Reader::getLearnPredictedStateT1() const {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_reader.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}
inline  ::CStateProto::Builder Cells4Proto::Builder::getLearnPredictedStateT1() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::get(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::CStateProto::Pipeline Cells4Proto::Pipeline::getLearnPredictedStateT1() {
  return  ::CStateProto::Pipeline(_typeless.getPointerField(4));
}
#endif  // !CAPNP_LITE
inline void Cells4Proto::Builder::setLearnPredictedStateT1( ::CStateProto::Reader value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::set(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS), value);
}
inline  ::CStateProto::Builder Cells4Proto::Builder::initLearnPredictedStateT1() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::init(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::adoptLearnPredictedStateT1(
    ::capnp::Orphan< ::CStateProto>&& value) {
  ::capnp::_::PointerHelpers< ::CStateProto>::adopt(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::CStateProto> Cells4Proto::Builder::disownLearnPredictedStateT1() {
  return ::capnp::_::PointerHelpers< ::CStateProto>::disown(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}

inline bool Cells4Proto::Reader::hasCells() const {
  return !_reader.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasCells() {
  return !_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List< ::CellProto>::Reader Cells4Proto::Reader::getCells() const {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::CellProto>>::get(_reader.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS));
}
inline  ::capnp::List< ::CellProto>::Builder Cells4Proto::Builder::getCells() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::CellProto>>::get(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::setCells( ::capnp::List< ::CellProto>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::CellProto>>::set(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List< ::CellProto>::Builder Cells4Proto::Builder::initCells(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::CellProto>>::init(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), size);
}
inline void Cells4Proto::Builder::adoptCells(
    ::capnp::Orphan< ::capnp::List< ::CellProto>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::CellProto>>::adopt(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List< ::CellProto>> Cells4Proto::Builder::disownCells() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::CellProto>>::disown(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS));
}

inline bool Cells4Proto::Reader::hasSegmentUpdates() const {
  return !_reader.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS).isNull();
}
inline bool Cells4Proto::Builder::hasSegmentUpdates() {
  return !_builder.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List< ::SegmentUpdateProto>::Reader Cells4Proto::Reader::getSegmentUpdates() const {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::SegmentUpdateProto>>::get(_reader.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS));
}
inline  ::capnp::List< ::SegmentUpdateProto>::Builder Cells4Proto::Builder::getSegmentUpdates() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::SegmentUpdateProto>>::get(_builder.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS));
}
inline void Cells4Proto::Builder::setSegmentUpdates( ::capnp::List< ::SegmentUpdateProto>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::SegmentUpdateProto>>::set(_builder.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List< ::SegmentUpdateProto>::Builder Cells4Proto::Builder::initSegmentUpdates(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::SegmentUpdateProto>>::init(_builder.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS), size);
}
inline void Cells4Proto::Builder::adoptSegmentUpdates(
    ::capnp::Orphan< ::capnp::List< ::SegmentUpdateProto>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::SegmentUpdateProto>>::adopt(_builder.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List< ::SegmentUpdateProto>> Cells4Proto::Builder::disownSegmentUpdates() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::SegmentUpdateProto>>::disown(_builder.getPointerField(
      ::capnp::bounded<6>() * ::capnp::POINTERS));
}


#endif  // CAPNP_INCLUDED_d5c4908fa0384eda_
