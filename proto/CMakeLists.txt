cmake_minimum_required(VERSION 2.8.4)

project(pbrpc_proto)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# The .proto source files
file(GLOB proto_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

# set PROTOBUF_ROOT to compile protobuf with protobuf-cmake
if(PROTOBUF_ROOT)
    set(PROTOBUF_SRC_ROOT_FOLDER   ${PROTOBUF_ROOT})
    set(PROTOBUF_LIBRARY           ${libprotobuf_BINARY_DIR})
    set(PROTOBUF_PROTOC_EXECUTABLE ${protoc_BINARY_DIR}/protoc)
    set(PROTOBUF_LIBRARIES
        libprotobuf
    )
    link_directories(${libprotobuf_BINARY_DIR})
endif()

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})

# Generate the proto message files
PROTOBUF_GENERATE_CPP(
    proto_SRCS
    proto_HDRS
    ${proto_FILES}
)

set_source_files_properties(${proto_FILES} PROPERTIES GENERATED TRUE)

# Build library, link as static
add_library(pbrpc_proto
    STATIC
    ${proto_SRCS}
)

add_dependencies(pbrpc_proto protoc)

target_link_libraries(pbrpc_proto
    protobuf
)

set(INS_INCLUDE_DIR
    "/pbrpc"
)

# Install
set(INS_TARGETS
    pbrpc_proto
)

# Install
install(TARGETS ${INS_TARGETS}
    RUNTIME DESTINATION bin COMPONENT applications
    LIBRARY DESTINATION lib COMPONENT libraries
    ARCHIVE DESTINATION lib COMPONENT libraries
)

install(FILES ${proto_HDRS} DESTINATION "include${INS_INCLUDE_DIR}" COMPONENT headers)
