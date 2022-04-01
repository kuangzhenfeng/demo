#ifndef __MY_PROTOBUF_H__
#define __MY_PROTOBUF_H__

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "common.h"

class MyProtobufTest : public ModuleBase
{
public:
    MyProtobufTest() : ModuleBase(MODULE_PROTOBUF, "MODULE_PROTOBUF"){};
    int test();
};

class MyProtobuf
{
public:
    MyProtobuf(){};
    static int test();

private:

};


#endif