#include "task.hpp"
#include "priority-queue.hpp"

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

TEST(SystemTest, CoroutineTest6)
{
    auto f = t();
    f.Init(4, 4, 0.1);
    ASSERT_EQ(f.Available(), true);
}

TEST(SystemTest, TaskTest)
{
    auto f = t();
    auto g = t();

    std::swap(f, g);
}

Task F()
{
    std::cout << "F\n";
    co_yield a;
}

Task G()
{
    std::cout << "G\n";
    co_yield a;
}

Task H()
{
    std::cout << "H\n";
    co_yield a;
}

Task I()
{
    std::cout << "I\n";
    co_yield a;
}




TEST(SystemTest, PriorityQTest1)
{
    TaskPriorityQueue<4> Q;
    auto f = F();
    auto g = G();
    auto h = H();
    auto i = I();

    ASSERT_TRUE(f.Init(1, 1, 1));
    ASSERT_TRUE(g.Init(5, 2, 2));
    ASSERT_TRUE(h.Init(4, 3, 3));
    ASSERT_TRUE(i.Init(4, 4, 4));

    ASSERT_TRUE(Q.Push(std::move(f)));
    ASSERT_TRUE(Q.Push(std::move(g)));
    ASSERT_TRUE(Q.Push(std::move(h)));
    ASSERT_TRUE(Q.Push(std::move(i)));

    ASSERT_EQ(Q.Size(), 4);

    auto a = Q.Pop();
    auto b = Q.Pop();
    auto c = Q.Pop();
    auto d = Q.Pop();

    ASSERT_EQ(Q.Size(), 0);

    ASSERT_TRUE((bool)a);
    ASSERT_TRUE((bool)b);
    ASSERT_TRUE((bool)c);
    ASSERT_TRUE((bool)d);

    while(a.DoTask());
    while(b.DoTask());
    while(c.DoTask());
    while(d.DoTask());
}
