/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef shop_TYPES_H
#define shop_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




class ProductAnswer;

class Bill;

typedef struct _ProductAnswer__isset {
  _ProductAnswer__isset() : sensorId(false), preis(false), menge(false) {}
  bool sensorId :1;
  bool preis :1;
  bool menge :1;
} _ProductAnswer__isset;

class ProductAnswer : public virtual ::apache::thrift::TBase {
 public:

  ProductAnswer(const ProductAnswer&);
  ProductAnswer& operator=(const ProductAnswer&);
  ProductAnswer() : sensorId(0), preis(0), menge(0) {
  }

  virtual ~ProductAnswer() throw();
  int32_t sensorId;
  int32_t preis;
  int32_t menge;

  _ProductAnswer__isset __isset;

  void __set_sensorId(const int32_t val);

  void __set_preis(const int32_t val);

  void __set_menge(const int32_t val);

  bool operator == (const ProductAnswer & rhs) const
  {
    if (!(sensorId == rhs.sensorId))
      return false;
    if (!(preis == rhs.preis))
      return false;
    if (!(menge == rhs.menge))
      return false;
    return true;
  }
  bool operator != (const ProductAnswer &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProductAnswer & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ProductAnswer &a, ProductAnswer &b);

inline std::ostream& operator<<(std::ostream& out, const ProductAnswer& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _Bill__isset {
  _Bill__isset() : produkte(false) {}
  bool produkte :1;
} _Bill__isset;

class Bill : public virtual ::apache::thrift::TBase {
 public:

  Bill(const Bill&);
  Bill& operator=(const Bill&);
  Bill() {
  }

  virtual ~Bill() throw();
  std::vector<ProductAnswer>  produkte;

  _Bill__isset __isset;

  void __set_produkte(const std::vector<ProductAnswer> & val);

  bool operator == (const Bill & rhs) const
  {
    if (!(produkte == rhs.produkte))
      return false;
    return true;
  }
  bool operator != (const Bill &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Bill & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Bill &a, Bill &b);

inline std::ostream& operator<<(std::ostream& out, const Bill& obj)
{
  obj.printTo(out);
  return out;
}



#endif
