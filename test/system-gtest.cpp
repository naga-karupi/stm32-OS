#include "task.hpp"

#include <iostream>
#include <gtest/gtest.h>

class A : public YieldHandle
{

public:
    int counter = 0;
    bool JudgeReturn() override {
        std::cout << counter << std::endl;    
        counter++;
        return true;
    }
};

A a;

Task t() 
{
    co_yield a;
    co_yield a;
    co_yield a;
    co_return;
}

A a2;

Task s()
{
    co_yield a2;
    co_yield a2;
    co_yield a2;
    co_return;
}

TEST(SystemTest, CoroutineTest1) 
{
    auto f = t();

    while(f.DoTask());

    ASSERT_FALSE(f);
}


TEST(SystemTest, CoroutineTest2) 
{
    auto f = t();
    int counter = 0;

    while(f.DoTask()) counter++;

    ASSERT_FALSE(f);

    ASSERT_EQ(counter, 3);
}

TEST(SystemTest, CoroutineTest3)
{
    auto f = t();
    auto g = t();

    while(f.DoTask());

    ASSERT_FALSE(f);
    ASSERT_TRUE((bool)g);
}

TEST(SystemTest, CoroutineTest4)
{
    auto f = t();
    
    while(f.DoTask());

    auto g = std::move(f);

    ASSERT_FALSE((bool)g);
}

TEST(SystemTest, CoroutineTest5)
{
    int counter = 0;

    auto f = t();

    f.DoTask();
    counter++;

    auto g = std::move(f);

    while(g.DoTask()) counter++;

    ASSERT_FALSE(f);
    ASSERT_FALSE((bool)g);

    ASSERT_EQ(counter, 3);
}
