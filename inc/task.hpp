/**
 * @file task.hpp
 * @author Nishinaga
 * @brief 
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstddef>

#include "handle.hpp"
#include "generator.hpp"

/**
 * @brief ユーザ側で定義する関数の型
 * 
 */
class Task : public Generator
{
    size_t m_priority;
    size_t m_ID;
    size_t m_depth;
    float m_frequency;

    bool ready;

public:
    Task(Task&&);
    Task(Generator&&);

    void operator=(Task&&);
    void operator=(Generator&&);

    bool Init(size_t priority, size_t ID, size_t depth, float frequency);

    size_t GetPriority();
    void SetPriority(size_t priority);

    size_t GetID();
    void SetID(size_t ID);

    // version 0.1では未実装
    // size_t GetDepth();
    // void ResetDepth(size_t depth);

    float GetFrequency();
    void SetFrequency(float frequency);


    Task() = delete;
    Task(Task&) = delete;
    Task(Generator&) = delete;
    void operator=(Task&) = delete;

};
