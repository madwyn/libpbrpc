# Required cmake version
cmake_minimum_required(VERSION 2.8.4)

project(pbrpc_proto)

# The .proto source files
file(GLOB proto_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

if (NOT PROTOBUF_ROOT)
    find_package(Protobuf REQUIRED)
else()
    set(PROTOBUF_SRC_ROOT_FOLDER ${PROTOBUF_ROOT})
    set(PROTOBUF_PROTOC_EXECUTABLE ${protoc_BINARY_DIR}/protoc)
    include(FindProtobufExt)
endif()

# Generate the proto message files
PROTOBUF_GENERATE_CPP(proto_SRCS proto_HDRS ${proto_FILES})

set_source_files_properties(${proto_FILES} PROPERTIES GENERATED TRUE)

# Build library
add_library(pbrpc_proto
    SHARED
    ${proto_SRCS}
    ${proto_HDRS}
)

add_dependencies(pbrpc_proto protoc)

target_link_libraries(pbrpc_proto protobuf)

target_include_directories(pbrpc_proto PUBLIC "${pbrpc_proto_BINARY_DIR}")

install(TARGETS pbrpc_proto DESTINATION lib)
