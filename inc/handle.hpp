/**
 * @file handle.hpp
 * @author Nishinaga
 * @brief co_yieldに返すハンドル型を定義
 * @version 0.1
 * @date 2023-09-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief co_yieldの返り値として使う
 * 
 */

#pragma once

class YieldHandle
{

public:
    /**
     * @brief 復帰できるかを判定する。
     * 
     * @return true 復帰可能　
     * @return false 復帰不可
     */
    virtual bool JudgeReturn() = 0;
};
