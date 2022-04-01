#ifndef __MY_JSON_H__
#define __MY_JSON_H__

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "common.h"

class MyJsonTest: public ModuleBase
{
public:
    MyJsonTest() : ModuleBase(MODULE_JSON, "MODULE_JSON"){};
    int test();
};


class MyJson: public rapidjson::Document
{
public:
    static int test();
    int parse(const char* str);
    std::string toString();


private:


};



#endif