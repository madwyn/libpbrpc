#ifndef __ControllerRPC_HH_INCLUDED_
#define __ControllerRPC_HH_INCLUDED_

#include <string>
#include <google/protobuf/service.h>
#include <pbrpc.pb.h>


namespace pbrpc {

using ::std::string;
using ::google::protobuf::RpcController;
using ::google::protobuf::Closure;
using ::pbrpc::Error;

class ControllerRPC : public RpcController {
public:
             ControllerRPC(void) {Reset();}
    virtual ~ControllerRPC()     {}
    void     Reset()             {_failed = false;}
    bool     Failed()      const {return _failed;}
    string   ErrorText()   const {return _message;}

    void SetFailed(const string &reason) {
        _failed  = true;
        _message = reason;
    }

    void AppendFailed(const string &reason) {
        _message += reason;
    }

    // get the Error object
    Error ErrorObj(void) const {
        Error error;
        error.set_message(ErrorText());
        return error;
    }

    // not in use
    void StartCancel() {}
    bool IsCanceled() const { return false; };
    void NotifyOnCancel(Closure *callback) {};

private:
    bool   _failed;
    string _message;
};

}

#endif //__ControllerRPC_HH_INCLUDED_
