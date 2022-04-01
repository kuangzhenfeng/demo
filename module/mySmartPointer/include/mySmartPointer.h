#ifndef __MY_SMART_POINTER_H__
#define __MY_SMART_POINTER_H__

#include <memory>
#include "common.h"

class MySmartPointerTest : public ModuleBase
{
public:
    MySmartPointerTest() : ModuleBase(MODULE_SMART_POINTER, "MODULE_SMART_POINTER"){};
    int test();

private:


};

namespace my_smart_pointer
{
    template<typename T>
    class shared_ptr
    {
    public:
        shared_ptr() : _ptr(nullptr), _refCount(nullptr){};
        shared_ptr(T *obj) : _ptr(obj), _refCount(new int(1)){};
        ~shared_ptr()
        {
            if(_ptr && 0 == --*_refCount)
            {
                delete _ptr;
                delete _refCount;
            }
        }
        shared_ptr(shared_ptr &other) : _ptr(other._ptr), _refCount(&(++*other._refCount)){}
        shared_ptr operator=(shared_ptr &other)
        {
            if(this == &other)
                return *this;
            ++*other._refCount;
            if(0 == --*_refCount)
            {
                delete _ptr;
                delete _refCount;
            }
            _ptr = other._ptr;
            _refCount = other._refCount;
            return *this;
        }
        T &operator*()
        {
            return *_ptr;
        }
        T *operator->()
        {
            return _ptr;
        }
        T *get()
        {
            return _ptr;
        }

    private:
        T *_ptr;
        int *_refCount;
    };

}
 




#endif