/**
 * @file mutex.hpp
 * @brief ミューテックスまわりの実装を行う。シングルコアでは割り込みの禁止のみを行う。
 *        デュアルコアは実装未定(実装者が未所持のため)
 * @version 0.1
 * @date 2023-09-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <mutex>

/**
 * @brief ミューテックスの本体
 * 
 */
class Mutex
{
public:

    Mutex() noexcept;

    ~Mutex();

    /**
     * @brief ロックを取得します。
     * 
     */
    void Lock();

    /**
     * @brief ロックを取得できるか試します。
     * 
     * @return true ロックが取得できた。
     * @return false ロックが取得できなかった。
     */
    bool TryLock();

    /**
     * @brief ロックを手放します。
     * 
     */
    void Unlock();
};


/**
 * @brief ミューテックスのロックと開放を任せるクラス
 * 
 */
class LockGuard
{
public:
    LockGuard(Mutex&);
    ~LockGuard();

    Mutex& TransferMutex();

    LockGuard() = delete;
    LockGuard(LockGuard&) = delete;
    LockGuard(LockGuard&&) = delete;
    void operator = (LockGuard&) = delete;
    void operator = (LockGuard&&) = delete;
};
