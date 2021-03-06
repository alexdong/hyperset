// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "hyperset.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TNonblockingServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "core.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace std;

class hypersetHandler : virtual public hyperset::hypersetIf {
    public:
        hypersetHandler(const string &db) {
            m_db = db;
            LOG(INFO) << "Loading from file: " << m_db;
            hyperset::load(m_db, m_setmap);
            LOG(INFO) << "Hyperset ready";
        }

        int32_t calc(const string& query) {
            return hyperset::calc(m_setmap, query);            
        }

        void    add(const string& name, const vector<int32_t> & vals) {
            hyperset::add(m_setmap, name, vals);
        }

        void    save() {
            hyperset::save(m_db, m_setmap);
        }

    private:
        hyperset::setmap_t m_setmap;
        string   m_db;

        hypersetHandler() {}
};

DEFINE_int32(hyperset_port, 9091, 
        "Which port hyperset server listens on");
DEFINE_string(hyperset_db, "set.db", 
        "Where to put the database file. ");
int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    google::ParseCommandLineFlags(&argc, &argv, true);

    shared_ptr<hypersetHandler> handler(
            new hypersetHandler(FLAGS_hyperset_db));
    shared_ptr<TProcessor> processor(
            new hyperset::hypersetProcessor(handler));
    shared_ptr<TProtocolFactory> protocolFactory(
            new TBinaryProtocolFactory());

    TNonblockingServer server(processor, protocolFactory, FLAGS_hyperset_port);
    LOG(INFO) << "Hyperset begining at port " << FLAGS_hyperset_port;

    try {
        server.serve();
    } catch(std::exception const& e) {
        LOG(INFO) << "Exception in main: %s" << e.what();
    }

    LOG(INFO) << "Hyperset quitting";
    return 0;
}
