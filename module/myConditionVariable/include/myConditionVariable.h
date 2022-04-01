#ifndef __MY_CONDITION_VARIABLE_H__
#define __MY_CONDITION_VARIABLE_H__

#include "common.h"

class MyConditionVariableTest : public ModuleBase
{
public:
    MyConditionVariableTest() : ModuleBase(MODULE_CONDITION_VARIABLE, "MODULE_CONDITION_VARIABLE"){};
    int test();
};


#endif