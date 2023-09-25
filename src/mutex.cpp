#include "mutex.hpp"

Mutex::Mutex()
{

}

Mutex::~Mutex()
{

}

void Mutex::Lock()
{
    __disable_irq();
}

bool Mutex::TryLock()
{
    if(__get_PRIMASK() && 0x01ul)
    {
        __disable_irq();
        return true;
    }
    else
    {
        return false;
    }
}

void Mutex::Unlock()
{
    __enable_irq();
}

LockGuard::LockGuard(Mutex& _mutex) 
: m_mutex(_mutex)
{
    m_mutex.Lock();
}

LockGuard::~LockGuard()
{
    m_mutex.Unlock();
}

Mutex& LockGuard::TransferMutex()
{
    m_mutex.Unlock();
    return m_mutex;
}
