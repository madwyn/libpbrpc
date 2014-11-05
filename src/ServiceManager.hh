#ifndef __ServiceManager_HH_INCLUDED_
#define __ServiceManager_HH_INCLUDED_

#include <map>
#include <string>

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>

#include <pbrpc.pb.h>

#include "ServiceRPC.hh"
#include "MethodRPC.hh"
#include "ControllerRPC.hh"


namespace pbrpc {

using ::std::string;
using ::std::map;
using ::google::protobuf::Service;
using ::google::protobuf::RpcController;

class ServiceManager {
public:
    ServiceManager();
    virtual ~ServiceManager();

    void init(void);
    void dest(void);
    void handleRPC(const char *data, const size_t len, string &ret);
    void regService(Service *service);

private:
    void freeServices(void);
    inline       Service*    getService   (const string &serviceName) const;
    inline const ServiceRPC* getServiceRPC(const string &serviceName) const;
    inline const MethodRPC*  getMethod    (const string &serviceName, const string &methodName) const;

    bool isValidParams(const char *data, const size_t len, ControllerRPC *controller) const;
    bool isValidRequest(const Request &request, ControllerRPC *controller) const;
    bool isValidVersion(const string &version) const;
    bool isExistService(const string &serviceName) const;

    // services in a map
    map<string, ServiceRPC> _services;
};

}

#endif //__ServiceManager_HH_INCLUDED_
