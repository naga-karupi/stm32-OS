/**
 * @file Generator.hpp
 * @brief コルーチン用のジェネレータークラスの実装
 * @version 0.1
 * @date 2023-09-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <coroutine>
#include "handle.hpp"


class Generator
{
public:
	struct promise_type
	{
		YieldHandle* pyh;
		static auto get_return_object_an_allocation_failure() 
		{
			return Generator{ nullptr }; 
		}

		auto get_return_object() 
		{
			return Generator(Handle::from_promise(*this)); 
		}

		std::suspend_always initial_suspend()
		{
			return {};
		}
		
		std::suspend_always final_suspend()
		{
			return {};
		}

		void unhandled_exception()
		{
			 /*TODO*/
		}

		void return_void()
		{

		}

		auto yield_value(YieldHandle& yh)
		{
			pyh = &yh;
			return std::suspend_always{};
		}
	};

	Generator(const Generator&)
	{

	}

	Generator(Generator&& rGen)
	  : handle(rGen.handle)
	{
		rGen.handle = nullptr;
	} 

	bool DoTask()
	{
		return handle ? (handle.resume(), not handle.done()) : false;
	}

private:
	using Handle = std::coroutine_handle<promise_type>;
	
	Generator(Handle h) : handle(h)
	{

	}
	
	Handle handle;
	
};
