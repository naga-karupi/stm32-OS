/**
 * @file generator.cpp
 * @author Nishinaga
 * @brief Generatorの定義
 * @version 0.1
 * @date 2023-10-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <exception>

#include "generator.hpp"

Generator Generator::promise_type::get_return_object() const
{
    return Generator(Handle::from_promise(*this));
}


std::suspend_always Generator::promise_type::initial_suspend() const noexcept
{
    return {};
}

std::suspend_always Generator::promise_type::final_suspend() const noexcept
{
    return {};
}

void Generator::promise_type::unhandled_exception() const
{
    std::terminate();
}

void Generator::promise_type::return_void() const noexcept
{

}

std::suspend_always Generator::promise_type::yield_value(YieldHandle& yh) noexcept
{
    pyh = &yh;
    return {};
}

Generator::Generator(Generator&& rGen) 
  : handle(rGen.handle)
{
    rGen.handle = nullptr;
}

Generator::~Generator()
{
//    if(handle) handle.destroy();
}

bool Generator::DoTask()
{
    if(handle)
    {
        handle.resume();
        auto done = handle.done();

        if(done)
        {
            handle.destroy();
            handle = nullptr;
        }

        return not done;
    }
    
    return false;
}

void Generator::Destroy() noexcept
{
    handle.destroy();
    handle = nullptr;
}

Generator::operator bool() noexcept
{
    return (bool)handle;
}

Generator& Generator::operator = (Generator&& rGen)
{
    if(handle)
        handle.destroy();
    
    handle = rGen.handle;
    rGen.handle = nullptr;

    return *this;

}

Generator::Handle& Generator::GetHandle()
{
    return handle;
}

Generator::Generator(Handle h) 
  : handle(h)
{

}
