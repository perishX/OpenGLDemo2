#ifndef TEST_H
#define TEST_H

typedef void(* CallbackFun)(bool,float);

class Test
{
public:
    Test();
    void startWork(CallbackFun callback=nullptr);
};

#endif // TEST_H
