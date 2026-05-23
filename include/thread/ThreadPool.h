#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t threadCount);

    ~ThreadPool();

    void addTask(const std::function<void()>& task);

private:
    void worker();

private:
    std::vector<std::thread> m_threads;

    std::queue<std::function<void()>> m_tasks;

    std::mutex m_mutex;

    std::condition_variable m_cond;

    bool m_stop;
};

#endif