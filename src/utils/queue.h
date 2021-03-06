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

    void push(const T& item);

    void push(T&& item);

    T pop();

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
T Queue<T>::pop() {
    std::unique_lock<std::mutex> locker(mutex);
    isEmpty.wait(locker, [&]() { return !queue.empty(); });
    T item = queue.front();
    queue.pop();
    isEmpty.notify_one();
    return item;
}

#endif // QUEUE_H
