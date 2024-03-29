// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: NetworkProto.capnp

#ifndef CAPNP_INCLUDED_bec20a8f487acf07_
#define CAPNP_INCLUDED_bec20a8f487acf07_

#include <capnp/generated-header-support.h>

#if CAPNP_VERSION != 6001
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif

#include <nupic/proto/LinkProto.capnp.h>
#include <nupic/proto/Map.capnp.h>
#include <nupic/proto/RegionProto.capnp.h>

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(b414112f4b6b1b45);

}  // namespace schemas
}  // namespace capnp


struct NetworkProto {
  NetworkProto() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(b414112f4b6b1b45, 0, 2)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class NetworkProto::Reader {
public:
  typedef NetworkProto Reads;

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

  inline bool hasRegions() const;
  inline  ::Map< ::capnp::Text,  ::RegionProto>::Reader getRegions() const;

  inline bool hasLinks() const;
  inline  ::capnp::List< ::LinkProto>::Reader getLinks() const;

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

class NetworkProto::Builder {
public:
  typedef NetworkProto Builds;

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

  inline bool hasRegions();
  inline  ::Map< ::capnp::Text,  ::RegionProto>::Builder getRegions();
  inline void setRegions( ::Map< ::capnp::Text,  ::RegionProto>::Reader value);
  inline  ::Map< ::capnp::Text,  ::RegionProto>::Builder initRegions();
  inline void adoptRegions(::capnp::Orphan< ::Map< ::capnp::Text,  ::RegionProto>>&& value);
  inline ::capnp::Orphan< ::Map< ::capnp::Text,  ::RegionProto>> disownRegions();

  inline bool hasLinks();
  inline  ::capnp::List< ::LinkProto>::Builder getLinks();
  inline void setLinks( ::capnp::List< ::LinkProto>::Reader value);
  inline  ::capnp::List< ::LinkProto>::Builder initLinks(unsigned int size);
  inline void adoptLinks(::capnp::Orphan< ::capnp::List< ::LinkProto>>&& value);
  inline ::capnp::Orphan< ::capnp::List< ::LinkProto>> disownLinks();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class NetworkProto::Pipeline {
public:
  typedef NetworkProto Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Map< ::capnp::Text,  ::RegionProto>::Pipeline getRegions();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline bool NetworkProto::Reader::hasRegions() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool NetworkProto::Builder::hasRegions() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::Map< ::capnp::Text,  ::RegionProto>::Reader NetworkProto::Reader::getRegions() const {
  return ::capnp::_::PointerHelpers< ::Map< ::capnp::Text,  ::RegionProto>>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Map< ::capnp::Text,  ::RegionProto>::Builder NetworkProto::Builder::getRegions() {
  return ::capnp::_::PointerHelpers< ::Map< ::capnp::Text,  ::RegionProto>>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Map< ::capnp::Text,  ::RegionProto>::Pipeline NetworkProto::Pipeline::getRegions() {
  return  ::Map< ::capnp::Text,  ::RegionProto>::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void NetworkProto::Builder::setRegions( ::Map< ::capnp::Text,  ::RegionProto>::Reader value) {
  ::capnp::_::PointerHelpers< ::Map< ::capnp::Text,  ::RegionProto>>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::Map< ::capnp::Text,  ::RegionProto>::Builder NetworkProto::Builder::initRegions() {
  return ::capnp::_::PointerHelpers< ::Map< ::capnp::Text,  ::RegionProto>>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void NetworkProto::Builder::adoptRegions(
    ::capnp::Orphan< ::Map< ::capnp::Text,  ::RegionProto>>&& value) {
  ::capnp::_::PointerHelpers< ::Map< ::capnp::Text,  ::RegionProto>>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Map< ::capnp::Text,  ::RegionProto>> NetworkProto::Builder::disownRegions() {
  return ::capnp::_::PointerHelpers< ::Map< ::capnp::Text,  ::RegionProto>>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline bool NetworkProto::Reader::hasLinks() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool NetworkProto::Builder::hasLinks() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::List< ::LinkProto>::Reader NetworkProto::Reader::getLinks() const {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::LinkProto>>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::capnp::List< ::LinkProto>::Builder NetworkProto::Builder::getLinks() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::LinkProto>>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void NetworkProto::Builder::setLinks( ::capnp::List< ::LinkProto>::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::LinkProto>>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::capnp::List< ::LinkProto>::Builder NetworkProto::Builder::initLinks(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::LinkProto>>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), size);
}
inline void NetworkProto::Builder::adoptLinks(
    ::capnp::Orphan< ::capnp::List< ::LinkProto>>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::List< ::LinkProto>>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::List< ::LinkProto>> NetworkProto::Builder::disownLinks() {
  return ::capnp::_::PointerHelpers< ::capnp::List< ::LinkProto>>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}


#endif  // CAPNP_INCLUDED_bec20a8f487acf07_
