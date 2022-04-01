#ifndef __MY_IPC_H__
#define __MY_IPC_H__

#include "common.h"

// TODO: FIFO PIPE SOCKET(AF_LOCAL)

class MyIPCTest : public ModuleBase
{
public:
    MyIPCTest() : ModuleBase(MODULE_IPC, "MODULE_IPC"){};
    int test();

private:
};

#endif