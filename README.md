# libpbrpc
The aim is to build a minimal protobuf RPC lib using [Google's Protocol Buffers](https://code.google.com/p/protobuf).

libpbrpc is flexible as it is not bound to the http server, it's a lightweight middleware.

# Dependencies
The only dependency is [Protocol Buffers](https://github.com/google/protobuf).

# How to use
To use this lib is really simple. First define `ServiceManager` some where in your code.
```c
ServiceManager srvMan;
```

Then the `ServiceManager` only provides two functions:

1. Register a service:
    ```c
    void regService(Service *service);
    ```

2. Handle the RPC message:
    ```c
    void handleRPC(const char *data, const size_t len, string &ret);
    ```
    - `data` is the raw Protobuf binary,
    - `len` is the length of the data,
    - `ret` is the result generated, you can send it back directly. (Note: use ret.length() to get the correct length.)

# How it's made
The over all design is really simple:
- Protocol. The RPC protocol is defined in the "pbrpc.proto" file. The protocol took the [JSON RPC 2.0](http://www.jsonrpc.org/specification) as a reference.
- `Service`s. The RPC server provides several `Service`s, and each `Service` has some `Method`s.
- `Method`s. Each `Method` should have input(`params`) and output(`results`).

# Examples
Please take a look of my other repository [pbrpc](https://github.com/madwyn/pbrpc) as a demo which implements a simple RPC server.
