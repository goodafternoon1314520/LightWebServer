#include "thread/ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount) : m_stop(false) {
    for (size_t i = 0; i < threadCount; i++)
        m_threads.emplace_back(&ThreadPool::worker, this);
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_stop = true;
    }

    m_cond.notify_all();

    for (auto& t : m_threads)
        t.join();
}

void ThreadPool::addTask(const std::function<void()>& task) {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_tasks.push(task);
    }

    m_cond.notify_one();
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_cond.wait(lock, [this] {return m_stop || !m_tasks.empty();});

            if (m_stop && m_tasks.empty())
                return;

            task = m_tasks.front();

            m_tasks.pop();
        }
        task();
    }
}