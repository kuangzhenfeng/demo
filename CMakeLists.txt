cmake_minimum_required(VERSION 3.1)
project(demo)

find_program(CCACHE "ccache")
if(CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif(CCACHE)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fsanitize=address -fno-omit-frame-pointer -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_C_COMPILER "/usr/bin/gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

find_package(Threads)
find_package(Protobuf REQUIRED)

IF(PROTOBUF_FOUND)
    MESSAGE(STATUS "protobuf library found")
ELSE()
    MESSAGE(FATAL_ERROR "protobuf library is needed but cant be found")
ENDIF()

set(PROJECT_DIR         ${PROJECT_SOURCE_DIR})
set(MAIN_DIR            ${PROJECT_DIR}/main)
set(MODULE_DIR          ${PROJECT_DIR}/module)
set(MY_LIB_DIR          ${PROJECT_DIR}/myLib)
set(THIRD_PART_DIR      ${PROJECT_DIR}/thirdlib)

# module
set(COMMON_DIR                  ${MODULE_DIR}/common)
set(MY_NEURON_DIR               ${MODULE_DIR}/myNeuron)
set(MY_THREAD_POOL_THIRD_DIR    ${MODULE_DIR}/myThreadPoolThird)
set(MY_MEMORY_POOL_DIR          ${MODULE_DIR}/myMemoryPool)
set(MY_THREAD_POOL_DIR          ${MODULE_DIR}/myThreadPool)
set(MY_IO_MULTIPLEXING_DIR      ${MODULE_DIR}/myIOMultiplexing)
set(MY_CONDITION_VARIABLE_DIR   ${MODULE_DIR}/myConditionVariable)
set(MY_JSON_DIR                 ${MODULE_DIR}/myJson)
set(MY_SMART_POINTER_DIR        ${MODULE_DIR}/mySmartPointer)
set(MY_PROTOBUF_DIR             ${MODULE_DIR}/myProtobuf)
set(MY_SOCKET_DIR               ${MODULE_DIR}/mySocket)
set(MY_IPC_DIR                  ${MODULE_DIR}/myIPC)
set(MY_REACTOR_DIR              ${MODULE_DIR}/myReactor)

# my lib
set(LIB_MY_TIMER_DIR    ${MY_LIB_DIR}/timer)
set(LIB_MY_LOG_DIR      ${MY_LIB_DIR}/log)

# third lib
set(LIB_BOOST_DIR       ${THIRD_PART_DIR}/boost_1_76_0)
set(LIB_RAPIDJSON_DIR   ${THIRD_PART_DIR}/rapidjson-1.1.0)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${MY_PROTOBUF_DIR}/pb/myProtobuf.proto)

include_directories(
    ${COMMON_DIR}/include
    ${MY_NEURON_DIR}/include
    ${MY_THREAD_POOL_THIRD_DIR}/include
    ${MY_MEMORY_POOL_DIR}/include
    ${MY_THREAD_POOL_DIR}/include
    ${MY_IO_MULTIPLEXING_DIR}/include
    ${MY_CONDITION_VARIABLE_DIR}/include
    ${MY_JSON_DIR}/include
    ${MY_SMART_POINTER_DIR}/include
    ${MY_PROTOBUF_DIR}/include
    ${MY_SOCKET_DIR}/include
    ${MY_IPC_DIR}/include
    ${MY_REACTOR_DIR}/include

    # protobuf
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}

    # my lib
    ${LIB_MY_TIMER_DIR}/include
    ${LIB_MY_LOG_DIR}/include

    # third lib
    ${LIB_BOOST_DIR}/include
    ${LIB_RAPIDJSON_DIR}/include
)

set(SOURCE_FILES
    ${MAIN_DIR}/demo.cpp
    ${COMMON_DIR}/commonTest.cpp
    ${MY_NEURON_DIR}/myNeuron.cpp
    ${MY_THREAD_POOL_THIRD_DIR}/myThreadPoolThird.cpp
    ${MY_MEMORY_POOL_DIR}/myMemoryPool.cpp
    ${MY_THREAD_POOL_DIR}/myThreadPool.cpp
    ${MY_IO_MULTIPLEXING_DIR}/myIOMultiplexing.cpp
    ${MY_CONDITION_VARIABLE_DIR}/myConditionVariable.cpp
    ${MY_JSON_DIR}/myJson.cpp
    ${MY_SMART_POINTER_DIR}/mySmartPointer.cpp
    ${MY_PROTOBUF_DIR}/myProtobuf.cpp
    ${MY_SOCKET_DIR}/mySocket.cpp
    ${MY_IPC_DIR}/myIPC.cpp
    ${MY_REACTOR_DIR}/myReactor.cpp

    # protobuf
    ${PROTO_SRCS}

    # my lib
    ${LIB_MY_TIMER_DIR}/myTimer.cpp
    ${LIB_MY_LOG_DIR}/myLog.cpp
)


# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROTOBUF_LIBRARIES} 
    # -lrt
)

# find_library(boost_lib NAMES boost PATHS ${LIB_BOOST_DIR}/boost)
# target_link_libraries(${PROJECT_NAME} ${boost_lib})