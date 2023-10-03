/**
 * @file rTask.cpp
 * @author Nishinaga
 * @brief Task型の定義
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <utility>

#include "task.hpp"

Task::Task(Task&& rTask)
  : Generator(),
    m_priority(rTask.m_priority), 
    m_ID(rTask.m_ID), 
    m_depth(rTask.m_depth),
    m_frequency(rTask.m_frequency),
    ready(true)
{
    (Generator&&)*this = std::move(rTask);
}

Task::Task(Generator&& rGen)
  : Generator(std::move(rGen)),
    ready(false)
{

}

void Task::operator=(Task&& rTask)
{
    m_priority = rTask.m_priority;
    m_ID       = rTask.m_ID;
    m_depth    = rTask.m_depth;
    
    (Generator&&)*this = std::move(rTask);
}

void Task::operator=(Generator&& rGen)
{
    (Generator&&)*this = std::move(rGen);
}

bool Task::Init(size_t priority, size_t ID, size_t depth, float frequency)
{
    if(not ready)
    {
        m_priority = priority;
        m_ID = ID;
        m_depth = depth;
        m_frequency = frequency;
        ready = true;

        return true;
    }

    return false;    
}

size_t Task::GetPriority()
{
    return m_priority;
}

void Task::SetPriority(size_t priority)
{
    m_priority = priority;
}

size_t Task::GetID()
{
    return m_ID;
}

void Task::SetID(size_t ID)
{
    m_ID = ID;
}

// Version 0.1では未実装
// size_t Task::GetDepth()
// {
//     return m_depth;
// }

// // 必要かどうか要検討
// void Task::ResetDepth(size_t depth)
// {
// //    m_depth = depth;
// //    メモリのアロックも
// }

float Task::GetFrequency()
{
    return m_frequency;
}

void Task::SetFrequency(float frequency)
{
    m_frequency = frequency;
}
