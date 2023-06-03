#include "Test.h"
#include "stdlib.h"

Test::Test()
{

}


void Test::startWork(CallbackFun callback)
{
    for (size_t i = 0; i < 100; i++)
    {
        _sleep(10);
        if (callback != nullptr)
            callback(false,static_cast<float>(i)/100.f);
    }
    callback(true,1);
}
