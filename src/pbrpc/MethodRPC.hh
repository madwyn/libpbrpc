#ifndef __MethodRPC_HH_INCLUDED_
#define __MethodRPC_HH_INCLUDED_

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>


namespace pbrpc {

using ::google::protobuf::MethodDescriptor;
using ::google::protobuf::Message;
using ::google::protobuf::Service;

/** \brief This class describes a RPC Method object.
*/
class MethodRPC {
public:
    const MethodDescriptor *descriptor; /**< method descriptor */
    const Message          *request;    /**< parameters */
    const Message          *response;   /**< result */

    MethodRPC(const MethodDescriptor *descriptor,
              const Message          *request,
              const Message          *response)
               : descriptor(descriptor), request(request), response(response) {}

    MethodRPC(void) : descriptor(NULL), request(NULL), response(NULL) {}
};

}

#endif //__MethodRPC_HH_INCLUDED_
