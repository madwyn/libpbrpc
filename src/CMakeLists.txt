cmake_minimum_required(VERSION 2.8.4)

project(pbrpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(WIN32 AND BUILD_SHARED_LIBS AND MSVC)
    add_definitions("-DPROTOBUF_USE_DLLS")
endif()

include(FindProtobuf)
find_package(Protobuf REQUIRED)

include_directories(
    ${PROTOBUF_ROOT}/src
    ${pbrpc_proto_BINARY_DIR}
    ${pbrpc_BINARY_DIR}
)

link_directories(
    ${libprotobuf_BINARY_DIR}
)

include(GenerateExportHeader)

set(pbrpc_SRCS
    pbrpc/ServiceManager.cc
)

set(pbrpc_HDRS
    pbrpc/config.h
    pbrpc/ControllerRPC.hh
    pbrpc/MethodRPC.hh
    pbrpc/ServiceManager.hh
    pbrpc/ServiceRPC.hh
)

add_library(pbrpc ${pbrpc_SRCS})

if(NOT BUILD_SHARED_LIBS)
add_definitions(-DPBRPC_BUILT_AS_STATIC)
endif()

GENERATE_EXPORT_HEADER(pbrpc
             BASE_NAME         PBRPC
             EXPORT_MACRO_NAME PBRPC_EXPORT
             EXPORT_FILE_NAME  pbrpc_export.h
             STATIC_DEFINE     PBRPC_BUILT_AS_STATIC
)

target_link_libraries(pbrpc
    pbrpc_proto
)

set(INS_INCLUDE_DIR
    "/pbrpc"
)

set(INS_TARGETS
    pbrpc
)

# Install
install(TARGETS ${INS_TARGETS}
    RUNTIME DESTINATION bin COMPONENT applications
    LIBRARY DESTINATION lib COMPONENT libraries
    ARCHIVE DESTINATION lib COMPONENT libraries
)

install(FILES ${pbrpc_HDRS} DESTINATION "include${INS_INCLUDE_DIR}" COMPONENT headers)
