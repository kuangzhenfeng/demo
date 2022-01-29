#ifndef __MY_JSON_H__
#define __MY_JSON_H__

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class MyJson: public rapidjson::Document
{
public:
    MyJson();
    ~MyJson();

    static int test();
    int parse(const char* str);
    std::string toString();


private:


};



#endif