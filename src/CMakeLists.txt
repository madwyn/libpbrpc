# Required cmake version
cmake_minimum_required(VERSION 2.8.4)
project(pbrpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindProtobuf)

find_package(Protobuf REQUIRED)

set(pbrpc_SRCS ServiceManager.cc)

add_library(pbrpc SHARED ${pbrpc_SRCS})

target_link_libraries(pbrpc
    pbrpc_proto
    protobuf
)

target_include_directories(pbrpc PUBLIC "${pbrpc_SOURCE_DIR}")

install(TARGETS pbrpc DESTINATION lib)
