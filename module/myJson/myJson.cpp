#include "myJson.h"
#include <iostream>
 

MyJson::MyJson()
{

}

MyJson::~MyJson()
{
    
}

int MyJson::parse(const char* str)
{
    Parse(str);
    return 0;
}

std::string MyJson::toString()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    Accept(writer);
    return buffer.GetString();
}


int MyJson::test()
{
    // 1. 把 JSON 解析至 DOM。
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document d;
    d.Parse(json);
 
    // 2. 利用 DOM 作出修改。
    rapidjson::Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
 
    // 3. 把 DOM 转换（stringify）成 JSON。
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
 
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    return 0;
}
