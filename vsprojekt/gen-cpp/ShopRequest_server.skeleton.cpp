// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ShopRequest.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class ShopRequestHandler : virtual public ShopRequestIf {
 public:
  ShopRequestHandler() {
    // Your initialization goes here
  }

  void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge) {
    // Your implementation goes here
    printf("buyProducts\n");
  }

  void getBill(Bill& _return) {
    // Your implementation goes here
    printf("getBill\n");
  }

  void ping() {
    // Your implementation goes here
    printf("ping\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ShopRequestHandler> handler(new ShopRequestHandler());
  shared_ptr<TProcessor> processor(new ShopRequestProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

