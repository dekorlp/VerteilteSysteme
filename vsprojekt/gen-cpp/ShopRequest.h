/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ShopRequest_H
#define ShopRequest_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "shop_types.h"



#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class ShopRequestIf {
 public:
  virtual ~ShopRequestIf() {}
  virtual void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge) = 0;
  virtual void getBill(Bill& _return) = 0;
  virtual void ping() = 0;
};

class ShopRequestIfFactory {
 public:
  typedef ShopRequestIf Handler;

  virtual ~ShopRequestIfFactory() {}

  virtual ShopRequestIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(ShopRequestIf* /* handler */) = 0;
};

class ShopRequestIfSingletonFactory : virtual public ShopRequestIfFactory {
 public:
  ShopRequestIfSingletonFactory(const boost::shared_ptr<ShopRequestIf>& iface) : iface_(iface) {}
  virtual ~ShopRequestIfSingletonFactory() {}

  virtual ShopRequestIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(ShopRequestIf* /* handler */) {}

 protected:
  boost::shared_ptr<ShopRequestIf> iface_;
};

class ShopRequestNull : virtual public ShopRequestIf {
 public:
  virtual ~ShopRequestNull() {}
  void buyProducts(ProductAnswer& /* _return */, const int32_t /* sendorId */, const int32_t /* bestellMenge */) {
    return;
  }
  void getBill(Bill& /* _return */) {
    return;
  }
  void ping() {
    return;
  }
};

typedef struct _ShopRequest_buyProducts_args__isset {
  _ShopRequest_buyProducts_args__isset() : sendorId(false), bestellMenge(false) {}
  bool sendorId :1;
  bool bestellMenge :1;
} _ShopRequest_buyProducts_args__isset;

class ShopRequest_buyProducts_args {
 public:

  ShopRequest_buyProducts_args(const ShopRequest_buyProducts_args&);
  ShopRequest_buyProducts_args& operator=(const ShopRequest_buyProducts_args&);
  ShopRequest_buyProducts_args() : sendorId(0), bestellMenge(0) {
  }

  virtual ~ShopRequest_buyProducts_args() throw();
  int32_t sendorId;
  int32_t bestellMenge;

  _ShopRequest_buyProducts_args__isset __isset;

  void __set_sendorId(const int32_t val);

  void __set_bestellMenge(const int32_t val);

  bool operator == (const ShopRequest_buyProducts_args & rhs) const
  {
    if (!(sendorId == rhs.sendorId))
      return false;
    if (!(bestellMenge == rhs.bestellMenge))
      return false;
    return true;
  }
  bool operator != (const ShopRequest_buyProducts_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ShopRequest_buyProducts_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ShopRequest_buyProducts_pargs {
 public:


  virtual ~ShopRequest_buyProducts_pargs() throw();
  const int32_t* sendorId;
  const int32_t* bestellMenge;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ShopRequest_buyProducts_result__isset {
  _ShopRequest_buyProducts_result__isset() : success(false) {}
  bool success :1;
} _ShopRequest_buyProducts_result__isset;

class ShopRequest_buyProducts_result {
 public:

  ShopRequest_buyProducts_result(const ShopRequest_buyProducts_result&);
  ShopRequest_buyProducts_result& operator=(const ShopRequest_buyProducts_result&);
  ShopRequest_buyProducts_result() {
  }

  virtual ~ShopRequest_buyProducts_result() throw();
  ProductAnswer success;

  _ShopRequest_buyProducts_result__isset __isset;

  void __set_success(const ProductAnswer& val);

  bool operator == (const ShopRequest_buyProducts_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ShopRequest_buyProducts_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ShopRequest_buyProducts_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ShopRequest_buyProducts_presult__isset {
  _ShopRequest_buyProducts_presult__isset() : success(false) {}
  bool success :1;
} _ShopRequest_buyProducts_presult__isset;

class ShopRequest_buyProducts_presult {
 public:


  virtual ~ShopRequest_buyProducts_presult() throw();
  ProductAnswer* success;

  _ShopRequest_buyProducts_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class ShopRequest_getBill_args {
 public:

  ShopRequest_getBill_args(const ShopRequest_getBill_args&);
  ShopRequest_getBill_args& operator=(const ShopRequest_getBill_args&);
  ShopRequest_getBill_args() {
  }

  virtual ~ShopRequest_getBill_args() throw();

  bool operator == (const ShopRequest_getBill_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const ShopRequest_getBill_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ShopRequest_getBill_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ShopRequest_getBill_pargs {
 public:


  virtual ~ShopRequest_getBill_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ShopRequest_getBill_result__isset {
  _ShopRequest_getBill_result__isset() : success(false) {}
  bool success :1;
} _ShopRequest_getBill_result__isset;

class ShopRequest_getBill_result {
 public:

  ShopRequest_getBill_result(const ShopRequest_getBill_result&);
  ShopRequest_getBill_result& operator=(const ShopRequest_getBill_result&);
  ShopRequest_getBill_result() {
  }

  virtual ~ShopRequest_getBill_result() throw();
  Bill success;

  _ShopRequest_getBill_result__isset __isset;

  void __set_success(const Bill& val);

  bool operator == (const ShopRequest_getBill_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ShopRequest_getBill_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ShopRequest_getBill_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ShopRequest_getBill_presult__isset {
  _ShopRequest_getBill_presult__isset() : success(false) {}
  bool success :1;
} _ShopRequest_getBill_presult__isset;

class ShopRequest_getBill_presult {
 public:


  virtual ~ShopRequest_getBill_presult() throw();
  Bill* success;

  _ShopRequest_getBill_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class ShopRequest_ping_args {
 public:

  ShopRequest_ping_args(const ShopRequest_ping_args&);
  ShopRequest_ping_args& operator=(const ShopRequest_ping_args&);
  ShopRequest_ping_args() {
  }

  virtual ~ShopRequest_ping_args() throw();

  bool operator == (const ShopRequest_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const ShopRequest_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ShopRequest_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ShopRequest_ping_pargs {
 public:


  virtual ~ShopRequest_ping_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ShopRequest_ping_result {
 public:

  ShopRequest_ping_result(const ShopRequest_ping_result&);
  ShopRequest_ping_result& operator=(const ShopRequest_ping_result&);
  ShopRequest_ping_result() {
  }

  virtual ~ShopRequest_ping_result() throw();

  bool operator == (const ShopRequest_ping_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const ShopRequest_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ShopRequest_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ShopRequest_ping_presult {
 public:


  virtual ~ShopRequest_ping_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class ShopRequestClient : virtual public ShopRequestIf {
 public:
  ShopRequestClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  ShopRequestClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge);
  void send_buyProducts(const int32_t sendorId, const int32_t bestellMenge);
  void recv_buyProducts(ProductAnswer& _return);
  void getBill(Bill& _return);
  void send_getBill();
  void recv_getBill(Bill& _return);
  void ping();
  void send_ping();
  void recv_ping();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class ShopRequestProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<ShopRequestIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (ShopRequestProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_buyProducts(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getBill(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  ShopRequestProcessor(boost::shared_ptr<ShopRequestIf> iface) :
    iface_(iface) {
    processMap_["buyProducts"] = &ShopRequestProcessor::process_buyProducts;
    processMap_["getBill"] = &ShopRequestProcessor::process_getBill;
    processMap_["ping"] = &ShopRequestProcessor::process_ping;
  }

  virtual ~ShopRequestProcessor() {}
};

class ShopRequestProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  ShopRequestProcessorFactory(const ::boost::shared_ptr< ShopRequestIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< ShopRequestIfFactory > handlerFactory_;
};

class ShopRequestMultiface : virtual public ShopRequestIf {
 public:
  ShopRequestMultiface(std::vector<boost::shared_ptr<ShopRequestIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~ShopRequestMultiface() {}
 protected:
  std::vector<boost::shared_ptr<ShopRequestIf> > ifaces_;
  ShopRequestMultiface() {}
  void add(boost::shared_ptr<ShopRequestIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->buyProducts(_return, sendorId, bestellMenge);
    }
    ifaces_[i]->buyProducts(_return, sendorId, bestellMenge);
    return;
  }

  void getBill(Bill& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getBill(_return);
    }
    ifaces_[i]->getBill(_return);
    return;
  }

  void ping() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping();
    }
    ifaces_[i]->ping();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class ShopRequestConcurrentClient : virtual public ShopRequestIf {
 public:
  ShopRequestConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  ShopRequestConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge);
  int32_t send_buyProducts(const int32_t sendorId, const int32_t bestellMenge);
  void recv_buyProducts(ProductAnswer& _return, const int32_t seqid);
  void getBill(Bill& _return);
  int32_t send_getBill();
  void recv_getBill(Bill& _return, const int32_t seqid);
  void ping();
  int32_t send_ping();
  void recv_ping(const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif



#endif
