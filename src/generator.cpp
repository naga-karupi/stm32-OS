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

#include "inc/generator.hpp"

std::suspend_always Generator::promise_type::initial_suspend() const noexcept
{
    return {};
}

std::suspend_always Generator::promise_type::final_suspend() const noexcept
{
    return {};
}

void Generator::promise_type::unhandled_exception()
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

Generator::Generator(const Generator& Gen) 
  : handle(Gen.handle)
{

}

Generator::Generator(Generator&& rGen) 
  : handle(rGen.handle)
{
    rGen.handle = nullptr;
}

bool Generator::DoTask()
{
    return handle ? (handle.resume(), not handle.done()) : false;
}

Generator::Handle& Generator::GetHandle()
{
    return handle;
}

Generator::Generator(Handle h) 
  : handle(h)
{

}
