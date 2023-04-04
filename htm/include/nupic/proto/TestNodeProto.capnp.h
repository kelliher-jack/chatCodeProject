// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: TestNodeProto.capnp

#ifndef CAPNP_INCLUDED_acbfb584b84b791c_
#define CAPNP_INCLUDED_acbfb584b84b791c_

#include <capnp/generated-header-support.h>

#if CAPNP_VERSION != 6001
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(848435be3fac2986);

}  // namespace schemas
}  // namespace capnp


struct TestNodeProto {
  TestNodeProto() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(848435be3fac2986, 8, 6)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class TestNodeProto::Reader {
public:
  typedef TestNodeProto Reads;

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

  inline  ::int32_t getInt32Param() const;

  inline  ::uint32_t getUint32Param() const;

  inline  ::int64_t getInt64Param() const;

  inline  ::uint64_t getUint64Param() const;

  inline float getReal32Param() const;

  inline double getReal64Param() const;

  inline bool hasStringParam() const;
  inline  ::capnp::Text::Reader getStringParam() const;

  inline bool hasReal32ArrayParam() const;
  inline  ::capnp::List<float>::Reader getReal32ArrayParam() const;

  inline bool hasInt64ArrayParam() const;
  inline  ::capnp::List< ::int64_t>::Reader getInt64ArrayParam() const;

  inline  ::uint32_t getIterations() const;

  inline  ::uint32_t getOutputElementCount() const;

  inline  ::int64_t getDelta() const;

  inline bool getShouldCloneParam() const;

  inline bool hasUnclonedParam() const;
  inline  ::capnp::List< ::uint32_t>::Reader getUnclonedParam() const;

  inline bool hasUnclonedInt64ArrayParam() const;
  inline  ::capnp::List< ::capnp::List< ::int64_t>>::Reader getUnclonedInt64ArrayParam() const;

  inline  ::uint32_t getNodeCount() const;

  inline bool getBoolParam() const;

  inline bool hasBoolArrayParam() const;
  inline  ::capnp::List<bool>::Reader getBoolArrayParam() const;

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

class TestNodeProto::Builder {
public:
  typedef TestNodeProto Builds;

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

  inline  ::int32_t getInt32Param();
  inline void setInt32Param( ::int32_t value);

  inline  ::uint32_t getUint32Param();
  inline void setUint32Param( ::uint32_t value);

  inline  ::int64_t getInt64Param();
  inline void setInt64Param( ::int64_t value);

  inline  ::uint64_t getUint64Param();
  inline void setUint64Param( ::uint64_t value);

  inline float getReal32Param();
  inline void setReal32Param(float value);

  inline double getReal64Param();
  inline void setReal64Param(double value);

  inline bool hasStringParam();
  inline  ::capnp::Text::Builder getStringParam();
  inline void setStringParam( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initStringParam(unsigned int size);
  inline void adoptStringParam(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownStringParam();

  inline bool hasReal32ArrayParam();
  inline  ::capnp::List<float>::Builder getReal32ArrayParam();
  inline void setReal32ArrayParam( ::capnp::List<float>::Reader value);
  inline void setReal32ArrayParam(::kj::ArrayPtr<const float> value);
  inline  ::capnp::List<float>::Builder initReal32ArrayParam(unsigned int size);
  inline void adoptReal32ArrayParam(::capnp::Orphan< ::capnp::List<float>>&& value);
  inline ::capnp::Orphan< ::capnp::List<float>> disownReal32ArrayParam();

  inline bool hasInt64ArrayParam();
  inline  ::capnp::List< ::int64_t>::Builder getInt64ArrayParam();
  inline void setInt64ArrayParam( ::capnp::List< ::int64_t>::Reader value);
  inline void setInt64ArrayParam(::kj::ArrayPtr<const  ::int64_t> value);
  inline  ::capnp::List< ::int64_t>::Builder initInt64ArrayParam(unsigned int size);
  inline void adoptInt64ArrayParam(::capnp::Orphan< ::capnp::List< ::int64_t>>&& value);
  inline ::capnp::Orphan< ::capnp::List< ::int64_t>> disownInt64ArrayParam();

  inline  ::uint32_t getIterations();
  inline void setIterations( ::uint32_t value);

  inline  ::uint32_t getOutputElementCount();
  inline void setOutputElementCount( ::uint32_t value);

  inline  ::int64_t getDelta();
  inline void setDelta( ::int64_t value);

  inline bool getShouldCloneParam();
  inline void setShouldCloneParam(bool value);

  inline bool hasUnclonedParam();
  inline  ::capnp::List< ::uint32_t>::Builder getUnclonedParam();
  inline void setUnclonedParam( ::capnp::List< ::uint32_t>::Reader value);
  inline void setUnclonedParam(::kj::ArrayPtr<const  ::uint32_t> value);
  inline  ::capnp::List< ::uint32_t>::Builder initUnclonedParam(unsigned int size);
  inline void adoptUnclonedParam(::capnp::Orphan< ::capnp::List< ::uint32_t>>&& value);
  inline ::capnp::Orphan< ::capnp::List< ::uint32_t>> disownUnclonedParam();

  inline bool hasUnclonedInt64ArrayParam();
  inline  ::capnp::List< ::capnp::List< ::int64_t>>::Builder getUnclonedInt64ArrayParam();
  inline void setUnclonedInt64ArrayParam( ::capnp::List< ::capnp::List< ::int64_t>>::Reader value);
  inline void setUnclonedInt64ArrayParam(::kj::ArrayPtr<const  ::capnp::List< ::int64_t>::Reader> value);
  inline  ::capnp::List< ::capnp::List< ::int64_t>>::Builder initUnclonedInt64ArrayParam(unsigned int size);
  inline void adoptUnclonedInt64ArrayParam(::capnp::Orphan< ::capnp::List< ::capnp::List< ::int64_t>>>&& value);
  inline ::capnp::Orphan< ::capnp::List< ::capnp::List< ::int64_t>>> disownUnclonedInt64ArrayParam();

  inline  ::uint32_t getNodeCount();
  inline void setNodeCount( ::uint32_t value);

  inline bool getBoolParam();
  inline void setBoolParam(bool value);

  inline bool hasBoolArrayParam();
  inline  ::capnp::List<bool>::Builder getBoolArrayParam();
  inline void setBoolArrayParam( ::capnp::List<bool>::Reader value);
  inline void setBoolArrayParam(::kj::ArrayPtr<const bool> value);
  inline  ::capnp::List<bool>::Builder initBoolArrayParam(unsigned int size);
  inline void adoptBoolArrayParam(::capnp::Orphan< ::capnp::List<bool>>&& value);
  inline ::capnp::Orphan< ::capnp::List<bool>> disownBoolArrayParam();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class TestNodeProto::Pipeline {
public:
  typedef TestNodeProto Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline  ::int32_t TestNodeProto::Reader::getInt32Param() const {
  return _reader.getDataField< ::int32_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int32_t TestNodeProto::Builder::getInt32Param() {
  return _builder.getDataField< ::int32_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setInt32Param( ::int32_t value) {
  _builder.setDataField< ::int32_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t TestNodeProto::Reader::getUint32Param() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t TestNodeProto::Builder::getUint32Param() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setUint32Param( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t TestNodeProto::Reader::getInt64Param() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::int64_t TestNodeProto::Builder::getInt64Param() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setInt64Param( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t TestNodeProto::Reader::getUint64Param() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t TestNodeProto::Builder::getUint64Param() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setUint64Param( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline float TestNodeProto::Reader::getReal32Param() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline float TestNodeProto::Builder::getReal32Param() {
  return _builder.getDataField<float>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setReal32Param(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline double TestNodeProto::Reader::getReal64Param() const {
  return _reader.getDataField<double>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline double TestNodeProto::Builder::getReal64Param() {
  return _builder.getDataField<double>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setReal64Param(double value) {
  _builder.setDataField<double>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline bool TestNodeProto::Reader::hasStringParam() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool TestNodeProto::Builder::hasStringParam() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader TestNodeProto::Reader::getStringParam() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder TestNodeProto::Builder::getStringParam() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void TestNodeProto::Builder::setStringParam( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder TestNodeProto::Builder::initStringParam(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), size);
}
inline void TestNodeProto::Builder::adoptStringParam(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> TestNodeProto::Builder::disownStringParam() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline bool TestNodeProto::Reader::hasReal32ArrayParam() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool TestNodeProto::Builder::hasReal32ArrayParam() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List<float>::Reader TestNodeProto::Reader::getReal32ArrayParam() const {
  return ::capnp::_::PointerHelpers< ::capnp::List<float>>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::capnp::List<float>::Builder TestNodeProto::Builder::getReal32ArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List<float>>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void TestNodeProto::Builder::setReal32ArrayParam( ::capnp::List<float>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List<float>>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline void TestNodeProto::Builder::setReal32ArrayParam(::kj::ArrayPtr<const float> value) {
  ::capnp::_::PointerHelpers< ::capnp::List<float>>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List<float>::Builder TestNodeProto::Builder::initReal32ArrayParam(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List<float>>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), size);
}
inline void TestNodeProto::Builder::adoptReal32ArrayParam(
    ::capnp::Orphan< ::capnp::List<float>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List<float>>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List<float>> TestNodeProto::Builder::disownReal32ArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List<float>>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline bool TestNodeProto::Reader::hasInt64ArrayParam() const {
  return !_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline bool TestNodeProto::Builder::hasInt64ArrayParam() {
  return !_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List< ::int64_t>::Reader TestNodeProto::Reader::getInt64ArrayParam() const {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::get(_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline  ::capnp::List< ::int64_t>::Builder TestNodeProto::Builder::getInt64ArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::get(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline void TestNodeProto::Builder::setInt64ArrayParam( ::capnp::List< ::int64_t>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline void TestNodeProto::Builder::setInt64ArrayParam(::kj::ArrayPtr<const  ::int64_t> value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List< ::int64_t>::Builder TestNodeProto::Builder::initInt64ArrayParam(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::init(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), size);
}
inline void TestNodeProto::Builder::adoptInt64ArrayParam(
    ::capnp::Orphan< ::capnp::List< ::int64_t>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::adopt(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List< ::int64_t>> TestNodeProto::Builder::disownInt64ArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::int64_t>>::disown(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}

inline  ::uint32_t TestNodeProto::Reader::getIterations() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t TestNodeProto::Builder::getIterations() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setIterations( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t TestNodeProto::Reader::getOutputElementCount() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t TestNodeProto::Builder::getOutputElementCount() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setOutputElementCount( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t TestNodeProto::Reader::getDelta() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::int64_t TestNodeProto::Builder::getDelta() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setDelta( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline bool TestNodeProto::Reader::getShouldCloneParam() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<352>() * ::capnp::ELEMENTS);
}

inline bool TestNodeProto::Builder::getShouldCloneParam() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<352>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setShouldCloneParam(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<352>() * ::capnp::ELEMENTS, value);
}

inline bool TestNodeProto::Reader::hasUnclonedParam() const {
  return !_reader.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS).isNull();
}
inline bool TestNodeProto::Builder::hasUnclonedParam() {
  return !_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List< ::uint32_t>::Reader TestNodeProto::Reader::getUnclonedParam() const {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::get(_reader.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}
inline  ::capnp::List< ::uint32_t>::Builder TestNodeProto::Builder::getUnclonedParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::get(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}
inline void TestNodeProto::Builder::setUnclonedParam( ::capnp::List< ::uint32_t>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::set(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS), value);
}
inline void TestNodeProto::Builder::setUnclonedParam(::kj::ArrayPtr<const  ::uint32_t> value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::set(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List< ::uint32_t>::Builder TestNodeProto::Builder::initUnclonedParam(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::init(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS), size);
}
inline void TestNodeProto::Builder::adoptUnclonedParam(
    ::capnp::Orphan< ::capnp::List< ::uint32_t>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::adopt(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List< ::uint32_t>> TestNodeProto::Builder::disownUnclonedParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::uint32_t>>::disown(_builder.getPointerField(
      ::capnp::bounded<3>() * ::capnp::POINTERS));
}

inline bool TestNodeProto::Reader::hasUnclonedInt64ArrayParam() const {
  return !_reader.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS).isNull();
}
inline bool TestNodeProto::Builder::hasUnclonedInt64ArrayParam() {
  return !_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List< ::capnp::List< ::int64_t>>::Reader TestNodeProto::Reader::getUnclonedInt64ArrayParam() const {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::get(_reader.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}
inline  ::capnp::List< ::capnp::List< ::int64_t>>::Builder TestNodeProto::Builder::getUnclonedInt64ArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::get(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}
inline void TestNodeProto::Builder::setUnclonedInt64ArrayParam( ::capnp::List< ::capnp::List< ::int64_t>>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::set(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS), value);
}
inline void TestNodeProto::Builder::setUnclonedInt64ArrayParam(::kj::ArrayPtr<const  ::capnp::List< ::int64_t>::Reader> value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::set(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List< ::capnp::List< ::int64_t>>::Builder TestNodeProto::Builder::initUnclonedInt64ArrayParam(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::init(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS), size);
}
inline void TestNodeProto::Builder::adoptUnclonedInt64ArrayParam(
    ::capnp::Orphan< ::capnp::List< ::capnp::List< ::int64_t>>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::adopt(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List< ::capnp::List< ::int64_t>>> TestNodeProto::Builder::disownUnclonedInt64ArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::capnp::List< ::int64_t>>>::disown(_builder.getPointerField(
      ::capnp::bounded<4>() * ::capnp::POINTERS));
}

inline  ::uint32_t TestNodeProto::Reader::getNodeCount() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<14>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t TestNodeProto::Builder::getNodeCount() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<14>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setNodeCount( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<14>() * ::capnp::ELEMENTS, value);
}

inline bool TestNodeProto::Reader::getBoolParam() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<353>() * ::capnp::ELEMENTS);
}

inline bool TestNodeProto::Builder::getBoolParam() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<353>() * ::capnp::ELEMENTS);
}
inline void TestNodeProto::Builder::setBoolParam(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<353>() * ::capnp::ELEMENTS, value);
}

inline bool TestNodeProto::Reader::hasBoolArrayParam() const {
  return !_reader.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS).isNull();
}
inline bool TestNodeProto::Builder::hasBoolArrayParam() {
  return !_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List<bool>::Reader TestNodeProto::Reader::getBoolArrayParam() const {
  return ::capnp::_::PointerHelpers< ::capnp::List<bool>>::get(_reader.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS));
}
inline  ::capnp::List<bool>::Builder TestNodeProto::Builder::getBoolArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List<bool>>::get(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS));
}
inline void TestNodeProto::Builder::setBoolArrayParam( ::capnp::List<bool>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List<bool>>::set(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), value);
}
inline void TestNodeProto::Builder::setBoolArrayParam(::kj::ArrayPtr<const bool> value) {
  ::capnp::_::PointerHelpers< ::capnp::List<bool>>::set(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List<bool>::Builder TestNodeProto::Builder::initBoolArrayParam(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List<bool>>::init(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), size);
}
inline void TestNodeProto::Builder::adoptBoolArrayParam(
    ::capnp::Orphan< ::capnp::List<bool>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List<bool>>::adopt(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List<bool>> TestNodeProto::Builder::disownBoolArrayParam() {
  return ::capnp::_::PointerHelpers< ::capnp::List<bool>>::disown(_builder.getPointerField(
      ::capnp::bounded<5>() * ::capnp::POINTERS));
}


#endif  // CAPNP_INCLUDED_acbfb584b84b791c_
