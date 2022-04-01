#ifndef __MY_REACTOR_H__
#define __MY_REACTOR_H__

#include "common.h"

class MyReactorTest : public ModuleBase
{
public:
    MyReactorTest() : ModuleBase(MODULE_REACTOR, "MODULE_REACTOR"){};
    int test();
};

class MyReactor
{
public:
    MyReactor(){};

private:

};




#endif