#ifndef __MY_MODULE_BASE_H__
#define __MY_MODULE_BASE_H__

class TestBase
{
public:
    TestBase(){};
    virtual ~TestBase(){};

    virtual int test() = 0;

private:
};

#endif