#include "mySmartPointer.h"
#include <iostream>
#include <memory>
#include "commonDebug.h"

// 智能指针参考：https://blog.csdn.net/zy19940906/article/details/50470087

namespace smartPointerTest
{
    class A
    {

    };
}

int MySmartPointerTest::test()
{
#if 0
    std::auto_ptr<smartPointerTest::A> a(new smartPointerTest::A);
    DEBUG("a.get()=%p", a.get());
    a.reset();
    DEBUG("a.reset()");
    DEBUG("a.get()=%p", a.get());
    
    std::unique_ptr<smartPointerTest::A> b(new smartPointerTest::A);
    DEBUG("b.get()=%p", b.get());
    b.reset();
    DEBUG("b.reset()");
    DEBUG("b.get()=%p", b.get());
#endif
    my_smart_pointer::shared_ptr<int> sp(new int(100));
    my_smart_pointer::shared_ptr<smartPointerTest::A> sp2(new smartPointerTest::A);
    std::shared_ptr<int> stdSp = std::make_shared<int>();
    // std::shared_ptr<int> stdSp2 = std::shared_ptr<int>();
    return 0;
}