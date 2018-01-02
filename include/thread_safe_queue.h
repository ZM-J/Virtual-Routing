#ifndef CONCURRENT_QUEUE_
#define CONCURRENT_QUEUE_

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class Queue {
   public:
    T pop();
    void pop(T& item);
    void push(const T& item);

    Queue() = default;
    Queue(const Queue&) = delete;             // disable copying
    Queue& operator=(const Queue&) = delete;  // disable assignment

   private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif