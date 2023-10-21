/**
 * @file priority-queue.hpp
 * @author Nishinaga
 * @brief 優先度付きキュー
 * @version 0.1
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <concepts>
#include <utility>
#include <queue>

#include "task.hpp"

#pragma once

/**
 * @brief type eraser
 * 
 */
class TaskPriorityQueueInternal
{
    virtual bool Push(Task&&) = 0;
    virtual Task Pop() = 0;

    virtual bool Empty() = 0;
    virtual size_t Size() = 0;
};

/**
 * @brief 今の実装だと優先度値が大きい方が優先度が高い扱いとなっている
 *        必要に応じて変更
 * 
 * @tparam SIZE queue size
 */
template<size_t SIZE>
class TaskPriorityQueue : public TaskPriorityQueueInternal
{
    Task m_tasks[SIZE];
    size_t m_size = 0;

    void Enqueue(Task&& rTask)
    {
        m_tasks[m_size] = std::move(rTask);
        EnqueueSwap(m_size);
        
        ++m_size;
    }

    Task Dequeue()
    {
        Task r_task = std::move(m_tasks[0]);

        DequeueSwap(0);

        --m_size;
        return r_task;
    }

    void EnqueueSwap(const size_t child)
    {
        const auto parent = (child - 1) / 2;

        if(child == 0)
            return;

        if(m_tasks[child].GetPriority() <= m_tasks[parent].GetPriority())
            return;

        std::swap(m_tasks[parent], m_tasks[child]);

        return EnqueueSwap(parent);
    }

    void DequeueSwap(const size_t parent)
    {
        const auto new_size = m_size - 1;
        const auto child_1 = parent * 2 + 1;
        const auto child_2 = parent * 2 + 2;

        if(new_size == 0)
            return;

        if(parent == 0)
            m_tasks[0] = std::move(m_tasks[new_size]);
        
        if(child_1 >= new_size)
            return;

        if(child_2 == new_size)
        {
            if(m_tasks[parent].GetPriority() <= m_tasks[child_1].GetPriority())
                std::swap(m_tasks[parent], m_tasks[child_1]);
            
            return;
        }

        const auto comp_child = (m_tasks[child_1].GetPriority() >= m_tasks[child_2].GetPriority())
                                    ? child_1 : child_2;

        if(m_tasks[parent].GetPriority() >= m_tasks[comp_child].GetPriority())
            return;

        std::swap(m_tasks[parent], m_tasks[comp_child]);
        return DequeueSwap(comp_child);
    }
    
public:
    TaskPriorityQueue() {}

    bool Push(Task&& rTask) override
    {
        if(m_size >= SIZE)
        {
            return false;
        }

        if(not rTask.Available())
        {
            return false;
        }

        Enqueue(std::move(rTask));

        return true;
    }

    Task Pop() override
    {
        if(m_size <= 0)
        {
            return Task{};
        }

        return Dequeue();
    }
    
    bool Empty() override
    {
        return m_size == 0;
    }

    size_t Size() override
    {
        return m_size;
    }
};
