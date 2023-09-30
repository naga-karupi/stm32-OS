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
	struct promise_type;

	/**
	 * @brief エイリアスの設定
	 * 
	 */
	using Handle = std::coroutine_handle<promise_type>;

	/**
	 * @brief コルーチンの使用に必要な構造体
	 * 
	 */
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

		std::suspend_always initial_suspend() const noexcept
		{
			return {};
		}
		
		std::suspend_always final_suspend() const noexcept
		{
			return {};
		}

		void unhandled_exception()
		{
			 /*TODO*/
		}

		void return_void() const noexcept
		{

		}

		auto yield_value(YieldHandle& yh) noexcept
		{
			pyh = &yh;
			return std::suspend_always{};
		}
	};

	/**
	 * @brief Construct a new Generator object
	 * 
	 * @param Gen Generator型左辺値オブジェクト
	 */
	Generator(const Generator& Gen) : handle(Gen.handle)
	{

	}

	/**
	 * @brief Construct a new Generator object
	 * 
	 * @param rGen Generator型右辺値オブジェクト
	 */
	Generator(const Generator&& rGen)
	  : handle(rGen.handle)
	{
		rGen.handle = nullptr;
	} 

	/**
	 * @brief タスクの実行
	 * 
	 * @return true 実行成功
	 * @return false 実行失敗
	 */
	bool DoTask()
	{
		return handle ? (handle.resume(), not handle.done()) : false;
	}

	/**
	 * @brief Get the Handle object
	 * 
	 * @return Handle& Generator型の保有しているハンドル
	 */
	Handle& GetHandle()
	{
		return handle;
	}

private:
	Generator(Handle h) : handle(h)
	{

	}
	
	Handle handle;
	
};