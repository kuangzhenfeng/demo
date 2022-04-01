#ifndef __MY_IO_MULTIPLEXING_H__
#define __MY_IO_MULTIPLEXING_H__

#include "common.h"

class MyIOMultiplexingTest : public ModuleBase
{
public:
    MyIOMultiplexingTest() : ModuleBase(MODULE_IO_MULTIPLEXING, "MODULE_IO_MULTIPLEXING"){};
    int test();
};




int selectTest();
int epollTest();



#endif