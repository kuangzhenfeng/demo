cmake_minimum_required(VERSION 3.1)
project(demo)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fsanitize=address -fno-omit-frame-pointer -std=c++11")

find_package(Threads)
find_package(Protobuf REQUIRED)

set(PROJECT_DIR         ${PROJECT_SOURCE_DIR})
set(MAIN_DIR            ${PROJECT_DIR}/main)
set(MODULE_DIR          ${PROJECT_DIR}/module)
set(MY_LIB_DIR          ${PROJECT_DIR}/myLib)
set(THIRD_PART_DIR      ${PROJECT_DIR}/thirdlib)

# module
set(COMMON_DIR          ${MODULE_DIR}/common)
set(NEURON_DIR          ${MODULE_DIR}/neuron)
set(THREAD_POOL_DIR     ${MODULE_DIR}/threadPool)
set(MY_MEMORY_POOL_DIR  ${MODULE_DIR}/myMemoryPool)
set(MY_THREAD_POOL_DIR  ${MODULE_DIR}/myThreadPool)
set(IO_MULTIPLEXING_DIR ${MODULE_DIR}/IOMultiplexing)
set(MY_CONDITION_VARIABLE_DIR ${MODULE_DIR}/myConditionVariable)
set(MY_JSON_DIR         ${MODULE_DIR}/myJson)
set(SMART_POINTER_DIR   ${MODULE_DIR}/smartPointer)
set(MY_PROTOBUF_DIR     ${MODULE_DIR}/myProtobuf)

# my lib
set(LIB_MY_TIMER_DIR    ${MY_LIB_DIR}/timer)
set(LIB_MY_LOG_DIR      ${MY_LIB_DIR}/log)

# third lib
set(LIB_BOOST_DIR       ${THIRD_PART_DIR}/boost_1_76_0)
set(LIB_RAPIDJSON_DIR   ${THIRD_PART_DIR}/rapidjson-1.1.0)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${MY_PROTOBUF_DIR}/pb/myProtobuf.proto)

include_directories(
    ${COMMON_DIR}/include
    ${NEURON_DIR}/include
    ${THREAD_POOL_DIR}/include
    ${MY_MEMORY_POOL_DIR}/include
    ${MY_THREAD_POOL_DIR}/include
    ${IO_MULTIPLEXING_DIR}/include
    ${MY_CONDITION_VARIABLE_DIR}/include
    ${MY_JSON_DIR}/include
    ${SMART_POINTER_DIR}/include
    ${MY_PROTOBUF_DIR}/include

    # protobuf
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
    ${NEURON_DIR}/neuron.cpp
    ${MY_MEMORY_POOL_DIR}/myMemoryPool.cpp
    ${MY_THREAD_POOL_DIR}/myThreadPool.cpp
    ${IO_MULTIPLEXING_DIR}/IOMultiplexing.cpp
    ${MY_CONDITION_VARIABLE_DIR}/myConditionVariable.cpp
    ${MY_JSON_DIR}/myJson.cpp
    ${SMART_POINTER_DIR}/smartPointer.cpp
    ${MY_PROTOBUF_DIR}/myProtobuf.cpp

    # protobuf
    ${PROTO_SRCS}

    # my lib
    ${LIB_MY_TIMER_DIR}/myTimer.cpp
    ${LIB_MY_LOG_DIR}/myLog.cpp
)


# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${PROTOBUF_LIBRARIES} -lrt)

# find_library(boost_lib NAMES boost PATHS ${LIB_BOOST_DIR}/boost)
# target_link_libraries(${PROJECT_NAME} ${boost_lib})