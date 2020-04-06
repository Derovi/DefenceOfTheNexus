#ifndef QUEUE_H
#define QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>


template<typename T>
class Queue {
  public:
    Queue() = default;

    Queue(const Queue<T>& other) = delete;

    Queue& operator=(const Queue<T>& other) = delete;

    int size() const;

    bool empty() const;

    const T& front() const;

    void push(const T& item);

    void push(T&& item);

    void pop();

  private:
    mutable std::mutex mutex;
    mutable std::condition_variable isEmpty;
    std::queue<T> queue;
};

template<typename T>
int Queue<T>::size() const {
    std::unique_lock<std::mutex> locker(mutex);
    return queue.size();
}

template<typename T>
bool Queue<T>::empty() const {
    std::unique_lock<std::mutex> locker(mutex);
    return queue.empty();
}

template<typename T>
const T& Queue<T>::front() const {
    std::unique_lock<std::mutex> locker(mutex);
    while (queue.empty()) {
        isEmpty.wait(locker);
    }
    return queue.front();
}

template<typename T>
void Queue<T>::push(const T& item) {
    std::unique_lock<std::mutex> locker(mutex);
    queue.push(item);
    isEmpty.notify_one();
}

template<typename T>
void Queue<T>::push(T&& item) {
    std::unique_lock<std::mutex> locker(mutex);
    queue.push(item);
    isEmpty.notify_one();
}

template<typename T>
void Queue<T>::pop() {
    std::unique_lock<std::mutex> locker(mutex);
    while (queue.empty()) {
        isEmpty.wait(locker);
    }
    queue.pop();
}

#endif // QUEUE_H
