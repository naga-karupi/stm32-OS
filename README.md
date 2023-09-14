# naga OS

stm32の開発を楽にしたいという思想から生まれたマルチスレッドを実現するためのOS

最終的なユーザーコード予定

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
    Task Setup() override
    {
        // Setup処理
    }

    Task Loop() override
    {
        // Loop処理
    }
};

class ProcessB : public Process
{
    BinarySemaphore bs;
    CountingSemaphore<3> cs;
public:
    Task Setup() override
    {
        // Setup処理
    }

    Task Loop() override
    {
        // Loop処理
    }
};

int main() 
{
    using system = System<ShareObject>; // 共有オブジェクトの設定
    
    system::setFrequency(500);//500Hz

    system::Add<A>(Args...).setPriority(Priority::High).setStackSize(1024); // スレッドの追加(優先度高、stackの量1024KB)
    system::Add<B>(); // スレッドの追加(何も書かない場合はコンストラクタの引数なし、優先度普通、stackの量は256KB)

    system.launch();
}
```
