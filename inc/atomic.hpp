/**
 * @file atomic.hpp
 * @author Nishinaga
 * @brief Atomic変数を実現するクラスの定義
 * @version 0.1
 * @date 2023-09-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <concepts>
#include <utility>

template <std::copyable Copyable>
class Atomic
{
public:
    Atomic(Copyable);
    Atomic(Atomic&&);

    ~Atomic();

    bool isLockFree();
    
    void Store(Copyable);

    Copyable Load();

    template<typename T>
    operator T();

    Copyable Exchange(Copyable);

    Copyable CompareExchange(Copyable);

private:
    Atomic(Atomic&) = delete;
    void operator = (Atomic&) = delete;
    void operator = (Atomic&&) = delete;
};
