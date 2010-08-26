// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "hyperset.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace hyperset;

class hypersetHandler : virtual public hypersetIf {
    public:
        hypersetHandler() {
            // Your initialization goes here
        }

        int32_t count(const std::vector<SetOp> & query) {
            // Your implementation goes here
            printf("count\n");
        }

        int32_t add(const std::string& name, const std::vector<int32_t> & vals) {
            // Your implementation goes here
            printf("add\n");
        }

        int32_t save() {
            // Your implementation goes here
            printf("save\n");
        }

};

int main(int argc, char **argv) {
    int port = 9090;
    shared_ptr<hypersetHandler> handler(new hypersetHandler());
    shared_ptr<TProcessor> processor(new hypersetProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}

