#ifndef __MY_EXAMPLE_H__
#define __MY_EXAMPLE_H__

#include "common.h"

class MyExampleTest : public ModuleBase
{
public:
    MyExampleTest() : ModuleBase(MODULE_MAX, "MODULE_MAX"){};
    int test();
};

class MyExample
{
public:
    MyExample(){};

private:

};




#endif