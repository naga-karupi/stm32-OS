# naga OS

stm32の開発を楽にしたいという思想から生まれたマルチスレッドを実現するためのOS

最終的に

```cpp
#include "naga-OS.h"

struct ShareObject
{
    // スレッド全体で共有するオブジェクト
    // Atomic変数として扱われる
};

class ProcessA : public Process
{
    Mutex mutex;
    ConditionVariable sv{functionObject};
public:
    void Setup() override
    {
        // Setup処理
    }

    void Loop() override
    {
        // Loop処理
    }
};

class ProcessB : public Process
{
    BinarySemaphore bs;
    CountingSemaphore<3> cs;
public:
    void Setup() override
    {
        // Setup処理
    }

    void Loop() override
    {
        // Loop処理
    }
};

int main() 
{
    using system = System<ShareObject>; // 共有オブジェクトの設定

    system::Add<A>(Priority::High); // スレッドの追加
    system::Add<B>(/* 何も書かない場合はPriority::Normal */); // スレッドの追加
}
```
