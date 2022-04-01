#ifndef __COMMON_TEST_H__
#define __COMMON_TEST_H__

#include <map>
#include <memory>
#include "common.h"



class CommonTest
{
public:
    CommonTest();
    static CommonTest *Instance() { static CommonTest s_obj; return &s_obj;}
    int test(MODULE_TYPE_E moduleType);
    int testAll();

private:
    std::map<MODULE_TYPE_E, std::shared_ptr<ModuleBase>> moduleMap;
};


#endif